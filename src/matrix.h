// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

namespace math {

//! Inicializa uma matriz como um array de height ponteiros para arrays com width ints.
//! Deve ser destruido com matrix_destroy() para liberar a memoria.
int** matrix_init(int height, int width);

//! Utilizado para liberar a memoria alocada por matrix_init().
void matrix_destroy(int** M, int height);

//! Calcula o numero de componentes conexos na matriz usando vizinhanca-4.
int count_shapes(int** E, int height, int width);

}  // namespace math

#endif  // MATH_MATRIX_H
