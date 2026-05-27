#pragma once
#include "TVector.h"
#include <stdexcept>
#include <algorithm>

template <typename T>
class MinHeap {
private:
    TVector<T> _data;

    inline int parent(int i) const { return (i - 1) / 2; }
    inline int left(int i) const { return 2 * i + 1; }
    inline int right(int i) const { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && _data[i] < _data[parent(i)]) {
            std::swap(_data[i], _data[parent(i)]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int minIndex = i;
        int l = left(i);
        int r = right(i);

        if (l < _data.size() && _data[l] < _data[minIndex])
            minIndex = l;
        if (r < _data.size() && _data[r] < _data[minIndex])
            minIndex = r;

        if (minIndex != i) {
            std::swap(_data[i], _data[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    MinHeap() = default;

    void insert(const T& value) {
        _data.push_back(value);
        siftUp(_data.size() - 1);
    }

    T extractMin() {
        if (_data.is_empty()) {
            throw std::logic_error("Heap is empty");
        }
        T root = _data[0];
        _data[0] = _data[_data.size() - 1];
        _data.pop_back();

        if (!_data.is_empty()) {
            siftDown(0);
        }
        return root;
    }


    bool is_empty() const {
        return _data.is_empty();
    }

    size_t size() const {
        return _data.size();
    }

};

template <typename T>
void heapSort(TVector<T>& arr) {
    if (arr.size() <= 1) return;

    MinHeap<T> heap;

    for (int i = 0; i < arr.size(); ++i) {
        heap.insert(arr[i]);
    }

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = heap.extractMin();
    }
}