#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#define STEP_OF_CAPACITY 15


template <typename Tkey, typename Tvalue>

class ITable {

public:

	virtual void insert(const Tkey& key, const Tvalue& value) = 0;
    virtual void replace(const Tkey& key, const Tvalue& value) = 0;
	virtual Tvalue find(const Tkey key) const = 0;
	virtual void erase(const Tkey& key) = 0;
	virtual std::ostream& print(std::ostream& out) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const Tkey& key) const noexcept = 0;
	~ITable(){}

};


















template <class T>
class TVector {
protected:
    T* _data;
    int _size;
    int _capacity;

public:
    TVector();
    TVector(int size);
    TVector(T* data, size_t size);
    TVector(std::initializer_list<T> data);
    TVector(const TVector& other);
    ~TVector();

    inline T* data() const noexcept;
    inline int size() const noexcept;
    inline int capacity() const noexcept;
    const T& operator[](int index) const;
    T& operator[](int index);
    void push_back(const T& value);
    void insert(int index, const T& value);
    void erase(int index);
    void pop_back();
    T begin();
    T end();
    inline bool is_empty() const noexcept;
};

template <class T>
TVector<T>::TVector() : _data(nullptr), _size(0), _capacity(0) {}

template <class T>
TVector<T>::TVector(int size) : _data(new T[size]()), _size(size), _capacity(size) {}

template <class T>
TVector<T>::TVector(T* data, size_t size) {
    this->_data = new T[size];
    this->_size = size;
    this->_capacity = size;
    for (int i = 0; i < size; i++) {
        this->_data[i] = data[i];
    }
}
template <class T>
T TVector<T>::begin() {

    return _data[0]

}
template <class T>
T TVector<T>::end() {

    return _data[-1]

}

template <class T>
TVector<T>::TVector(std::initializer_list<T> data) {
    _size = data.size();
    _capacity = ((_size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY;
    _data = new T[_capacity]();
    int i = 0;
    for (const auto& item : data) {
        _data[i++] = item;
    }
}

template <class T>
TVector<T>::TVector(const TVector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template <class T>
TVector<T>::~TVector() {
    delete[] _data;
}

template <class T>
inline T* TVector<T>::data() const noexcept {
    return _data;
}

template <class T>
inline int TVector<T>::size() const noexcept {
    return _size;
}

template <class T>
inline int TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <class T>
const T& TVector<T>::operator[](int index) const {
    return _data[index];
}

template <class T>
T& TVector<T>::operator[](int index) {
    return _data[index];
}


template <class T>
void TVector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        int new_capacity = _capacity + STEP_OF_CAPACITY;
        T* new_data = new T[new_capacity]();
        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }
    _data[_size++] = value;
}

template <class T>
void TVector<T>::insert(int index, const T& value) {
    if (index < 0 || index > _size) {
        throw std::out_of_range("Index out of range");
    }

    if (_size >= _capacity) {
        int new_capacity = _capacity + STEP_OF_CAPACITY;
        T* new_data = new T[new_capacity]();
        for (int i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    for (int i = _size; i > index; i--) {
        _data[i] = _data[i - 1];
    }

    _data[index] = value;
    _size++;
}

template <class T>
void TVector<T>::erase(int index) {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("Index out of range");
    }

    for (int i = index; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }

    _size--;
}

template <class T>
void TVector<T>::pop_back() {
    if (_size > 0) {
        _size--;
    }
}

template <class T>
inline bool TVector<T>::is_empty() const noexcept {

    return _size == 0;

}