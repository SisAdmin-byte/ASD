#pragma once

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


        Iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator operator--(int) {
            Iterator temp = (*this);
            (*this)--;
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
        if (is_empty()) throw "List is empty";

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
        if (is_empty()) throw "List is empty";

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
        if (is_empty()) throw "List is empty";
        return _head->value;
    }

    const T& front() const {
        if (is_empty()) throw "List is empty";
        return _head->value;
    }

    T& back() {
        if (is_empty()) throw "List is empty";
        return _tail->value;
    }

    const T& back() const {
        if (is_empty()) throw "List is empty";
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