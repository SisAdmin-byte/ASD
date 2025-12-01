#pragma once
#include <iostream>
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
    _data[++_top] = val;

}

template <class T>
T Stack<T>::pop() {

    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    --_top;

}
template <class T>
inline T Stack<T>::top() {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    return _data[_top];
}

template <class T>
void Stack<T>::clear() {

    _top = 0;

}