#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>

using Matriz = std::vector<std::vector<double>>;

Matriz crear_matriz(int n);

void fill_random(Matriz& M, int n);
void fill_integers(Matriz& M, int n, int min = 0, int max = 100);
void fill_identity(Matriz& M, int n);
void fill_sparse(Matriz& M, int n, double probability = 0.1);

Matriz sumar(const Matriz& A, const Matriz& B, int n);
Matriz restar(const Matriz& A, const Matriz& B, int n);

#endif