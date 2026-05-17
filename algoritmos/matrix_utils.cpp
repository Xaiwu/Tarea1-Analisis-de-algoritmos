#include <random>
#include <vector>

using Matriz = std::vector<std::vector<double>>;

// Crea matriz n x n
Matriz crear_matriz(int n) { return Matriz(n, std::vector<double>(n, 0.0)); }

// Llena la matriz con números enteros aleatorios en un rango [min, max]
void fill_integers(Matriz& M, int n, int min = 0, int max = 100) {
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
void fill_random(Matriz& M, int n) {
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
void fill_identity(Matriz& M, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j) {
                M[i][j] = 1.0;
            } else {
                M[i][j] = 0.0;
            }
}
// Llena la matriz de ceros y unos pocos valores distintos de cero
void fill_sparse(Matriz& M, int n, double probability = 0.1) {
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
Matriz sumar(Matriz& A, Matriz& B, int n) {
    Matriz res(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = A[i][j] + B[i][j];
        }
    }
    return res;
}

Matriz restar(Matriz& A, Matriz& B, int n) {
    Matriz res(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = A[i][j] - B[i][j];
        }
    }
    return res;
}
