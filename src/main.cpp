/*!
 * @file main.cpp
 * @author Alek Frohlich, Gabriel B. Sant'Anna
 * @brief Código do programa principal.
 * @version 1.0
 * @date 2019-05-19
 *
 * @copyright Copyright (c) 2019
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

#include "xml.h"
#include "linked_queue.h"
#include "matrix.h"


/*!
 * @brief Inicializa uma matriz de inteiros a partir da string que a representa.
 *
 * @param height Número de linhas da matriz.
 * @param width Múmero de colunas da matriz.
 * @param data String contendo os valores colocados na matriz. Whitespace é ignorado.
 * @return int** Matriz gerada. Deve ser destruido com matrix_destroy() para liberar a memória alocada.
 */
static int** matrix_init(int height, int width, const std::string& data);

/*!
 * @brief Programa principal, realiza a leitura e processamento dos XMLs e conta
 * o número de componentes conexos nas imagens contidas nos mesmos.
 *
 * Resultados de cada imagem são disponibilizados na saída padrão.
 *
 * @return int Algum dos seguintes códigos de erro:
 * 0 quando não houver erros;
 * 1 quando não foi possivel abrir o arquivo lido;
 * -1 quando o XML lido é inválido;
 * -2 quando alguma das imagens apresenta dimensões inválidas.
 */
int main() {
	using namespace std;
	using namespace xml;
	using namespace math;

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


static int** matrix_init(int height, int width, const std::string& data) {
	auto img = math::matrix_init(height, width);

	int i = 0, j = 0;
	for (const auto& c : data) {
		// ignorar whitespace
		if (std::isspace(c))
			continue;

		// preenche a matriz
		img[i][j] = c - '0';  // conversao de char para int

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
