/*!
 * @file matrix.h
 * @author Alek Frohlich, Gabriel B. Sant'Anna
 * @brief Declarações das funções de processamento de matrizes.
 * @version 1.0
 * @date 2019-05-19
 *
 * @copyright Copyright (c) 2019
 */

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H


//! Código de natureza matemática.
namespace math {

/*!
 * @brief Inicializa uma matriz com as dimensões especificadas.
 *
 * A matriz é dada na forma de um array de arrays onde todos os elementos são
 * inicializados com zero, uma matriz nula.
 *
 * @param height Número de linhas da matriz.
 * @param width Número de colunas da matriz.
 * @return int** Matriz gerada. Deve ser destruído com matrix_destroy() para liberar a memória alocada.
 */
int** matrix_init(int height, int width);

/*!
 * @brief Destroi uma matriz e libera a memória que ocupava.
 *
 * @param M Matriz anteriormente inicializada por matrix_init().
 * @param height Número de linhas da matriz. Deve ser o mesmo valor usado em
 * sua inicialização.
 */
void matrix_destroy(int** M, int height);

/*!
 * @brief Calcula o número de componentes conexos na matriz usando vizinhança-4.
 *
 * Utiliza a técnica de rotulação de formas, para tal criando uma matriz temporária
 * do mesmo tamanho da de entrada: este algoritmo utiliza memória na ordem O(w*h).
 *
 * Cada "pixel" é processado em uma fila (FIFO) de tamanho dinâmico, assim como
 * seus vizinhos e assim por diante ate percorrer todos os caminhos do componente.
 *
 * @param E Matriz de entrada.
 * @param height Número de linhas da matriz.
 * @param width Número de colunas da matriz.
 * @return int Número de componentes conexos (formas) encontrados. Zero implica
 * que a matriz é nula/vazia.
 */
int count_shapes(int** E, int height, int width);

}  // namespace math

#endif  // MATH_MATRIX_H
