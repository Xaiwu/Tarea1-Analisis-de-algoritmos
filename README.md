# Implementación y análisis de algoritmos de multiplicación de matrices

## Grupo
- Jesús Guevara Salcedo
- Joseph Matamala Sepúlveda
- Marcelo Vergara Fierro

## Dependencias
- Compilador C++ con soporte C++11 o superior (`g++`, `clang++` o `MSVC`).
- Biblioteca Eigen para comparación. Para poder compilar y ejecutar `main_correctitud.cpp` con los comandos proporcionados, descargue Eigen desde https://libeigen.gitlab.io y coloque la carpeta `eigen` en la raíz del proyecto. Alternativamente, puede instalar Eigen globalmente en su sistema y ajustar los flags de compilación para apuntar a la ubicación de los headers.

## Compilación y ejecución
- Para compilar las pruebas de correctitud 
```bash
g++ main_correctitud.cpp algoritmos/clasico.cpp algoritmos/hibrido.cpp algoritmos/strassen.cpp algoritmos/matrix_utils.cpp -o correctitud  # Linux

g++ main_correctitud.cpp algoritmos/clasico.cpp algoritmos/hibrido.cpp algoritmos/strassen.cpp algoritmos/matrix_utils.cpp -o correctitud.exe  # Windows
```

- Ejecutar las pruebas de correctitud (genera `correctitud` o `correctitud.exe`):
```bash
./correctitud    # Linux
.\correctitud.exe  # Windows (PowerShell)
```
## Experimentación
- Los scripts `experimentos.sh` y `experimento_strassen.sh` automatizan ejecuciones para medir tiempos; deben ser ejecutados en un entorno que soporte bash, ya sea linux o WSL.
