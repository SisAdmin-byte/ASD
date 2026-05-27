#pragma once
#include "ITable.h"
#include "List.h"
#include <string>

template <typename TVal>
class HashTable : public ITable<std::string, TVal> {
private:
    struct HashData {
        std::string key;
        TVal value;
    };

    TVector<List<HashData>> _rows;
    size_t _size = 0;

    size_t h(const std::string& key) const {
        size_t hash = 0;
        for (char c : key) {
            hash = hash * 31 + static_cast<unsigned char>(c);
        }
        return hash % _rows.size();
    }

public:
    HashTable(size_t table_size = 100) : _rows(table_size), _size(0) {}

    void insert(const std::string& key, const TVal& value) override {
        size_t hash_value = h(key);

        for (auto it = _rows[hash_value].begin(); it != _rows[hash_value].end(); ++it) {
            if ((*it).key == key) {
                throw std::logic_error("Key already exists!");
            }
        }

        _rows[hash_value].push_back({ key, value });
        ++_size;
    }

    void replace(const std::string& key, const TVal& value) override {
        size_t hash_value = h(key);
        for (auto it = _rows[hash_value].begin(); it != _rows[hash_value].end(); ++it) {
            if ((*it).key == key) {
                (*it).value = value;
                return;
            }
        }
        throw std::logic_error("Key not found for replacement!");
    }

    TVal find(const std::string key) const override {
        size_t hash_value = h(key);
        for (auto it = _rows[hash_value].begin(); it != _rows[hash_value].end(); ++it) {
            if ((*it).key == key) {
                return (*it).value;
            }
        }
        throw std::logic_error("Key not found!");
    }

    void erase(const std::string& key) override {
        size_t hash_value = h(key);
        auto& bucket = _rows[hash_value];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if ((*it).key == key) {
                bucket.erase(it);
                --_size;
                return;
            }
        }
        throw std::logic_error("Key not found for erasure!");
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        for (int i = 0; i < _rows.size(); ++i) {
            for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
                out << (*it).key << " : " << (*it).value << std::endl;
            }
        }
        return out;
    }

    bool is_empty() const noexcept override {
        return _size == 0;
    }

    bool consist(const std::string& key) const noexcept override {
        size_t hash_value = h(key);
        for (auto it = _rows[hash_value].begin(); it != _rows[hash_value].end(); ++it) {
            if ((*it).key == key) {
                return true;
            }
        }
        return false;
    }

    size_t size() const { return _size; }
};

template <class T>
HashTable<T> merge_dict(const TVector<std::pair<std::string, T>>& dict1,
    const TVector<std::pair<std::string, T>>& dict2) {
    HashTable<T> result(128);

    for (int i = 0; i < dict1.size(); ++i) {
        result.insert(dict1[i].first, dict1[i].second);
    }

    for (int i = 0; i < dict2.size(); ++i) {
        if (!result.consist(dict2[i].first)) {
            result.insert(dict2[i].first, dict2[i].second);
        }
    }

    return result;
}