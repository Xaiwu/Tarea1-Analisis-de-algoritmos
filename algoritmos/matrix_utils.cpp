#include "matrix_utils.h"

// Crea matriz n x n
Matriz crear_matriz(int n) { return Matriz(n, std::vector<double>(n, 0.0)); }

// Llena la matriz con números enteros aleatorios en un rango [min, max]
void fill_integers(Matriz& M, int min, int max) {
    int n = M.size();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = dis(gen);
        }
    }
}

// Llena la matriz con valores aleatorios
void fill_random(Matriz& M) {
    int n = M.size();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = dis(gen);
        }
    }
}

// Llena la matriz para formar la identidad I
void fill_identity(Matriz& M) {
    int n = M.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) {
                M[i][j] = 1.0;
            } else {
                M[i][j] = 0.0;
            }
}

// Llena la matriz de ceros y unos pocos valores distintos de cero
void fill_sparse(Matriz& M, double probability) {
    int n = M.size();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double value = dis(gen);
            if (value < probability) {
                M[i][j] = value;
            } else {
                M[i][j] = 0.0;
            }
        }
    }
}

// Suma y Resta
Matriz sumar(const Matriz& A, const Matriz& B) {
    int n = A.size();
    if (B.size() != n) {
        std::cout << "Las matrices deben ser el mismo tamaño." << std::endl;
        std::exit(1);
    }
    Matriz res(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = A[i][j] + B[i][j];
        }
    }
    return res;
}

Matriz restar(const Matriz& A, const Matriz& B) {
    int n = A.size();
    if (B.size() != n) {
        std::cout << "Las matrices deben ser el mismo tamaño." << std::endl;
        std::exit(1);
    }
    Matriz res(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = A[i][j] - B[i][j];
        }
    }
    return res;
}

void preparar_experimento(const std::string& tipo, Matriz& A, Matriz& B) {
    if (tipo == "REALES") {
        fill_random(A);
        fill_random(B);
    } else if (tipo == "ENTEROS") {
        fill_integers(A, 0, 100);
        fill_integers(B, 0, 100);
    } else if (tipo == "IDENTIDAD") {
        fill_random(A);
        fill_identity(B);
    } else if (tipo == "SPARSE") {
        fill_sparse(A, 0.05);
        fill_sparse(B, 0.05);
    } else {
        fill_random(A);
        fill_random(B);
    }
}