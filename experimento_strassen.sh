#!/bin/bash

g++ -O3 uhr/uhr.cpp algoritmos/matrix_utils.cpp algoritmos/clasico.cpp algoritmos/strassen.cpp algoritmos/hibrido.cpp -o tester

# Verificar si la compilación falló
if [ $? -ne 0 ]; then
    exit 1
fi

# Parámetros base
LOW=32
UP_MAX=2048     # Límite máximo general
EXPERIMENTOS=("REALES" "ENTEROS" "IDENTIDAD" "SPARSE")


for exp in "${EXPERIMENTOS[@]}"; do
    ./tester "datos/STRASSEN_PURO_${exp}.csv" 32 $LOW $UP_MAX "STRASSEN" "$exp" 2
done

