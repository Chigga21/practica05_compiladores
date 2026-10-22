#include "ast.hpp"

NodoPtr accionSemantica(int regla, std::vector<NodoPtr>& v) {
    switch (regla) {
        case 1:  // Script -> Script Query
            v[0]->hijos.push_back(std::move(v[1]));
            return std::move(v[0]);
        case 2:  // Script -> Query
            return nuevoNodo("Script", std::move(v[0]));
        case 3:  // Query -> select Cols from id ;
            return nuevoNodo("Select", std::move(v[1]), nuevoNodo("Tabla", std::move(v[3])));
        case 4:  // Query -> select Cols from id where Cond ;
            return nuevoNodo("Select", std::move(v[1]), nuevoNodo("Tabla", std::move(v[3])),
                             nuevoNodo("Where", std::move(v[5])));
        case 5:  // Cols -> *
        case 8:  // ColList -> id
            return nuevoNodo("Columnas", std::move(v[0]));
        case 7:  // ColList -> ColList , id
            v[0]->hijos.push_back(std::move(v[2]));
            return std::move(v[0]);
        case 9:  // Cond -> Cond or Conj
            return nuevoNodo("OR", std::move(v[0]), std::move(v[2]));
        case 11:  // Conj -> Conj and Neg
            return nuevoNodo("AND", std::move(v[0]), std::move(v[2]));
        case 13:  // Neg -> not Neg
            return nuevoNodo("NOT", std::move(v[1]));
        case 15:  // Pred -> Val Op Val: el operador queda como raíz de la comparación
            v[1]->hijos.push_back(std::move(v[0]));
            v[1]->hijos.push_back(std::move(v[2]));
            return std::move(v[1]);
        case 16:  // Pred -> ( Cond ): los paréntesis sólo agrupan y no generan nodo
            return std::move(v[1]);
        default:  // reglas unitarias (6, 10, 12, 14, 17-22): el valor sube sin cambios
            return std::move(v[0]);
    }
}

namespace {

void imprimirRama(const Nodo& nodo, const std::string& prefijo, bool ultimo, std::ostream& salida) {
    salida << prefijo << (ultimo ? "└── " : "├── ") << nodo.etiqueta << '\n';
    const std::string prefijoHijos = prefijo + (ultimo ? "    " : "│   ");
    for (size_t i = 0; i < nodo.hijos.size(); ++i)
        imprimirRama(*nodo.hijos[i], prefijoHijos, i + 1 == nodo.hijos.size(), salida);
}

}  // namespace

void imprimirArbol(const Nodo& raiz, std::ostream& salida) {
    salida << raiz.etiqueta << '\n';
    for (size_t i = 0; i < raiz.hijos.size(); ++i)
        imprimirRama(*raiz.hijos[i], "", i + 1 == raiz.hijos.size(), salida);
}
