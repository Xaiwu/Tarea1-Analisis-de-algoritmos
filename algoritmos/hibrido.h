#ifndef HIBRIDO_H
#define HIBRIDO_H

#include "matrix_utils.h"
#include "clasico.h"
#include "strassen.h"

Matriz multiplicacion_hibrida(const Matriz& A, const Matriz& B, int umbral);

#endif