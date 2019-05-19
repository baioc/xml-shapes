// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
/* libraries */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cassert>

/* our includes */
#include "xml.h"


//! Inicializa uma matriz como um array de height ponteiros para arrays com width ints.
//! Deve ser destruido com destroy_matrix() para liberar a memoria.
static int** init_matrix(int height, int width);

//! Inicializa uma matriz a partir da string que representa seus valores.
//! Deve ser destruido com destroy_matrix() para liberar a memoria.
static int** init_matrix(int height, int width, const std::string& data);

//! Utilizado para liberar a memoria alocada por init_matrix().
static void destroy_matrix(int** img, int height);

//! Calcula o numero de componentes conexos na matriz usando vizinhanca-4.
static int count_shapes(int** img, int height, int width);

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
		auto frame = init_matrix(height, width, extract(img, "<data>", "</data>"));
		cout << name << ' ' << count_shapes(frame, height, width) << '\n';
		#ifdef DEBUG
			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; ++j) {
					cout << frame[i][j];
				}
				cout << '\n';
			}
		#endif  // DEBUG
		destroy_matrix(frame, height);
	}

	return 0;
}


static int count_shapes(int** img, int height, int width) {
	// @TODO: aplicar o algoritmo de busca de formas na matriz
	return -1;
}


static int** init_matrix(int height, int width) {
	assert(width > 0);
	assert(height > 0);
	int** matrix = new int*[height];
	for (int i = 0; i < height; ++i) {
		matrix[i] = new int[width];
		for (int j = 0; j < width; ++j)
			matrix[i][j] = 0;
	}
	return matrix;
}

static void destroy_matrix(int** img, int height) {
	for (int i = 0; i < height; ++i)
		delete[] img[i];
	delete[] img;
}

static int** init_matrix(int height, int width, const std::string& data) {
	auto img = init_matrix(height, width);

	int i = 0, j = 0;
	for (const auto& c : data) {
		// ignorar whitespace
		if (std::isspace(c))
			continue;

		// preenche a matriz
		img[i][j] = c - '0'; // conversao de char ASCII para int

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
