// Copyright 2024 Marina Usova

#include <iostream>
#include <string>
#include <sstream>
#include "../UnsortedTableOnBinaryTree.h"


int main() {
    
    UnsortedTableOnTree<std::string, int> table;

    table.insert("first", 1);
    table.insert("second", 2);
    table.insert("third", 3);

    return 0;
}