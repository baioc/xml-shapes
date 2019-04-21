//! Copyright [2019] <Alek Frohlich>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Pilha Ecandeada
class LinkedStack {
 public:
    //! Construtor padrao.
    LinkedStack() = default;

    //! Destrutor.
    ~LinkedStack();

    //! Empilha.
    void push(const T& data);

    //! Desempilha.
    T pop();

    //! Acessa o topo da Pilha.
    T& top() const;

    //! Confere se a Pilha esta vazia.
    bool empty() const;

    //! Retorna o tamanho da Pilha.
    std::size_t size() const;

    //! Limpa a Pilha.
    void clear();

 private:
	// Elemento da Lista Encadeada
    class Node {
     public:
        explicit Node(const T& data) : data_{data} { }

        Node(const T& data, Node* next) : data_{data}, next_{next} { }

        T& data() {
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};  //  nodo-topo
    std::size_t size_{0u};  //  tamanho
};

}  // namespace structures

#endif

