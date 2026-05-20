#include "hibrido.h"

Matriz multiplicacion_hibrida(const Matriz& A, const Matriz& B, int umbral) {
    // Obtener el tamaño
    int n = A.size();

    // Verificar que sean ambas iguales
    if (B.size() != n) {
        std::cout << "Las matrices deben ser el mismo tamaño." << std::endl;
        std::exit(1);
    }

    // Mientras reciba recursivamente matrices menores al umbral, usar la
    // multiplicación clásica
    if (n < umbral) {
        return multiplicacion_clasica(A, B);
    }

    // Verificar que n sea potencia de 2
    if ((n & (n - 1)) != 0) {
        std::cout << "El tamaño de las matrices debe ser una potencia de 2."
                  << std::endl;
        std::exit(1);
    }

    // Dividir en 4 cada matriz
    int m = n / 2;
    Matriz A11(m, std::vector<double>(m));
    Matriz A12(m, std::vector<double>(m));
    Matriz A21(m, std::vector<double>(m));
    Matriz A22(m, std::vector<double>(m));

    Matriz B11(m, std::vector<double>(m));
    Matriz B12(m, std::vector<double>(m));
    Matriz B21(m, std::vector<double>(m));
    Matriz B22(m, std::vector<double>(m));

    // Llenar las submatrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + m];
            B21[i][j] = B[i + m][j];
            B22[i][j] = B[i + m][j + m];
        }
    }

    // Generar recursivamente los M1 a M7
    Matriz M1 =
        multiplicacion_hibrida(sumar(A11, A22), sumar(B11, B22), umbral);
    Matriz M2 = multiplicacion_hibrida(sumar(A21, A22), B11, umbral);
    Matriz M3 = multiplicacion_hibrida(A11, restar(B12, B22), umbral);
    Matriz M4 = multiplicacion_hibrida(A22, restar(B21, B11), umbral);
    Matriz M5 = multiplicacion_hibrida(sumar(A11, A12), B22, umbral);
    Matriz M6 =
        multiplicacion_hibrida(restar(A21, A11), sumar(B11, B12), umbral);
    Matriz M7 =
        multiplicacion_hibrida(restar(A12, A22), sumar(B21, B22), umbral);

    // Calcular las submatrices del resultado C
    Matriz C11 = sumar(restar(sumar(M1, M4), M5), M7);
    Matriz C12 = sumar(M3, M5);
    Matriz C21 = sumar(M2, M4);
    Matriz C22 = sumar(sumar(restar(M1, M2), M3), M6);

    // Combinar las submatrices en la matriz resultado C
    Matriz C = crear_matriz(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = C11[i][j];
            C[i][j + m] = C12[i][j];
            C[i + m][j] = C21[i][j];
            C[i + m][j + m] = C22[i][j];
        }
    }
    return C;
}