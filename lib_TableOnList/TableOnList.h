#pragma once
#include <utility>
#include "List.h"
#include "ITable.h"

//template <typename Tkey, typename Tvalue>
//
//
//struct Node {
//
//	std::pair<Tkey, Tvalue> data;
//	Node** next;
//
//};
//template <typename Tkey, typename Tvalue>
//class skipList {
//
//	List<Node*> heads;
//	size_t lvl, max_lvl;
//
//
//};
//
//
////Node* new_node = new_Node(...)
//if is_empty() {
//
//
//	for (int i = 0; i < new_node.lvls; i++) {
//
//		heads.push_front(new_node);
//
//	}
//
//}
//template <typename Tkey, typename Tvalue>
//struct Node {
//
//	std::pair<Tkey, Tval> data;
//	Node** next;
//};
//template <typename Tkey, typename Tvalue>
//class skipList {
//	List <Node*>heads;
//	size_t lvl, max_lvl;
//};
//template <typename Tkey, typename Tvalue>
//Node* new_node = new Node(...);
//если is_empty()
//for (int i = 0; i < new_node.lvls; i++) {
//	heads.push_front(new_node);
//}
////Выполнить поиск(ближ меньш равный)
//-> = key throw
//->Node * *prevs
//for (int i = 0; i < min(new_node lvls, prev lvl))
//	prev.next[i] == new_node;
//Выполнить поиск 
//List <Node**> path
//push_front


template <typename Tkey, typename Tvalue>
class UnsortedTableOnList : public ITable<Tkey, Tvalue> {
    List<std::pair<Tkey, Tvalue>> _rows;

public:
    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() = default;

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
void UnsortedTableOnList<Tkey, Tvalue>::insert(const Tkey& key, const Tvalue& value) {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {
            throw std::logic_error("Key already exists!");
        }
    }
    _rows.push_back(std::make_pair(key, value));
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnList<Tkey, Tvalue>::replace(const Tkey& key, const Tvalue& value) {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {
            (*it).second = value;
            return;
        }
    }
    throw std::logic_error("Key not found for replacement!");
}

template <typename Tkey, typename Tvalue>
Tvalue UnsortedTableOnList<Tkey, Tvalue>::find(const Tkey key) const {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {
            return (*it).second;
        }
    }
    throw std::logic_error("Key not found!");
}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnList<Tkey, Tvalue>::erase(const Tkey& key) {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {
            _rows.erase(it);
            return;
        }
    }
    throw std::logic_error("Key not found for erasure!");
}

template <typename Tkey, typename Tvalue>
std::ostream& UnsortedTableOnList<Tkey, Tvalue>::print(std::ostream& out) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        out << (*it).first << " : " << (*it).second << std::endl;
    }
    return out;
}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnList<Tkey, Tvalue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnList<Tkey, Tvalue>::consist(const Tkey& key) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); ++it) {
        if ((*it).first == key) {
            return true;
        }
    }
    return false;
}



