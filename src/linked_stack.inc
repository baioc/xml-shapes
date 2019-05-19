/*!
 * @file linked_stack.inc
 * @author Alek Frohlich, Gabriel B. Sant'Anna
 * @brief Implementações da Pilha Encadeada.
 * @version 1.0
 * @date 2019-05-19
 *
 * @copyright Copyright (c) 2019
 */


template<typename T>
LinkedStack<T>::~LinkedStack() {
	clear();
}

template<typename T>
void LinkedStack<T>::clear() {
	while (!empty())
		pop();
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
	top_ = new Node(data, empty() ? nullptr : top_);
	++size_;
}

template<typename T>
T LinkedStack<T>::pop() {
	if (empty())
		throw std::out_of_range("Pilha vazia, underflow.");

	auto nodepopped = top_;
	const T datapopped = top_->data();

	if (size() == 1)
		top_ = nullptr;
	else
		top_ = top_->next();

	delete nodepopped;

	--size_;
	return datapopped;
}

template<typename T>
T& LinkedStack<T>::top() const {
	if (empty())
		throw std::out_of_range("Pilha vazia, nada no topo.");

	return top_->data();
}

template<typename T>
bool LinkedStack<T>::empty() const {
	return size_ == 0;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
	return size_;
}
