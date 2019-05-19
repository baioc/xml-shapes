// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
#include "matrix.h"

#include <cassert>
#include <utility>

#include "linked_queue.h"


namespace math {

int** matrix_init(int height, int width) {
	assert(width > 0);
	int** M = new int*[height];
	for (int i = 0; i < height; ++i) {
		M[i] = new int[width];
		for (int j = 0; j < width; ++j)
			M[i][j] = 0;
	}
	return M;
}

void matrix_destroy(int** M, int height) {
	for (int i = 0; i < height; ++i)
		delete[] M[i];
	delete[] M;
}

int count_shapes(int** E, int height, int width) {
	using pixel = std::pair<int,int>;
	structures::LinkedQueue<pixel> paths;
	int label = 1;
	auto R = matrix_init(height, width);

	// para cada pixel na matriz de entrada
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			// caso ele nao tenha sido rotulado e for diferente de zero
			// entao temos um novo componente conexo
			if (!R[i][j] && E[i][j]) {
				// rotula o pixel e o coloca na fila de processamento
				R[i][j] = label;
				paths.enqueue({j,i});  // (x,y)

				// processa cada pixel conexo aos que estao na fila
				while (!paths.empty()) {
					const auto p = paths.dequeue();
					const auto x = p.first;
					const auto y = p.second;

					// repete para a vizinhanca-4, quando existir, for
					// diferente de zero e ainda nao tiver sido processada
					if (x - 1 >= 0 && !R[y][x-1] && E[y][x-1]) {
						R[y][x-1] = label;
						paths.enqueue({x-1,y});
					}
					if (x + 1 < width && !R[y][x+1] && E[y][x+1]) {
						R[y][x+1] = label;
						paths.enqueue({x+1,y});
					}
					if (y - 1 >= 0 && !R[y-1][x] && E[y-1][x]) {
						R[y-1][x] = label;
						paths.enqueue({x,y-1});
					}
					if (y + 1 < height && !R[y+1][x] && E[y+1][x]) {
						R[y+1][x] = label;
						paths.enqueue({x,y+1});
					}
				}

				label++;
			}
		}
	}

	matrix_destroy(R, height);
	return label - 1;  // retorna o ultimo rotulo efetivamente atribuido
}

}  // namespace math
