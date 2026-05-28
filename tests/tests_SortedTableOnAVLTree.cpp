#include <gtest/gtest.h>
#include "SortedTableOnAVLTree.h"

TEST(AVLTreeTest, InsertAndFind) {
    AVLTree<std::string, int> tree;

    tree.insert("one", 1);
    tree.insert("two", 2);
    tree.insert("three", 3);

    EXPECT_EQ(tree.find("one"), 1);
    EXPECT_EQ(tree.find("two"), 2);
    EXPECT_EQ(tree.find("three"), 3);
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, InsertDuplicate) {
    AVLTree<std::string, int> tree;

    tree.insert("key", 10);
    EXPECT_THROW(tree.insert("key", 20), std::logic_error);
}

TEST(AVLTreeTest, Replace) {
    AVLTree<std::string, int> tree;

    tree.insert("key", 10);
    tree.replace("key", 20);
    EXPECT_EQ(tree.find("key"), 20);

    EXPECT_THROW(tree.replace("nonexistent", 5), std::logic_error);
}

TEST(AVLTreeTest, Erase) {
    AVLTree<std::string, int> tree;

    tree.insert("one", 1);
    tree.insert("two", 2);
    tree.insert("three", 3);

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.contains("two"));

    tree.erase("two");

    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.contains("two"));
    EXPECT_TRUE(tree.contains("one"));
    EXPECT_TRUE(tree.contains("three"));

    EXPECT_THROW(tree.erase("nonexistent"), std::logic_error);
}

TEST(AVLTreeTest, EraseRoot) {
    AVLTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(5, "five");
    tree.insert(15, "fifteen");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    tree.erase(10);

    EXPECT_EQ(tree.size(), 4);
    EXPECT_FALSE(tree.contains(10));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
}

TEST(AVLTreeTest, LargeNumberOfElements) {
    AVLTree<int, int> tree;

    const int N = 1000;
    for (int i = 0; i < N; i++) {
        tree.insert(i, i * 10);
    }

    EXPECT_EQ(tree.size(), N);

    for (int i = 0; i < N; i++) {
        EXPECT_EQ(tree.find(i), i * 10);
    }
}

TEST(AVLTreeTest, BalanceAfterInsert) {
    AVLTree<int, int> tree;

    for (int i = 1; i <= 100; i++) {
        tree.insert(i, i);
    }

    int height = tree.height();
    EXPECT_LE(height, 15);
}

TEST(AVLTreeTest, BalanceAfterDelete) {
    AVLTree<int, int> tree;

    for (int i = 1; i <= 100; i++) {
        tree.insert(i, i);
    }

    for (int i = 2; i <= 100; i += 2) {
        tree.erase(i);
    }

    for (int i = 1; i <= 100; i += 2) {
        EXPECT_TRUE(tree.contains(i));
    }

    int height = tree.height();
    EXPECT_LE(height, 15);
}

TEST(AVLTreeTest, LeftLeftRotation) {
    AVLTree<int, int> tree;

    tree.insert(3, 30);
    tree.insert(2, 20);
    tree.insert(1, 10); 

    EXPECT_EQ(tree.find(1), 10);
    EXPECT_EQ(tree.find(2), 20);
    EXPECT_EQ(tree.find(3), 30);
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, RightRightRotation) {
    AVLTree<int, int> tree;

    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30); 

    EXPECT_EQ(tree.find(1), 10);
    EXPECT_EQ(tree.find(2), 20);
    EXPECT_EQ(tree.find(3), 30);
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, LeftRightRotation) {
    AVLTree<int, int> tree;

    tree.insert(3, 30);
    tree.insert(1, 10);
    tree.insert(2, 20);

    EXPECT_EQ(tree.find(1), 10);
    EXPECT_EQ(tree.find(2), 20);
    EXPECT_EQ(tree.find(3), 30);
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, RightLeftRotation) {
    AVLTree<int, int> tree;

    tree.insert(1, 10);
    tree.insert(3, 30);
    tree.insert(2, 20); 

    EXPECT_EQ(tree.find(1), 10);
    EXPECT_EQ(tree.find(2), 20);
    EXPECT_EQ(tree.find(3), 30);
    EXPECT_EQ(tree.size(), 3);
}

TEST(AVLTreeTest, EmptyTree) {
    AVLTree<int, int> tree;

    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_THROW(tree.find(1), std::logic_error);
    EXPECT_THROW(tree.erase(1), std::logic_error);
}


TEST(SortedTableOnAVLTest, InsertAndFind) {
    SortedTableOnAVL<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);
    EXPECT_EQ(table.size(), 3);
}

TEST(SortedTableOnAVLTest, InsertDuplicate) {
    SortedTableOnAVL<std::string, int> table;

    table.insert("key", 10);
    EXPECT_THROW(table.insert("key", 20), std::logic_error);
}

TEST(SortedTableOnAVLTest, Replace) {
    SortedTableOnAVL<std::string, int> table;

    table.insert("key", 10);
    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);

}

TEST(SortedTableOnAVLTest, Erase) {
    SortedTableOnAVL<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("two"));

    table.erase("two");

    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("two"));
    EXPECT_TRUE(table.consist("one"));
    EXPECT_TRUE(table.consist("three"));

}

TEST(SortedTableOnAVLTest, LargeNumberOfElements) {
    SortedTableOnAVL<int, int> table;

    const int n = 500;
    for (int i = 0; i < n; i++) {
        table.insert(i, i * 10);
    }

    EXPECT_EQ(table.size(), n);

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(table.find(i), i * 10);
    }
}

TEST(SortedTableOnAVLTest, IsEmpty) {
    SortedTableOnAVL<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
    table.insert("key", 10);
    EXPECT_FALSE(table.is_empty());
    table.erase("key");
    EXPECT_TRUE(table.is_empty());
}

