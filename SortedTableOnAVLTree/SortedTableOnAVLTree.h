#pragma once
#include <iostream>
#include <algorithm>
#include "ITable.h"

template <typename Tkey, typename Tvalue>
class AVLTree {
private:
    struct Node {
        std::pair<Tkey, Tvalue> data;
        Node* left;
        Node* right;
        int height;

        Node(const Tkey& key, const Tvalue& value)
            : data(key, value), left(nullptr), right(nullptr), height(1) {
        }
    };

    Node* _root;
    int _size;

    int get_height(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int get_balance(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return get_height(node->left) - get_height(node->right);
    }

    void update_height(Node* node) {
        if (node == nullptr) {
            return;
        }
        int left_height = get_height(node->left);
        int right_height = get_height(node->right);
        if (left_height > right_height) {
            node->height = 1 + left_height;
        }
        else {
            node->height = 1 + right_height;
        }
    }

    
       //Правый поворот (Right Rotation)
      
       //Схема поворота:
     
       //    ДО:                    ПОСЛЕ:
     
       //    old_root (y)           new_root (x)
       //      /    \                 /    \
       //     x      C               A      y (old_root)
       //   /   \                         /   \
       //  A     B                       B     C
       //        ^                       ^
       //        |                       |
       //  moving_subtree           moving_subtree
       //  (поддерево B             (поддерево B
       //   переезжает)              переехало)
      
     
    Node* rotate_right(Node* old_root) {

        Node* new_root = old_root->left;
        Node* moving_subtree = new_root->right;

        new_root->right = old_root;
        old_root->left = moving_subtree;

        update_height(old_root);  
        update_height(new_root);  

        return new_root;
    }

    
      //Левый поворот (Left Rotation)
     
      //Схема поворота:
     
      //    ДО:                    ПОСЛЕ:
     
      //    old_root (x)           new_root (y)
      //      /    \                 /    \
      //     A      y               x      C
      //          /   \           /   \
      //         B     C         A     B
      //         ^                     ^  
      //         |                     |
      //   moving_subtree          moving_subtree
      //   (поддерево B            (поддерево B
      //    переезжает)             переехало)

     
    Node* rotate_left(Node* old_root) {

        Node* new_root = old_root->right;
        Node* moving_subtree = new_root->left; 

        new_root->left = old_root;                 
        old_root->right = moving_subtree;          

        update_height(old_root);
        update_height(new_root);

        return new_root;
    }

    
      //Балансировка узла
      //Возможные случаи:
     
      //1. Лево-левый: balance > 1 и balance(left) >= 0
      //   Просто правый поворот
     
      //   ДО:            ПОСЛЕ:
      //     y (bf = 2)       x (bf = 0)
      //    /                / \
      //   x (bf = 1)       A   y
      //  /
      // A
     
      //2. Право-правый: balance < -1 и balance(right) <= 0
      //   Просто левый поворот
     
      //   ДО:              ПОСЛЕ:
      //   x (bf = -2)        y (bf = 0)
      //    \                / \
      //     y (bf = -1)    x   C
      //      \
      //       C
     
      //3. Лево-правый: balance > 1 и balance(left) < 0
      //   Левый поворот на левом ребенке, потом правый поворот
     
      //   ДО:            ПРОМЕЖУТОЧНО:    ПОСЛЕ:
      //     y (bf = 2)       y (bf = 2)        B (bf = 0)
      //    /                /                 / \
      //   x (bf = -1)      B (bf = 1)        x   y
      //    \              /
      //     B            x
     
      //4. Право-левый: balance < -1 и balance(right) > 0
      //   Правый поворот на правом ребенке, потом левый поворот
     
      //   ДО:            ПРОМЕЖУТОЧНО:    ПОСЛЕ:
      //   x (bf = -2)       x (bf = -2)        B (bf = 0)
      //    \                 \                / \
      //     y (bf = 1)        B (bf = -1)    x   y
      //    /                   \
      //   B                     y
     
    Node* balance(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        update_height(node);
        int balance_factor = get_balance(node);

        if (balance_factor > 1 && get_balance(node->left) > 0) {
            return rotate_right(node);
        }

        if (balance_factor < -1 && get_balance(node->right) < 0) {
            return rotate_left(node);
        }

        if (balance_factor > 1 && get_balance(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        if (balance_factor < -1 && get_balance(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        return node;
    }

    Node* insert_node(Node* node, const Tkey& key, const Tvalue& value) {
        if (node == nullptr) {
            _size++;
            return new Node(key, value);
        }

        if (key < node->data.first) {
            node->left = insert_node(node->left, key, value);
        }
        else if (key > node->data.first) {
            node->right = insert_node(node->right, key, value);
        }
        else {
            throw std::logic_error("Key already exists!");
        }

        return balance(node);
    }

    Node* find_min_node(Node* node) const {
        Node* current = node;
        while (current != nullptr && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* delete_node(Node* node, const Tkey& key) {
        if (node == nullptr) {
            throw std::logic_error("Key not found for erasure!");
        }

        if (key < node->data.first) {
            node->left = delete_node(node->left, key);
        }
        else if (key > node->data.first) {
            node->right = delete_node(node->right, key);
        }
        else {

            if (node->left == nullptr) {
                Node* right_child = node->right;
                delete node;
                _size--;
                return right_child;
            }

            else if (node->right == nullptr) {
                Node* left_child = node->left;
                delete node;
                _size--;
                return left_child;
            }
            else {
                Node* successor = find_min_node(node->right);
                node->data = successor->data;
                node->right = delete_node(node->right, successor->data.first);
            }
        }

        if (node == nullptr) {
            return nullptr;
        }

        return balance(node);
    }

    Node* find_node(Node* node, const Tkey& key) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (key == node->data.first) {
            return node;
        }
        else if (key < node->data.first) {
            return find_node(node->left, key);
        }
        else {
            return find_node(node->right, key);
        }
    }

    void clear_recursive(Node* node) {
        if (node != nullptr) {
            clear_recursive(node->left);
            clear_recursive(node->right);
            delete node;
        }
    }

    void inorder_traversal(Node* node, std::ostream& out) const {
        if (node != nullptr) {
            inorder_traversal(node->left, out);
            out << node->data.first << " : " << node->data.second << std::endl;
            inorder_traversal(node->right, out);
        }
    }

public:
    AVLTree() : _root(nullptr), _size(0) {}

    ~AVLTree() {
        clear();
    }

    void insert(const Tkey& key, const Tvalue& value) {
        _root = insert_node(_root, key, value);
    }

    void erase(const Tkey& key) {
        _root = delete_node(_root, key);
    }

    Tvalue find(const Tkey& key) const {
        Node* node = find_node(_root, key);
        if (node == nullptr) {
            throw std::logic_error("Key not found!");
        }
        return node->data.second;
    }

    bool contains(const Tkey& key) const {
        return find_node(_root, key) != nullptr;
    }

    void replace(const Tkey& key, const Tvalue& value) {
        Node* node = find_node(_root, key);
        if (node == nullptr) {
            throw std::logic_error("Key not found for replacement!");
        }
        node->data.second = value;
    }

    bool is_empty() const {
        return _size == 0;
    }

    int size() const {
        return _size;
    }

    int height() const {
        return get_height(_root);
    }

    void clear() {
        clear_recursive(_root);
        _root = nullptr;
        _size = 0;
    }

    void print(std::ostream& out = std::cout) const {
        inorder_traversal(_root, out);
    }
};

template <typename Tkey, typename Tvalue>
class SortedTableOnAVL : public ITable<Tkey, Tvalue> {
private:
    AVLTree<Tkey, Tvalue> _tree;

public:
    SortedTableOnAVL() = default;
    ~SortedTableOnAVL() = default;

    void insert(const Tkey& key, const Tvalue& value) override {
        try {
            _tree.insert(key, value);
        }
        catch (const std::logic_error& e) {
            throw std::logic_error("Key already exists!");
        }
    }

    void replace(const Tkey& key, const Tvalue& value) override {
        _tree.replace(key, value);
    }

    Tvalue find(const Tkey key) const override {
        return _tree.find(key);
    }

    void erase(const Tkey& key) override {
        _tree.erase(key);
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        _tree.print(out);
        return out;
    }

    bool is_empty() const noexcept override {
        return _tree.is_empty();
    }

    bool consist(const Tkey& key) const noexcept override {
        return _tree.contains(key);
    }

    int size() const {
        return _tree.size();
    }

    int height() const {
        return _tree.height();
    }
};