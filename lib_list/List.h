#pragma once
#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T value_, Node<T>* prev_ = nullptr, Node<T>* next_ = nullptr)
        : value(value_), prev(prev_), next(next_) {
    }
};

template <class T>
class List {
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    class Iterator {
        Node<T>* current;

    public:
        Iterator() : current(nullptr) {}
        Iterator(Node<T>* node) : current(node) {}

        Iterator& operator=(const Iterator& other) {
            current = other.current;
            return *this;
        }

        T& operator*() {
            return current->value;
        }

        const T& operator*() const {
            return current->value;
        }

        //  (++it)
        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        //  (it++)
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            if (current != nullptr) {
                current = current->prev;
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Node<T>* get_node() const { return current; }
    };

    class ConstIterator {
        const Node<T>* current;

    public:
        ConstIterator() : current(nullptr) {}
        ConstIterator(const Node<T>* node) : current(node) {}
        ConstIterator(const Iterator& it) : current(it.get_node()) {}

        const T& operator*() const {
            return current->value;
        }

        ConstIterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        ConstIterator& operator--() {
            if (current != nullptr) {
                current = current->prev;
            }
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }
    };

    List() : _head(nullptr), _tail(nullptr), _count(0) {}

    List(const List& other) : _head(nullptr), _tail(nullptr), _count(0) {
        Node<T>* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    ~List() {
        clear();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();

            Node<T>* current = other._head;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }

    ConstIterator begin() const { return ConstIterator(_head); }
    ConstIterator end() const { return ConstIterator(nullptr); }

    void push_front(const T& val) {
        Node<T>* new_node = new Node<T>(val, nullptr, _head);

        if (_head != nullptr) {
            _head->prev = new_node;
        }

        _head = new_node;

        if (_tail == nullptr) {
            _tail = new_node;
        }

        _count++;
    }

    void push_back(const T& val) {
        Node<T>* new_node = new Node<T>(val, _tail, nullptr);

        if (_tail != nullptr) {
            _tail->next = new_node;
        }

        _tail = new_node;

        if (_head == nullptr) {
            _head = new_node;
        }

        _count++;
    }

    void insert(const Iterator& position, const T& val) {
        if (position == begin()) {
            push_front(val);
            return;
        }

        if (position == end()) {
            push_back(val);
            return;
        }

        Node<T>* current_node = position.get_node();
        Node<T>* prev_node = current_node->prev;

        Node<T>* new_node = new Node<T>(val, prev_node, current_node);

        prev_node->next = new_node;
        current_node->prev = new_node;

        _count++;
    }

    void pop_front() {
        if (is_empty()) throw std::logic_error("List is empty");

        Node<T>* temp = _head;
        _head = _head->next;

        if (_head != nullptr) {
            _head->prev = nullptr;
        }
        else {
            _tail = nullptr;
        }

        delete temp;
        _count--;
    }

    void pop_back() {
        if (is_empty()) throw std::logic_error("List is empty");

        Node<T>* temp = _tail;
        _tail = _tail->prev;

        if (_tail != nullptr) {
            _tail->next = nullptr;
        }
        else {
            _head = nullptr;
        }

        delete temp;
        _count--;
    }

    void erase(const Iterator& position) {
        if (position == end()) return;

        Node<T>* node_to_delete = position.get_node();

        if (node_to_delete == _head) {
            pop_front();
            return;
        }

        if (node_to_delete == _tail) {
            pop_back();
            return;
        }

        Node<T>* prev_node = node_to_delete->prev;
        Node<T>* next_node = node_to_delete->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete node_to_delete;
        _count--;
    }

    T& front() {
        if (is_empty()) throw std::logic_error("List is empty");
        return _head->value;
    }

    const T& front() const {
        if (is_empty()) throw std::logic_error("List is empty");
        return _head->value;
    }

    T& back() {
        if (is_empty()) throw std::logic_error("List is empty");
        return _tail->value;
    }

    const T& back() const {
        if (is_empty()) throw std::logic_error("List is empty");
        return _tail->value;
    }

    bool is_empty() const {
        return _head == nullptr;
    }

    int size() const {
        return _count;
    }

    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

    Iterator find(const T& val) {
        Node<T>* current = _head;
        while (current != nullptr) {
            if (current->value == val) {
                return Iterator(current);
            }
            current = current->next;
        }
        return end();
    }
};

template <class T>
class TVector {
private:
    List<T> _list;

public:
    using Iterator = typename List<T>::Iterator;
    using ConstIterator = typename List<T>::ConstIterator;

    TVector() = default;

    TVector(int size) {
        for (int i = 0; i < size; i++) {
            push_back(T());
        }
    }

    TVector(std::initializer_list<T> data) {
        for (const auto& item : data) {
            push_back(item);
        }
    }

    TVector(const TVector& other) : _list(other._list) {}

    ~TVector() = default;

    TVector& operator=(const TVector& other) {
        if (this != &other) {
            _list = other._list;
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size()) {
            throw std::logic_error("TVector index out of range");
        }

        auto it = _list.begin();
        for (int i = 0; i < index; i++) {
            ++it;
        }
        return *it;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size()) {
            throw std::logic_error("TVector index out of range");
        }

        auto it = _list.begin();
        for (int i = 0; i < index; i++) {
            ++it;
        }
        return *it;
    }

    void push_back(const T& value) {
        _list.push_back(value);
    }

    void insert(int index, const T& value) {
        if (index < 0 || index > size()) {
            throw std::logic_error("TVector index out of range");
        }

        if (index == 0) {
            _list.push_front(value);
        }
        else if (index == size()) {
            _list.push_back(value);
        }
        else {
            auto it = _list.begin();
            for (int i = 0; i < index; i++) {
                ++it;
            }
            _list.insert(it, value);
        }
    }

    void erase(int index) {
        if (index < 0 || index >= size()) {
            throw std::logic_error("TVector index out of range");
        }

        auto it = _list.begin();
        for (int i = 0; i < index; i++) {
            ++it;
        }
        _list.erase(it);
    }

    void pop_back() {
        if (!_list.is_empty()) {
            _list.pop_back();
        }
    }

    Iterator begin() { return _list.begin(); }
    Iterator end() { return _list.end(); }

    ConstIterator begin() const { return _list.begin(); }
    ConstIterator end() const { return _list.end(); }

    int size() const { return _list.size(); }
    int capacity() const { return size(); }

    bool empty() const { return _list.is_empty(); }

    T& front() { return _list.front(); }
    const T& front() const { return _list.front(); }

    T& back() { return _list.back(); }
    const T& back() const { return _list.back(); }

    Iterator find(const T& value) {
        return _list.find(value);
    }

    void clear() {
        _list.clear();
    }

    T* data() { return nullptr; }
    const T* data() const { return nullptr; }
};