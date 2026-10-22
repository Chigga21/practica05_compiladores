#include "tabla_slr.hpp"

namespace {

constexpr Accion s(int estado) { return {TipoAccion::Desplazar, estado}; }
constexpr Accion r(int regla) { return {TipoAccion::Reducir, regla}; }
constexpr Accion acc{TipoAccion::Aceptar, 0};
constexpr Accion err{TipoAccion::Error, 0};

}  // namespace

// Las reducciones sólo aparecen en las columnas de Follow(A) (regla SLR(1)). Los estados
// 7, 16 y 34 son los que en LR(0) tenían un conflicto desplazamiento/reducción.
const Accion ACCION[NUM_ESTADOS][NUM_TERMINALES] = {
    //        select from   where  or     and    not    id     num    str    *      ,      ;      (      )      =      <      >      $
    /*  0 */ {s(3),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err},
    /*  1 */ {s(3),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   acc},
    /*  2 */ {r(2),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   r(2)},
    /*  3 */ {err,   err,   err,   err,   err,   err,   s(8),  err,   err,   s(6),  err,   err,   err,   err,   err,   err,   err,   err},
    /*  4 */ {r(1),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   r(1)},
    /*  5 */ {err,   s(9),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err},
    /*  6 */ {err,   r(5),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err},
    /*  7 */ {err,   r(6),  err,   err,   err,   err,   err,   err,   err,   err,   s(10), err,   err,   err,   err,   err,   err,   err},  // LR(0): s10/r6 en ','; Follow(Cols) = {from}
    /*  8 */ {err,   r(8),  err,   err,   err,   err,   err,   err,   err,   err,   r(8),  err,   err,   err,   err,   err,   err,   err},
    /*  9 */ {err,   err,   err,   err,   err,   err,   s(11), err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err},
    /* 10 */ {err,   err,   err,   err,   err,   err,   s(12), err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err},
    /* 11 */ {err,   err,   s(14), err,   err,   err,   err,   err,   err,   err,   err,   s(13), err,   err,   err,   err,   err,   err},
    /* 12 */ {err,   r(7),  err,   err,   err,   err,   err,   err,   err,   err,   r(7),  err,   err,   err,   err,   err,   err,   err},
    /* 13 */ {r(3),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   r(3)},
    /* 14 */ {err,   err,   err,   err,   err,   s(18), s(22), s(23), s(24), err,   err,   err,   s(21), err,   err,   err,   err,   err},
    /* 15 */ {err,   err,   err,   s(26), err,   err,   err,   err,   err,   err,   err,   s(25), err,   err,   err,   err,   err,   err},
    /* 16 */ {err,   err,   err,   r(10), s(27), err,   err,   err,   err,   err,   err,   r(10), err,   r(10), err,   err,   err,   err},  // LR(0): s27/r10 en and; Follow(Cond) = {; ) or}
    /* 17 */ {err,   err,   err,   r(12), r(12), err,   err,   err,   err,   err,   err,   r(12), err,   r(12), err,   err,   err,   err},
    /* 18 */ {err,   err,   err,   err,   err,   s(18), s(22), s(23), s(24), err,   err,   err,   s(21), err,   err,   err,   err,   err},
    /* 19 */ {err,   err,   err,   r(14), r(14), err,   err,   err,   err,   err,   err,   r(14), err,   r(14), err,   err,   err,   err},
    /* 20 */ {err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   s(30), s(31), s(32), err},
    /* 21 */ {err,   err,   err,   err,   err,   s(18), s(22), s(23), s(24), err,   err,   err,   s(21), err,   err,   err,   err,   err},
    /* 22 */ {err,   err,   err,   r(20), r(20), err,   err,   err,   err,   err,   err,   r(20), err,   r(20), r(20), r(20), r(20), err},
    /* 23 */ {err,   err,   err,   r(21), r(21), err,   err,   err,   err,   err,   err,   r(21), err,   r(21), r(21), r(21), r(21), err},
    /* 24 */ {err,   err,   err,   r(22), r(22), err,   err,   err,   err,   err,   err,   r(22), err,   r(22), r(22), r(22), r(22), err},
    /* 25 */ {r(4),  err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   err,   r(4)},
    /* 26 */ {err,   err,   err,   err,   err,   s(18), s(22), s(23), s(24), err,   err,   err,   s(21), err,   err,   err,   err,   err},
    /* 27 */ {err,   err,   err,   err,   err,   s(18), s(22), s(23), s(24), err,   err,   err,   s(21), err,   err,   err,   err,   err},
    /* 28 */ {err,   err,   err,   r(13), r(13), err,   err,   err,   err,   err,   err,   r(13), err,   r(13), err,   err,   err,   err},
    /* 29 */ {err,   err,   err,   err,   err,   err,   s(22), s(23), s(24), err,   err,   err,   err,   err,   err,   err,   err,   err},
    /* 30 */ {err,   err,   err,   err,   err,   err,   r(17), r(17), r(17), err,   err,   err,   err,   err,   err,   err,   err,   err},
    /* 31 */ {err,   err,   err,   err,   err,   err,   r(18), r(18), r(18), err,   err,   err,   err,   err,   err,   err,   err,   err},
    /* 32 */ {err,   err,   err,   err,   err,   err,   r(19), r(19), r(19), err,   err,   err,   err,   err,   err,   err,   err,   err},
    /* 33 */ {err,   err,   err,   s(26), err,   err,   err,   err,   err,   err,   err,   err,   err,   s(37), err,   err,   err,   err},
    /* 34 */ {err,   err,   err,   r(9),  s(27), err,   err,   err,   err,   err,   err,   r(9),  err,   r(9),  err,   err,   err,   err},  // LR(0): s27/r9 en and; Follow(Cond) = {; ) or}
    /* 35 */ {err,   err,   err,   r(11), r(11), err,   err,   err,   err,   err,   err,   r(11), err,   r(11), err,   err,   err,   err},
    /* 36 */ {err,   err,   err,   r(15), r(15), err,   err,   err,   err,   err,   err,   r(15), err,   r(15), err,   err,   err,   err},
    /* 37 */ {err,   err,   err,   r(16), r(16), err,   err,   err,   err,   err,   err,   r(16), err,   r(16), err,   err,   err,   err},
};

// SIN_TRANSICION (-1) marca las celdas vacías.
const int IR_A[NUM_ESTADOS][NUM_NO_TERMINALES] = {
    //        Script   Query    Cols     ColList  Cond     Conj     Neg      Pred     Op       Val
    /*  0 */ {1,       2,       -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  1 */ {-1,      4,       -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  2 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  3 */ {-1,      -1,      5,       7,       -1,      -1,      -1,      -1,      -1,      -1},
    /*  4 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  5 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  6 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  7 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  8 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /*  9 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 10 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 11 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 12 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 13 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 14 */ {-1,      -1,      -1,      -1,      15,      16,      17,      19,      -1,      20},
    /* 15 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 16 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 17 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 18 */ {-1,      -1,      -1,      -1,      -1,      -1,      28,      19,      -1,      20},
    /* 19 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 20 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      29,      -1},
    /* 21 */ {-1,      -1,      -1,      -1,      33,      16,      17,      19,      -1,      20},
    /* 22 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 23 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 24 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 25 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 26 */ {-1,      -1,      -1,      -1,      -1,      34,      17,      19,      -1,      20},
    /* 27 */ {-1,      -1,      -1,      -1,      -1,      -1,      35,      19,      -1,      20},
    /* 28 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 29 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      36},
    /* 30 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 31 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 32 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 33 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 34 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 35 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 36 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
    /* 37 */ {-1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1,      -1},
};
