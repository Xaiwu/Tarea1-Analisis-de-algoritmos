#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <iostream>
#include <random>
#include <string>
#include <vector>

using Matriz = std::vector<std::vector<double>>;

Matriz crear_matriz(int n);

// Funciones de llenado
void fill_random(Matriz& M);
void fill_integers(Matriz& M, int min = 0, int max = 100);
void fill_identity(Matriz& M);
void fill_sparse(Matriz& M, double probability = 0.1);

Matriz sumar(const Matriz& A, const Matriz& B);
Matriz restar(const Matriz& A, const Matriz& B);

void preparar_experimento(const std::string& tipo, Matriz& A, Matriz& B);

#endif