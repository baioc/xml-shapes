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
#include "concomps.h"

//! Inicializa uma matriz como um array de height ponteiros para arrays com width ints.
//! Deve ser destruido com destroy_matrix() para liberar a memoria.
static int** init_matrix(const std::string& data, int width, int height);

//! Utilizado para liberar a memoria alocada por init_matrix().
static void destroy_matrix(int** img, int height);

int main() {
	using namespace std;
	using namespace xml;
    using namespace concomps;

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
		auto frame = init_matrix(extract(img, "<data>", "</data>"), height, width);
		cout << name << ' ' << count_shapes(frame, width, height) << '\n';
		destroy_matrix(frame, width);
	}

	return 0;
}

static int** init_matrix(const std::string& data, int width, int height) {
	assert(width > 0);
	assert(height > 0);
	using namespace std;

	// alloc()a memoria para a matriz
	int** img = new int*[height];
	for (int i = 0; i < height; ++i) {
		img[i] = new int[width];
		for (int j = 0; j < width; ++j)
			img[i][j] = 0;
	}

	int i = 0, j = 0;
	for (const auto& c : data) {
		// ignorar whitespace
		if (isspace(c))
			continue;

		// preenche a matriz
		img[i][j] = c - '0';

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

static void destroy_matrix(int** img, int width) {
	for (int i = 0; i < width; ++i)
		delete[] img[i];
	delete[] img;
}

