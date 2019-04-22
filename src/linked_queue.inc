// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void LinkedQueue<T>::clear() {
    while (!empty())
        dequeue();
}

template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    auto nodenew = new Node(data, tail);
    if (empty())
        head = nodenew;
    tail = nodenew;
    size_++;
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else if (size() == 1) {
        auto nodepopped = head;
        T datapopped = head->data();
        head = nullptr;
        tail = nullptr;
        delete nodepopped;
        size_--;
        return datapopped;
    } else {
        auto nodepopped = head;
        T datapopped = head->data();
        auto it = tail;
        for (auto i = 1u; i < size() - 1; i++)
            it = it->next();
        it->next(nullptr);
        head = it;
        delete nodepopped;
        size_--;
        return datapopped;
    }
}

template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return tail->data();
    }
}

template<typename T>
bool LinkedQueue<T>::empty() const {
    return size() == 0;
}

template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_;
}
