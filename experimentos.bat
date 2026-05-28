@echo off

g++ -O3 ^
uhr\uhr.cpp ^
algoritmos\matrix_utils.cpp ^
algoritmos\clasico.cpp ^
algoritmos\strassen.cpp ^
algoritmos\hibrido.cpp ^
-o tester.exe

REM Verificar si la compilación falló
if %errorlevel% neq 0 (
    exit /b 1
)

REM Parámetros base
set LOW=32
set UP_MAX=2048

REM EXPERIMENTOS
for %%e in (REALES ENTEROS IDENTIDAD SPARSE) do (
    tester.exe "datos\CLASICO_%%e.csv" 32 %LOW% %UP_MAX% "CLASICO" "%%e" 2
)

REM UMBRALES
for %%u in (32 64 128 256) do (
    tester.exe "datos\HIBRIDO_n0_%%u_REALES.csv" 32 %LOW% %UP_MAX% "HIBRIDO" "REALES" %%u
)