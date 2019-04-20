//! Copyright [2019] <Alek Frohlich>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {
//! a
template<typename T>
class LinkedStack {
 public:
    //!  a
    LinkedStack() { }
    //!  a
    ~LinkedStack();
    //!  a
    void clear();  // limpa pilha
    //!  a
    void push(const T& data);  // empilha
    //!  a
    T pop();  // desempilha
    //!  a
    T& top() const;  // dado no topo
    //!  a
    bool empty() const;  // pilha vazia
    //!  a
    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {  // Elemento
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

