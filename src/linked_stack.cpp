#include "linked_stack.h"

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
    delete top_;
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty())
        pop();
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    if (empty()) {
        top_ = new Node(data, nullptr);
    } else {
        top_ = new Node(data, top_);
    }   
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    auto nodepopped = top_;
    if (empty())
        throw std::out_of_range("pilha vazia");
    T datapopped = top_->data();
    if (size() == 1) {
        top_ = nullptr;
    } else {
        top_ = top_->next();
    }   
    delete nodepopped;
    size_--;
    return datapopped;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    } else {
        return top_->data();
    }   
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}

