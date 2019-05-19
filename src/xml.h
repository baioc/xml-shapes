// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
#ifndef XML_H
#define XML_H

#include <string>
#include <cstddef>


namespace xml {

//! Confere a validez da estrutura do XML contido na string.
bool balanced(const std::string& xml);

/** Extrai substring de uma string entre dois delimitadores encontrados a partir
 *  de uma dada posicao.
 * Retorna a substring extraida (sem delimitadores) e altera a posicao para o
 * final do ultimo delimitador encontrado.
 * Se nao encontrar nada, retorna string vazia e leva a posicao para npos.
 */
std::string extract(const std::string& origin,
                    const std::string& open, const std::string& close,
                    std::size_t& from);

/** Extrai substring de uma string entre dois delimitadores.
 * Retorna a substring extraida (sem delimitadores).
 * Se nao encontrar nada, retorna string vazia.
 */
std::string extract(const std::string& origin,
                    const std::string& open, const std::string& close);

}  // namespace xml

#endif  // XML_H
