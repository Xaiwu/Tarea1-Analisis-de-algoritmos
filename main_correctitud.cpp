//g++ main_correctitud.cpp algoritmos/clasico.cpp algoritmos/hibrido.cpp algoritmos/strassen.cpp algoritmos/matrix_utils.cpp -o correctitud.exe 

#include "algoritmos/clasico.h"
#include "algoritmos/hibrido.h"
#include "algoritmos/strassen.h"
#include "algoritmos/matrix_utils.h"
#include "eigen/Eigen/Dense"

#include <iostream>
#include <iomanip>
#include <cmath>


void imprimir_matriz(const Matriz& M) {
    for (const auto& fila : M) {
        for (double val : fila) {
            std::cout << std::setw(10) << val << " ";
        }
        std::cout << std::endl;
    }
}

bool matrices_iguales(const Matriz& A, const Matriz& B, double eps = 1e-6) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (std::fabs(A[i][j] - B[i][j]) > eps) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    int n = 4;

    Matriz A = crear_matriz(n);
    Matriz B = crear_matriz(n);

    fill_integers(A, 1, 9);
    fill_integers(B, 1, 9);

    Eigen::MatrixXd eigen_A(n, n);
    Eigen::MatrixXd eigen_B(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            eigen_A(i, j) = A[i][j];
            eigen_B(i, j) = B[i][j];
        }
    }

    std::cout << "==============================" << std::endl;
    std::cout << " MATRIZ A" << std::endl;
    std::cout << "==============================" << std::endl;
    imprimir_matriz(A);

    std::cout << std::endl;

    std::cout << "==============================" << std::endl;
    std::cout << " MATRIZ B" << std::endl;
    std::cout << "==============================" << std::endl;
    imprimir_matriz(B);


    Eigen::MatrixXd eigen_C = eigen_A * eigen_B;
    Matriz resultado_clasico = multiplicacion_clasica(A, B);
    Matriz resultado_strassen = multiplicacion_strassen(A, B);
    Matriz resultado_hibrido = multiplicacion_hibrida(A, B, 2);


    // Transformar eigen_C a Matriz para comparación
    Matriz resultado_real(n, std::vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado_real[i][j] = eigen_C(i, j);
        }
    }

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << " RESULTADO REAL (BIBLIOTECA EIGEN)" << std::endl;
    std::cout << "==============================" << std::endl;
    imprimir_matriz(resultado_real);

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << " RESULTADO CLASICO" << std::endl;
    std::cout << "==============================" << std::endl;
    imprimir_matriz(resultado_clasico);

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << " RESULTADO STRASSEN" << std::endl;
    std::cout << "==============================" << std::endl;
    imprimir_matriz(resultado_strassen);

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << " RESULTADO HIBRIDO" << std::endl;
    std::cout << "==============================" << std::endl;
    imprimir_matriz(resultado_hibrido);

    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << " VERIFICACION DE CORRECTITUD" << std::endl;
    std::cout << "==============================" << std::endl;

    if (matrices_iguales(resultado_real, resultado_clasico)) {
        std::cout << "[OK] CLASICO ES CORRECTO" << std::endl;
    } else {
        std::cout << "[ERROR] CLASICO NO COINCIDE" << std::endl;
    }

    if (matrices_iguales(resultado_real, resultado_strassen)) {
        std::cout << "[OK] STRASSEN ES CORRECTO" << std::endl;
    } else {
        std::cout << "[ERROR] STRASSEN NO COINCIDE" << std::endl;
    }

    if (matrices_iguales(resultado_real, resultado_hibrido)) {
        std::cout << "[OK] HIBRIDO ES CORRECTO" << std::endl;
    } else {
        std::cout << "[ERROR] HIBRIDO NO COINCIDE" << std::endl;
    }

    return 0;
}
