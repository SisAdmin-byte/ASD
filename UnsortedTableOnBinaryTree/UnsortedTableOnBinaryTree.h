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
class BinaryTree {
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
    void preorder_recursive(Node* node, TVector<T>& result) const {
        if (!node) return;
        result.push_back(node->data);
        preorder_recursive(node->left, result);
        preorder_recursive(node->right, result);
    }

    void inorder_recursive(Node* node, TVector<T>& result) const {
        if (!node) return;
        inorder_recursive(node->left, result);
        result.push_back(node->data);
        inorder_recursive(node->right, result);
    }

    void postorder_recursive(Node* node, TVector<T>& result) const {
        if (!node) return;
        postorder_recursive(node->left, result);
        postorder_recursive(node->right, result);
        result.push_back(node->data);
    }

    void clear_recursive(Node* node) {
        if (!node) return;
        clear_recursive(node->left);
        clear_recursive(node->right);
        delete node;
    }

    Node* find_last_node() {
        if (!_root) return nullptr;

        Queue<Node*> q;
        q.enqueue(_root);
        Node* last = nullptr;

        while (!q.empty()) {
            last = q.front();
            q.dequeue();

            if (last->left) q.enqueue(last->left);
            if (last->right) q.enqueue(last->right);
        }
        return last;
    }

    Node* find_node(const T& value) {
        if (!_root) return nullptr;

        Queue<Node*> q;
        q.enqueue(_root);

        while (!q.empty()) {
            Node* current = q.front();
            q.dequeue();

            if (current->data == value) {
                return current;
            }

            if (current->left) q.enqueue(current->left);
            if (current->right) q.enqueue(current->right);
        }
        return nullptr;
    }
    Node* find_node_by_key(const T& value) const { // const_cast исправить
        if (!_root) return nullptr;

        Queue<Node*> q;
        q.enqueue(_root);

        while (!q.empty()) {
            Node* current = q.front();
            q.dequeue();

            if (current->data == value) {
                return current;
            }

            if (current->left) q.enqueue(current->left);
            if (current->right) q.enqueue(current->right);
        }
        return nullptr;
    }

    Node* get_parent_for_insert() {
        if (!_root) return nullptr;

        Queue<Node*> q;
        q.enqueue(_root);

        while (!q.empty()) {
            Node* current = q.front();
            q.dequeue();

            if (!current->left || !current->right) {
                return current;
            }

            if (current->left) q.enqueue(current->left);
            if (current->right) q.enqueue(current->right);
        }
        return nullptr;
    }

    void print_tree(Node* node, int space, int indent, std::ostream& out) const {
        if (!node) return;

        space += indent;

        print_tree(node->right, space, indent, out);

        out << std::endl;
        for (int i = indent; i < space; i++) {
            out << " ";
        }
        out << node->data << std::endl;

        print_tree(node->left, space, indent, out);
    }

public:
    BinaryTree() : _root(nullptr), _size(0) {}

    ~BinaryTree() {
        clear();
    }


    //BinaryTree<int> tree;
    //tree.insert(5);   корень
    //tree.insert(1);   левый потомок 5
    //tree.insert(3);   правый потомок 5
    //tree.insert(7);   левый потомок 1
    //tree.insert(2);   правый потомок 1


    //       5
    //    /    \
    //   1      3
    //  / \
    // 7   2

    void insert(const T& value) {
        if (!_root) {
            _root = new Node(value);
            _size++;
            return;
        }

        Node* parent = get_parent_for_insert();

        Node* new_node = new Node(value);
        new_node->parent = parent;

        if (!parent->left) {
            parent->left = new_node;
        }
        else if (!parent->right) {
            parent->right = new_node;
        }
        else {
            delete new_node;
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

        Node* last_node = find_last_node();

        to_delete->data = last_node->data;

        if (last_node->parent) {
            if (last_node->parent->left == last_node) {
                last_node->parent->left = nullptr;
            }
            else if (last_node->parent->right == last_node) {
                last_node->parent->right = nullptr;
            }
        }

        delete last_node;
        _size--;
    }

    const T& find_value(const T& value) const {
        Node* node = find_node_by_key(value);
        return node->data;
    }

    bool find(const T& value) const {
        return find_node_by_key(value) != nullptr;
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

    TVector<T> preorder() const {
        TVector<T> result;
        preorder_recursive(_root, result);
        return result;
    }

    TVector<T> inorder() const {
        TVector<T> result;
        inorder_recursive(_root, result);
        return result;
    }

    TVector<T> postorder() const {
        TVector<T> result;
        postorder_recursive(_root, result);
        return result;
    }

    TVector<T> levelorder() const {
        TVector<T> result;
        if (!_root) return result;

        Queue<Node*> q;
        q.enqueue(_root);

        while (!q.empty()) {
            Node* current = q.front();
            q.dequeue();
            result.push_back(current->data);

            if (current->left) q.enqueue(current->left);
            if (current->right) q.enqueue(current->right);
        }
        return result;
    }

    void print_all_traversals(std::ostream& out = std::cout) const {
        out << "\n=== Tree Traversals ===" << std::endl;

        out << "Preorder: ";
        TVector<T> pre = preorder();
        for (int i = 0; i < pre.size(); i++) {
            out << pre[i] << " ";
        }
        out << std::endl;

        out << "Inorder: ";
        TVector<T> in = inorder();
        for (int i = 0; i < in.size(); i++) {
            out << in[i] << " ";
        }
        out << std::endl;

        out << "Postorder: ";
        TVector<T> post = postorder();
        for (int i = 0; i < post.size(); i++) {
            out << post[i] << " ";
        }
        out << std::endl;

        out << "Level order: ";
        TVector<T> level = levelorder();
        for (int i = 0; i < level.size(); i++) {
            out << level[i] << " ";
        }
        out << std::endl;
    }
};

template <typename Tkey, typename Tvalue>
class UnsortedTableOnTree : public ITable<Tkey, Tvalue> {
private:
    BinaryTree<std::pair<Tkey, Tvalue>> _tree;
    std::pair<Tkey, Tvalue> find_pair(const Tkey& key) const {
        std::pair<Tkey, Tvalue> search_pair(key, Tvalue());
        return _tree.find_value(search_pair);
    }

public:
    UnsortedTableOnTree() = default;
    ~UnsortedTableOnTree() = default;

    void insert(const Tkey& key, const Tvalue& value) override {
        std::pair<Tkey, Tvalue> search_pair(key, Tvalue());
        if (_tree.find(search_pair)) {
            throw std::logic_error("Key already exists!");
        }
        _tree.insert(std::make_pair(key, value));
    }

    void replace(const Tkey& key, const Tvalue& value) override {
        std::pair<Tkey, Tvalue> search_pair(key, Tvalue());
        _tree.erase(search_pair);
        _tree.insert(std::make_pair(key, value));
    }

    Tvalue find(const Tkey key) const override {
        std::pair<Tkey, Tvalue> pair = find_pair(key);
        return pair.second;
    }

    void erase(const Tkey& key) override {
        std::pair<Tkey, Tvalue> erase_pair(key, Tvalue());
        _tree.erase(erase_pair);
    }

    std::ostream& print(std::ostream& out) const noexcept override {
        TVector<std::pair<Tkey, Tvalue>> level_order = _tree.levelorder();
        for (int i = 0; i < level_order.size(); i++) {
            out << level_order[i].first << " : " << level_order[i].second << std::endl;
        }
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

    void print_all_traversals(std::ostream& out = std::cout) const {
        _tree.print_all_traversals(out);
    }
};