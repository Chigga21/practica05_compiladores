# Práctica 5: motor LR para un subconjunto de SQL

Intérprete (driver) de un parser SLR(1) escrito en C++17. 

La gramática reconoce scripts de consultas con condiciones que
combinan `or`, `and`, `not`, paréntesis y comparaciones `=`, `<`, `>` entre identificadores, números y
cadenas.

## Compilación y pruebas

Se requiere un compilador con C++17 (g++ o clang++) y `make`.

```bash
make          # genera ./slr
make test     # ejecuta los 16 casos de tests/casos
make clean
```

## Uso

```bash
./slr consulta.sql                       # analiza un archivo
./slr -e "select * from alumnos;"        # analiza el texto dado
echo "select a from t;" | ./slr          # lee la entrada estándar
./slr -k -e "select id , id from id ;"   # la entrada ya es una lista de tokens
./slr -t -r -e "select * from t where not a = 1;"
```

| Opción | Efecto |
|--------|--------|
| `-e TEXTO` | analiza `TEXTO` en lugar de un archivo |
| `-k` | la entrada es una lista de nombres de token |
| `-t` | muestra la traza de la pila: contenido, entrada restante y acción de cada paso |
| `-r` | muestra el árbol de reducciones (la regla aplicada en cada nodo) |
| `-h` | ayuda |

Si la cadena es válida, el programa imprime `Resultado: ACEPTADA` y el AST, si no, imprime
`Resultado: RECHAZADA`.

En modo texto, las palabras reservadas no distinguen mayúsculas, los números admiten una parte decimal
(`3.5`), las cadenas van entre comillas simples `''` y `--` inicia un comentario.
