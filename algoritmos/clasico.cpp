#include "clasico.h"

Matriz multiplicacion_clasica(const Matriz& A, const Matriz& B, int n) {
    Matriz C = crear_matriz(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}