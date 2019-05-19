// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
/* libraries */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cassert>
#include <utility>

/* our includes */
#include "xml.h"
#include "linked_queue.h"


//! Inicializa uma matriz como um array de height ponteiros para arrays com width ints.
//! Deve ser destruido com matrix_destroy() para liberar a memoria.
static int** matrix_init(int height, int width);

//! Inicializa uma matriz a partir da string que representa seus valores.
//! Deve ser destruido com matrix_destroy() para liberar a memoria.
static int** matrix_init(int height, int width, const std::string& data);

//! Utilizado para liberar a memoria alocada por matrix_init().
static void matrix_destroy(int** M, int height);

//! Calcula o numero de componentes conexos na matriz usando vizinhanca-4.
static int count_shapes(int** E, int height, int width);

int main() {
	using namespace std;
	using namespace xml;

	// le o nome do arquivo
	char xmlfilename[100];
	cin.getline(xmlfilename, 100);

	// abre o arquivo
	ifstream file{xmlfilename};
	if (!file.is_open())
		return 1;

	// bufferiza em uma string
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	auto xml = buffer.str();

	// valida o XML
	if (!balanced(xml)) {
		cout << "error\n";
		return -1;
	}

	// para cada imagem no arquivo
	size_t from{0};
	while (from < xml.length()) {
		// extrai uma imagem com atributos
		const auto img = extract(xml, "<img>", "</img>", from);
		if (from == string::npos)
			break;

		// extrai atributos
		const auto name = extract(img, "<name>", "</name>");
		const auto height = stoi(extract(img, "<height>", "</height>"));
		const auto width = stoi(extract(img, "<width>", "</width>"));
		if (height <= 0 || width <= 0)
			return -2;

		// processamento da imagem propriamente dita
		auto frame = matrix_init(height, width, extract(img, "<data>", "</data>"));
		cout << name << ' ' << count_shapes(frame, height, width) << '\n';
		matrix_destroy(frame, height);
	}

	return 0;
}


static int count_shapes(int** E, int height, int width) {
	structures::LinkedQueue<std::pair<int,int>> paths;
	int shapes = 1;
	auto R = matrix_init(height, width);

	// para cada pixel na matriz de entrada
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			// caso ele nao tenha sido rotulado e for diferente de zero
			// entao temos um novo componente conexo
			if (!R[i][j] && E[i][j]) {
				// rotula o pixel e o coloca na fila de processamento
				R[i][j] = shapes;
				paths.enqueue({j,i}); // (x,y)

				// processa cada pixel conexo aos que estao na fila
				while (!paths.empty()) {
					const auto pos = paths.dequeue();
					const auto x = pos.first;
					const auto y = pos.second;

					// repete para a vizinhanca-4, quando existir, for
					// diferente de zero e ainda nao tiver sido processada
					if (x > 0 && !R[y][x-1] && E[y][x-1]) {
						R[y][x-1] = shapes;
						paths.enqueue({x-1,y});
					}
					if (x + 1 < width && !R[y][x+1] && E[y][x+1]) {
						R[y][x+1] = shapes;
						paths.enqueue({x+1,y});
					}
					if (y > 0 && !R[y-1][x] && E[y-1][x]) {
						R[y-1][x] = shapes;
						paths.enqueue({x,y-1});
					}
					if (y + 1 < height && !R[y+1][x] && E[y+1][x]) {
						R[y+1][x] = shapes;
						paths.enqueue({x,y+1});
					}
				}

				shapes++;
			}
		}
	}

	matrix_destroy(R, height);
	return shapes-1; // retorna o ultimo rotulo efetivamente atribuido
}


static int** matrix_init(int height, int width) {
	assert(height > 0);
	assert(width > 0);
	int** M = new int*[height];
	for (int i = 0; i < height; ++i) {
		M[i] = new int[width];
		for (int j = 0; j < width; ++j)
			M[i][j] = 0;
	}
	return M;
}

static void matrix_destroy(int** M, int height) {
	for (int i = 0; i < height; ++i)
		delete[] M[i];
	delete[] M;
}

static int** matrix_init(int height, int width, const std::string& data) {
	auto img = matrix_init(height, width);

	int i = 0, j = 0;
	for (const auto& c : data) {
		// ignorar whitespace
		if (std::isspace(c))
			continue;

		// preenche a matriz
		img[i][j] = c - '0'; // conversao de char para int

		// confere se chegou ao fim de uma linha
		if (++j >= width) {
			j = 0;
			// sai do loop se chegou na altura desejada
			if (++i >= height)
				break;
		}
	}

	return img;
}
