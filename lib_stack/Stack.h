#pragma once
#include "List.h"
#include <stdexcept>

template <class T>
class Stack {
private:
    List<T> _list;

public:
    Stack() = default;

    void push(const T& val) {
        _list.push_back(val);
    }

    T pop() {
        if (_list.is_empty()) {
            throw std::logic_error("Stack is empty");
        }
        T value = _list.back();
        _list.pop_back();
        return value;
    }

    T& top() {
        if (_list.is_empty()) {
            throw std::logic_error("Stack is empty");
        }
        return _list.back();
    }

    bool is_empty() const {
        return _list.is_empty();
    }

    int size() const {
        return _list.size();
    }

    void clear() {
        _list.clear();
    }

    bool is_full() const {
        return false;
    }
};