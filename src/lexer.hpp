#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "gramatica.hpp"

struct Token {
    Terminal tipo;
    std::string lexema;
    int linea;
    int columna;
};

class ErrorLexico : public std::runtime_error {
public:
    ErrorLexico(const std::string& mensaje, int linea, int columna)
        : std::runtime_error(mensaje), linea(linea), columna(columna) {}

    int linea;
    int columna;
};

// Convierte el texto en la lista de tokens que consume el motor LR, terminada en $.
// Con soloNombres = true la entrada ya es una lista de tokens ("select id , id from id ;"),
// así que las palabras deben ser nombres de terminal y no se aceptan literales.
std::vector<Token> tokenizar(const std::string& texto, bool soloNombres);

// "id alumnos", "num 18", "str 'Ana'"; para los demás terminales, su nombre.
std::string describirToken(const Token& token);
