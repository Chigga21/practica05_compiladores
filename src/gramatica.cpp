#include "gramatica.hpp"

// Gramática aumentada; el índice de cada producción es su número de regla.
const Produccion PRODUCCIONES[NUM_PRODUCCIONES] = {
    {NT_S_PRIMA, 1, "S' -> Script"},
    {NT_SCRIPT, 2, "Script -> Script Query"},
    {NT_SCRIPT, 1, "Script -> Query"},
    {NT_QUERY, 5, "Query -> select Cols from id ;"},
    {NT_QUERY, 7, "Query -> select Cols from id where Cond ;"},
    {NT_COLS, 1, "Cols -> *"},
    {NT_COLS, 1, "Cols -> ColList"},
    {NT_COLLIST, 3, "ColList -> ColList , id"},
    {NT_COLLIST, 1, "ColList -> id"},
    {NT_COND, 3, "Cond -> Cond or Conj"},
    {NT_COND, 1, "Cond -> Conj"},
    {NT_CONJ, 3, "Conj -> Conj and Neg"},
    {NT_CONJ, 1, "Conj -> Neg"},
    {NT_NEG, 2, "Neg -> not Neg"},
    {NT_NEG, 1, "Neg -> Pred"},
    {NT_PRED, 3, "Pred -> Val Op Val"},
    {NT_PRED, 3, "Pred -> ( Cond )"},
    {NT_OP, 1, "Op -> ="},
    {NT_OP, 1, "Op -> <"},
    {NT_OP, 1, "Op -> >"},
    {NT_VAL, 1, "Val -> id"},
    {NT_VAL, 1, "Val -> num"},
    {NT_VAL, 1, "Val -> str"},
};

std::string_view nombreTerminal(Terminal t) {
    static constexpr std::string_view NOMBRES[NUM_TERMINALES] = {
        "select", "from", "where", "or", "and", "not", "id", "num", "str",
        "*", ",", ";", "(", ")", "=", "<", ">", "$",
    };
    return NOMBRES[t];
}

std::string_view nombreNoTerminal(NoTerminal a) {
    static constexpr std::string_view NOMBRES[NUM_NO_TERMINALES + 1] = {
        "Script", "Query", "Cols", "ColList", "Cond", "Conj", "Neg", "Pred", "Op", "Val", "S'",
    };
    return NOMBRES[a];
}
