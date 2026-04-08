#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include "ITable.h"

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* _root;
    int _size;

    void clear_recursive(Node* node) {
        if (!node) return;
        clear_recursive(node->left);
        clear_recursive(node->right);
        delete node;
    }

    Node* find_min(Node* node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* find_max(Node* node) const {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    Node* find_node(const T& value) const {
        Node* current = _root;
        while (current) {
            if (value == current->data) {
                return current;
            }
            else if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void inorder_recursive(Node* node, TVector<T>& result) const {
        if (!node) return;
        inorder_recursive(node->left, result);
        result.push_back(node->data);
        inorder_recursive(node->right, result);
    }

public:
    BinarySearchTree() : _root(nullptr), _size(0) {}

    ~BinarySearchTree() {
        clear();
    }

    void insert(const T& value) {
        if (!_root) {
            _root = new Node(value);
            _size++;
            return;
        }

        Node* current = _root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value == current->data) {
                throw std::logic_error("Value already exists!");
            }
            else if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        Node* new_node = new Node(value);
        new_node->parent = parent;

        if (value < parent->data) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        _size++;
    }

    void erase(const T& value) {
        Node* to_delete = find_node(value);
        if (!to_delete) {
            throw std::logic_error("Value not found in tree");
        }

        if (_size == 1) {
            delete _root;
            _root = nullptr;
            _size--;
            return;
        }

        if (!to_delete->left && !to_delete->right) {
            if (to_delete->parent) {
                if (to_delete->parent->left == to_delete) {
                    to_delete->parent->left = nullptr;
                }
                else {
                    to_delete->parent->right = nullptr;
                }
            }
            delete to_delete;
            _size--;
        }
        else if (!to_delete->left) {
            Node* right_child = to_delete->right;
            if (to_delete->parent) {
                if (to_delete->parent->left == to_delete) {
                    to_delete->parent->left = right_child;
                }
                else {
                    to_delete->parent->right = right_child;
                }
            }
            else {
                _root = right_child;
            }
            right_child->parent = to_delete->parent;
            delete to_delete;
            _size--;
        }
        else if (!to_delete->right) {
            Node* left_child = to_delete->left;
            if (to_delete->parent) {
                if (to_delete->parent->left == to_delete) {
                    to_delete->parent->left = left_child;
                }
                else {
                    to_delete->parent->right = left_child;
                }
            }
            else {
                _root = left_child;
            }
            left_child->parent = to_delete->parent;
            delete to_delete;
            _size--;
        }
        else {
            Node* max_left = find_max(to_delete->left);
            T temp_data = max_left->data;
            erase(max_left->data);
            to_delete->data = temp_data;
        }
    }

    bool find(const T& value) const {
        return find_node(value) != nullptr;
    }

    bool is_empty() const {
        return _size == 0;
    }

    int size() const {
        return _size;
    }

    void clear() {
        clear_recursive(_root);
        _root = nullptr;
        _size = 0;
    }

    TVector<T> inorder() const {
        TVector<T> result;
        inorder_recursive(_root, result);
        return result;
    }

};


template <typename Tkey, typename Tvalue>
class SortedTableOnBST : public ITable<Tkey, Tvalue> {
private:
    BinarySearchTree<std::pair<Tkey, Tvalue>> _tree;

    struct ComparePair {
        bool operator()(const std::pair<Tkey, Tvalue>& a, const std::pair<Tkey, Tvalue>& b) const {
            return a.first < b.first;
        }

        bool operator()(const std::pair<Tkey, Tvalue>& a, const Tkey& key) const {
            return a.first < key;
        }

        bool operator()(const Tkey& key, const std::pair<Tkey, Tvalue>& b) const {
            return key < b.first;
        }
    };

public:
    SortedTableOnBST() = default;
    ~SortedTableOnBST() = default;

    void insert(const Tkey& key, const Tvalue& value) override {
        try {
            _tree.insert(std::make_pair(key, value));
        }
        catch (const std::logic_error& e) {
            throw std::logic_error("Key already exists!");
        }
    }

    void replace(const Tkey& key, const Tvalue& value) override {
        TVector<std::pair<Tkey, Tvalue>> inorder = _tree.inorder();
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i].first == key) {
                _tree.erase(inorder[i]);
                _tree.insert(std::make_pair(key, value));
                return;
            }
        }
        throw std::logic_error("Key not found for replacement!");
    }

    Tvalue find(const Tkey key) const override {
        TVector<std::pair<Tkey, Tvalue>> inorder = _tree.inorder();
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i].first == key) {
                return inorder[i].second;
            }
        }
        throw std::logic_error("Key not found!");
    }

    void erase(const Tkey& key) override {
        TVector<std::pair<Tkey, Tvalue>> inorder = _tree.inorder();
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i].first == key) {
                _tree.erase(inorder[i]);
                return;
            }
        }
        throw std::logic_error("Key not found for erasure!");
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        TVector<std::pair<Tkey, Tvalue>> inorder = _tree.inorder();
        for (int i = 0; i < inorder.size(); i++) {
            out << inorder[i].first << " : " << inorder[i].second << std::endl;
        }
        return out;
    }

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        TVector<std::pair<Tkey, Tvalue>> inorder = _tree.inorder();
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder[i].first == key) {
                return true;
            }
        }
        return false;
    }

    int size() const {
        return _tree.size();
    }
};