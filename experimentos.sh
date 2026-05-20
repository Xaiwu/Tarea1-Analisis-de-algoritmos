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
UMBRALES=(32 64 128 256)


for exp in "${EXPERIMENTOS[@]}"; do
    ./tester "datos/CLASICO_${exp}.csv" 32 $LOW $UP_MAX "CLASICO" "$exp" 2
done

# HÍBRIDO (SOLO REALES, Búsqueda de n0, 32 Runs)
for u in "${UMBRALES[@]}"; do
    ./tester "datos/HIBRIDO_n0_${u}_REALES.csv" 32 $LOW $UP_MAX  "HIBRIDO" "REALES" $u
done