#pragma once

#include <string_view>

// Terminales de la gramática. El orden coincide con las columnas de la tabla ACCION.
enum Terminal : int {
    T_SELECT,
    T_FROM,
    T_WHERE,
    T_OR,
    T_AND,
    T_NOT,
    T_ID,
    T_NUM,
    T_STR,
    T_ASTERISCO,
    T_COMA,
    T_PUNTO_Y_COMA,
    T_PAR_IZQ,
    T_PAR_DER,
    T_IGUAL,
    T_MENOR,
    T_MAYOR,
    T_FIN,  // $
};
constexpr int NUM_TERMINALES = T_FIN + 1;

// No terminales. El orden coincide con las columnas de la tabla IR_A.
enum NoTerminal : int {
    NT_SCRIPT,
    NT_QUERY,
    NT_COLS,
    NT_COLLIST,
    NT_COND,
    NT_CONJ,
    NT_NEG,
    NT_PRED,
    NT_OP,
    NT_VAL,
    NT_S_PRIMA,  // S' nunca se reduce (se acepta), por eso no tiene columna en IR_A
};
constexpr int NUM_NO_TERMINALES = NT_S_PRIMA;

// Producción A -> X1 ... Xn. El motor sólo necesita A y n para reducir;
// el texto se usa en la traza y en el árbol de reducciones.
struct Produccion {
    NoTerminal izquierda;
    int longitud;
    std::string_view texto;
};

constexpr int NUM_PRODUCCIONES = 23;
extern const Produccion PRODUCCIONES[NUM_PRODUCCIONES];

std::string_view nombreTerminal(Terminal t);
std::string_view nombreNoTerminal(NoTerminal a);
