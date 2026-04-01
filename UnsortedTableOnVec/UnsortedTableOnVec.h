#pragma once
#include "ITable.h"
#include <utility>
#include <stdexcept>

template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public ITable<Tkey, Tvalue> {
    TVector<std::pair<Tkey, Tvalue>> _rows;

public:
    UnsortedTableOnVec() = default;
    ~UnsortedTableOnVec() = default;

    void insert(const Tkey& key, const Tvalue& value) override;
    void replace(const Tkey& key, const Tvalue& value) override;
    Tvalue find(const Tkey& key) const override;
    void erase(const Tkey& key) override;
    std::ostream& print(std::ostream& out) const override;
    bool is_empty() const noexcept override;
    bool consist(const Tkey& key) const noexcept override;

    int size() const { return _rows.size(); }
};

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::insert(const Tkey& key, const Tvalue& value) {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            throw std::logic_error("Key already exists!");
        }
    }
    _rows.push_back(std::make_pair(key, value));
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::replace(const Tkey& key, const Tvalue& value) {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            _rows[i].second = value;
            return;
        }
    }
    throw std::logic_error("Key not found for replacement!");
}

template <typename Tkey, typename Tvalue>
Tvalue UnsortedTableOnVec<Tkey, Tvalue>::find(const Tkey& key) const {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::erase(const Tkey& key) {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            _rows.erase(i);
            return;
        }
    }
    throw std::logic_error("Key not found for erasure!");
}

template <typename Tkey, typename Tvalue>
std::ostream& UnsortedTableOnVec<Tkey, Tvalue>::print(std::ostream& out) const {
    for (int i = 0; i < _rows.size(); i++) {
        out << _rows[i].first << " : " << _rows[i].second << std::endl;
    }
    return out;
}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::consist(const Tkey& key) const noexcept {
    for (int i = 0; i < _rows.size(); i++) {
        if (_rows[i].first == key) {
            return true;
        }
    }
    return false;
}