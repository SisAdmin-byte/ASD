#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include "ITable.h"

template <typename Tkey, typename Tvalue>
bool operator<(const std::pair<Tkey, Tvalue>& a, const std::pair<Tkey, Tvalue>& b) {
    return a.first < b.first;
}

template <typename Tkey, typename Tvalue>
bool operator>(const std::pair<Tkey, Tvalue>& a, const std::pair<Tkey, Tvalue>& b) {
    return a.first > b.first;
}

template <typename Tkey, typename Tvalue>
bool operator==(const std::pair<Tkey, Tvalue>& a, const std::pair<Tkey, Tvalue>& b) {
    return a.first == b.first;
}

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* _root;
    int _size;

    Node* createNode(const T& value) {
        Node* newNode = new Node(value);
        return newNode;
    }

    Node* insertNode(Node* root, const T& value) {
        if (root == nullptr) {
            _size++;
            return createNode(value);
        }

        if (value < root->data) {
            root->left = insertNode(root->left, value);
        }
        else if (value > root->data) {
            root->right = insertNode(root->right, value);
        }
        else {
            throw std::logic_error("Value already exists!");
        }

        return root;
    }

    Node* searchNode(Node* root, const T& value) const {
        Node* current = root;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }

    Node* findMaxNode(Node* node) const {
        Node* current = node;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    Node* deleteNode(Node* root, const T& value) {
        if (root == nullptr) {
            throw std::logic_error("Value not found in tree!");
        }

        if (value < root->data) {
            root->left = deleteNode(root->left, value);
        }
        else if (value > root->data) {
            root->right = deleteNode(root->right, value);
        }
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                _size--;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                _size--;
                return temp;
            }

            Node* temp = findMaxNode(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data);
        }
        return root;
    }

    void inorderTraversal(Node* root, T* result, int& index) const {
        if (root != nullptr) {
            inorderTraversal(root->left, result, index);
            result[index++] = root->data;
            inorderTraversal(root->right, result, index);
        }
    }

    void clearRecursive(Node* root) {
        if (root != nullptr) {
            clearRecursive(root->left);
            clearRecursive(root->right);
            delete root;
        }
    }

public:
    BinarySearchTree() : _root(nullptr), _size(0) {}

    ~BinarySearchTree() {
        clear();
    }

    void insert(const T& value) {
        _root = insertNode(_root, value);
    }

    void erase(const T& value) {
        _root = deleteNode(_root, value);
    }

    bool find(const T& value) const {
        return searchNode(_root, value) != nullptr;
    }

    bool is_empty() const {
        return _size == 0;
    }

    int size() const {
        return _size;
    }

    void clear() {
        clearRecursive(_root);
        _root = nullptr;
        _size = 0;
    }

    T* inorder(int& size) const {
        T* result = new T[_size];
        int index = 0;
        inorderTraversal(_root, result, index);
        size = _size;
        return result;
    }
    const T& find_value(const T& value) const {
        Node* node = searchNode(_root, value);
        if (node == nullptr) {
            throw std::logic_error("Value not found!");
        }
        return node->data;
    }
};

template <typename Tkey, typename Tvalue>
class SortedTableOnBST : public ITable<Tkey, Tvalue> {
private:
    BinarySearchTree<std::pair<Tkey, Tvalue>> _tree;

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
        std::pair<Tkey, Tvalue> search_pair(key, Tvalue());

        if (!_tree.find(search_pair)) {
            throw std::logic_error("Key not found for replacement!");
        }

        _tree.erase(search_pair);
        _tree.insert(std::make_pair(key, value));
    }

    Tvalue find(const Tkey key) const override {
        std::pair<Tkey, Tvalue> search_pair(key, Tvalue());
        return _tree.find_value(search_pair).second;
    }

    void erase(const Tkey& key) override {
        std::pair<Tkey, Tvalue> erase_pair(key, Tvalue());
        try {
            _tree.erase(erase_pair);
        }
        catch (const std::logic_error& e) {
            throw std::logic_error("Key not found for erasure!");
        }
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        int size;
        std::pair<Tkey, Tvalue>* inorder_arr = _tree.inorder(size);

        for (int i = 0; i < size; i++) {
            out << inorder_arr[i].first << " : " << inorder_arr[i].second << std::endl;
        }

        delete[] inorder_arr;
        return out;
    }

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        std::pair<Tkey, Tvalue> check_pair(key, Tvalue());
        return _tree.find(check_pair);
    }

    int size() const {
        return _tree.size();
    }
};