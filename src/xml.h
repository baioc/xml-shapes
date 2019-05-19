/*!
 * @file xml.h
 * @author Alek Frohlich, Gabriel B. Sant'Anna
 * @brief Declarações das funções de processamento de XML.
 * @version 1.0
 * @date 2019-05-19
 *
 * @copyright Copyright (c) 2019
 */

#ifndef XML_H
#define XML_H

#include <string>
#include <cstddef>


//! Utilitários para processamento de XML.
namespace xml {

/*!
 * @brief Confere a validez da estrutura do XML contido na string.
 *
 * A validação consiste em verificar se as tags estão balanceadas, ou seja, se
 * para cada tag fechada houve seu par de abertura como última tag processada; e
 * se todas as tags abertas foram devidamente fechadas.
 * Para tal, este algoritmo utiliza uma pilha (LIFO) de tamanho dinâmico.
 *
 * @param xml String contendo o XML.
 * @return true Tags estão balanceadas.
 * @return false Tags não estão balanceadas.
 */
bool balanced(const std::string& xml);

/*!
 * @brief Extrai, a partir de uma string original, a substring que existir entre
 * o primeiro par de delimitadores encontrados a partir de uma dada posição.
 *
 * @param origin String original.
 * @param open Delimitador de abertura.
 * @param close Delimitador de fechamento.
 * @param from Índice por onde iniciar a busca na string original, este será
 * alterado para a posição após o final do delimitador de fechamento encontrado.
 * Se nada for encontrado, recebe o valor de `std::string::npos`.
 * @return std::string String extraída (sem os delimitadores), vazia quando
 * nada for encontrado.
 */
std::string extract(const std::string& origin,
                    const std::string& open, const std::string& close,
                    std::size_t& from);

/*!
 * @brief Extrai, a partir de uma string original, a substring que existir entre
 * o primeiro par de delimitadores encontrados.
 *
 * @param origin String original.
 * @param open Delimitador de abertura.
 * @param close Delimitador de fechamento.
 * @return std::string String extraída (sem os delimitadores), vazia quando
 * nada for encontrado.
 */
std::string extract(const std::string& origin,
                    const std::string& open, const std::string& close);

}  // namespace xml

#endif  // XML_H
