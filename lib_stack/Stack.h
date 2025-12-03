#pragma once
#include <iostream>
#include "List.h"
template <class T>
class Stack {

private:

    T* _data;
    int _size, _top;

public:

    Stack(int size);
    Stack();
    void push(const T& val);
    T pop();
    inline T top();
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear();

};

template <class T>
inline bool Stack<T>::is_empty() const noexcept {

    return _top == 0;

}

template <class T>
inline bool Stack<T>::is_full() const noexcept {

    return _top == _size;

}

template <class T>
Stack<T>::Stack(int size) : _data(new T[size]), _size(size), _top(0) {};
template <class T>
Stack<T>::Stack() : _data(nullptr), _size(0), _top(0) {};

template <class T>
void Stack<T>::push(const T& val) {

    if (is_full()) {
        throw std::logic_error("Queue is full");
    }
    _data[_top++] = val;

}

template <class T>
T Stack<T>::pop() {

    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    return _data[--_top];

}
template <class T>
inline T Stack<T>::top() {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    return _data[_top - 1];
}

template <class T>
void Stack<T>::clear() {

    _top = 0;

}


template <class T>
class StackList {
private:
    List<T> _list;

public:
    StackList() = default;

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