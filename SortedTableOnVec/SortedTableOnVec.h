#pragma once
#include "ITable.h"
#include <algorithm>

template <typename Tkey, typename Tvalue>
class SortedTableOnVec : public ITable<Tkey, Tvalue> {
    TVector<std::pair<Tkey, Tvalue>> _rows;

    int binary_search(const Tkey& key) const {
        int left = 0;
        int right = _rows.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (_rows[mid].first == key) {
                return mid;
            }
            if (_rows[mid].first < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -left - 1;
    }

    int find_insert_position(const Tkey& key) const {
        int left = 0;
        int right = _rows.size();

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (_rows[mid].first < key) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }

public:
    SortedTableOnVec() = default;
    ~SortedTableOnVec() = default;

    void insert(const Tkey& key, const Tvalue& value) override;
    void replace(const Tkey& key, const Tvalue& value) override;
    Tvalue find(const Tkey key) const override;
    void erase(const Tkey& key) override;
    std::ostream& print(std::ostream& out) const noexcept override;
    bool is_empty() const noexcept override;
    bool consist(const Tkey& key) const noexcept override;

    int size() const { return _rows.size(); }
};

template <typename Tkey, typename Tvalue>
void SortedTableOnVec<Tkey, Tvalue>::insert(const Tkey& key, const Tvalue& value) {
    int pos = binary_search(key);
    if (pos >= 0) {
        throw std::logic_error("Key already exists!");
    }

    int insert_pos = find_insert_position(key);
    _rows.insert(insert_pos, std::make_pair(key, value));
}

template <typename Tkey, typename Tvalue>
void SortedTableOnVec<Tkey, Tvalue>::replace(const Tkey& key, const Tvalue& value) {
    int pos = binary_search(key);
    if (pos >= 0) {
        _rows[pos].second = value;
    }
    else {
        throw std::logic_error("Key not found for replacement!");
    }
}

template <typename Tkey, typename Tvalue>
Tvalue SortedTableOnVec<Tkey, Tvalue>::find(const Tkey key) const {
    int pos = binary_search(key);
    if (pos >= 0) {
        return _rows[pos].second;
    }
    throw std::logic_error("Key not found!");
}

template <typename Tkey, typename Tvalue>
void SortedTableOnVec<Tkey, Tvalue>::erase(const Tkey& key) {
    int pos = binary_search(key);
    if (pos >= 0) {
        _rows.erase(pos);
    }
    else {
        throw std::logic_error("Key not found for erasure!");
    }
}

template <typename Tkey, typename Tvalue>
std::ostream& SortedTableOnVec<Tkey, Tvalue>::print(std::ostream& out) const noexcept{
    for (int i = 0; i < _rows.size(); i++) {
        out << _rows[i].first << " : " << _rows[i].second << std::endl;
    }
    return out;
}

template <typename Tkey, typename Tvalue>
bool SortedTableOnVec<Tkey, Tvalue>::is_empty() const noexcept {
    return _rows.size() == 0;
}

template <typename Tkey, typename Tvalue>
bool SortedTableOnVec<Tkey, Tvalue>::consist(const Tkey& key) const noexcept {
    return binary_search(key) >= 0;
}