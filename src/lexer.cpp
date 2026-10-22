#include "lexer.hpp"

#include <cctype>
#include <optional>
#include <unordered_map>

namespace {

const std::unordered_map<std::string, Terminal> PALABRAS_RESERVADAS = {
    {"select", T_SELECT}, {"from", T_FROM}, {"where", T_WHERE},
    {"or", T_OR},         {"and", T_AND},   {"not", T_NOT},
};

// Nombres de las clases léxicas; sólo son palabras válidas en el modo de lista de tokens.
const std::unordered_map<std::string, Terminal> CLASES_LEXICAS = {
    {"id", T_ID}, {"num", T_NUM}, {"str", T_STR},
};

std::optional<Terminal> simbolo(char c) {
    switch (c) {
        case '*': return T_ASTERISCO;
        case ',': return T_COMA;
        case ';': return T_PUNTO_Y_COMA;
        case '(': return T_PAR_IZQ;
        case ')': return T_PAR_DER;
        case '=': return T_IGUAL;
        case '<': return T_MENOR;
        case '>': return T_MAYOR;
        default: return std::nullopt;
    }
}

bool esLetra(char c) { return std::isalpha(static_cast<unsigned char>(c)) || c == '_'; }
bool esAlfanumerico(char c) { return std::isalnum(static_cast<unsigned char>(c)) || c == '_'; }
bool esDigito(char c) { return std::isdigit(static_cast<unsigned char>(c)); }
bool esEspacio(char c) { return std::isspace(static_cast<unsigned char>(c)); }

std::string minusculas(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// Bytes que ocupa el carácter UTF-8 cuyo primer byte es c (para mostrarlo completo en el error).
size_t longitudUtf8(unsigned char c) {
    if (c >= 0xF0) return 4;
    if (c >= 0xE0) return 3;
    if (c >= 0xC0) return 2;
    return 1;
}

class Lexer {
public:
    Lexer(const std::string& texto, bool soloNombres) : texto_(texto), soloNombres_(soloNombres) {}

    std::vector<Token> tokens() {
        std::vector<Token> resultado;
        while (true) {
            saltarEspaciosYComentarios();
            if (terminado()) break;
            resultado.push_back(siguiente());
        }
        resultado.push_back({T_FIN, "$", linea_, columna_});
        return resultado;
    }

private:
    bool terminado() const { return pos_ >= texto_.size(); }
    char actual() const { return texto_[pos_]; }
    char posterior() const { return pos_ + 1 < texto_.size() ? texto_[pos_ + 1] : '\0'; }

    void avanzar() {
        const char c = texto_[pos_++];
        if (c == '\n') {
            ++linea_;
            columna_ = 1;
        } else if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) {  // los bytes de continuación UTF-8 no cuentan
            ++columna_;
        }
    }

    void saltarEspaciosYComentarios() {
        while (!terminado()) {
            if (esEspacio(actual())) {
                avanzar();
            } else if (actual() == '-' && posterior() == '-') {  // comentario SQL hasta el fin de línea
                while (!terminado() && actual() != '\n') avanzar();
            } else {
                return;
            }
        }
    }

    Token siguiente() {
        const int linea = linea_;
        const int columna = columna_;
        const size_t inicio = pos_;
        const char c = actual();
        auto lexema = [&] { return texto_.substr(inicio, pos_ - inicio); };

        if (esLetra(c)) {
            while (!terminado() && esAlfanumerico(actual())) avanzar();
            const std::string clave = minusculas(lexema());
            if (auto it = PALABRAS_RESERVADAS.find(clave); it != PALABRAS_RESERVADAS.end())
                return {it->second, lexema(), linea, columna};
            if (!soloNombres_) return {T_ID, lexema(), linea, columna};
            if (auto it = CLASES_LEXICAS.find(clave); it != CLASES_LEXICAS.end())
                return {it->second, lexema(), linea, columna};
            throw ErrorLexico("'" + lexema() + "' no es el nombre de un token", linea, columna);
        }
        if (auto tipo = simbolo(c)) {
            avanzar();
            return {*tipo, lexema(), linea, columna};
        }
        if (soloNombres_ && (esDigito(c) || c == '\''))
            throw ErrorLexico("en una lista de tokens los literales se escriben como num o str", linea, columna);
        if (esDigito(c)) {
            while (!terminado() && esDigito(actual())) avanzar();
            if (!terminado() && actual() == '.' && esDigito(posterior())) {
                avanzar();
                while (!terminado() && esDigito(actual())) avanzar();
            }
            return {T_NUM, lexema(), linea, columna};
        }
        if (c == '\'') {
            avanzar();
            while (true) {
                if (terminado()) throw ErrorLexico("cadena sin cerrar", linea, columna);
                const char d = actual();
                avanzar();
                if (d != '\'') continue;
                if (terminado() || actual() != '\'') break;
                avanzar();  // '' dentro de la cadena es una comilla escapada
            }
            return {T_STR, lexema(), linea, columna};
        }
        const std::string caracter = texto_.substr(inicio, longitudUtf8(static_cast<unsigned char>(c)));
        throw ErrorLexico("carácter no reconocido '" + caracter + "'", linea, columna);
    }

    const std::string& texto_;
    const bool soloNombres_;
    size_t pos_ = 0;
    int linea_ = 1;
    int columna_ = 1;
};

}  // namespace

std::vector<Token> tokenizar(const std::string& texto, bool soloNombres) {
    return Lexer(texto, soloNombres).tokens();
}

std::string describirToken(const Token& token) {
    const std::string nombre(nombreTerminal(token.tipo));
    const bool llevaLexema = token.tipo == T_ID || token.tipo == T_NUM || token.tipo == T_STR;
    if (llevaLexema && minusculas(token.lexema) != nombre) return nombre + "(" + token.lexema + ")";
    return nombre;
}
