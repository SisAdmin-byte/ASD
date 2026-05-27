#include <gtest/gtest.h>
#include "UnsortedTableOnBinaryTree.h"


TEST(BinaryTreeTest, InsertAndFind) {
    BinaryTree<std::pair<std::string, int>> tree;

    tree.insert(std::make_pair("one", 1));
    tree.insert(std::make_pair("two", 2));
    tree.insert(std::make_pair("three", 3));

    EXPECT_TRUE(tree.find(std::make_pair("one", 0)));
    EXPECT_TRUE(tree.find(std::make_pair("two", 0)));
    EXPECT_TRUE(tree.find(std::make_pair("three", 0)));
    EXPECT_FALSE(tree.find(std::make_pair("four", 0)));
    EXPECT_EQ(tree.size(), 3);
}

TEST(BinaryTreeTest, FindValue) {
    BinaryTree<std::pair<std::string, int>> tree;

    tree.insert(std::make_pair("key", 42));

    std::pair<std::string, int> result = tree.find_value(std::make_pair("key", 0));
    EXPECT_EQ(result.second, 42);
}

TEST(BinaryTreeTest, Erase) {
    BinaryTree<std::pair<std::string, int>> tree;

    tree.insert(std::make_pair("one", 1));
    tree.insert(std::make_pair("two", 2));
    tree.insert(std::make_pair("three", 3));

    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.find(std::make_pair("two", 0)));

    tree.erase(std::make_pair("two", 0));

    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.find(std::make_pair("two", 0)));
    EXPECT_TRUE(tree.find(std::make_pair("one", 0)));
    EXPECT_TRUE(tree.find(std::make_pair("three", 0)));
}

TEST(BinaryTreeTest, EraseNonExisting) {
    BinaryTree<std::pair<std::string, int>> tree;

    tree.insert(std::make_pair("key", 10));

    EXPECT_THROW(tree.erase(std::make_pair("nonexistent", 0)), std::logic_error);
}

TEST(BinaryTreeTest, EraseLastElement) {
    BinaryTree<std::pair<std::string, int>> tree;

    tree.insert(std::make_pair("only", 1));

    tree.erase(std::make_pair("only", 0));

    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(BinaryTreeTest, IsEmpty) {
    BinaryTree<int> tree;

    EXPECT_TRUE(tree.is_empty());

    tree.insert(10);
    EXPECT_FALSE(tree.is_empty());

    tree.erase(10);
    EXPECT_TRUE(tree.is_empty());
}

TEST(BinaryTreeTest, Size) {
    BinaryTree<int> tree;

    EXPECT_EQ(tree.size(), 0);

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    EXPECT_EQ(tree.size(), 3);

    tree.erase(2);
    EXPECT_EQ(tree.size(), 2);

    tree.clear();
    EXPECT_EQ(tree.size(), 0);
}

TEST(BinaryTreeTest, Clear) {
    BinaryTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    tree.clear();

    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.size(), 0);
}


TEST(UnsortedTableOnTreeTest1, BasicInsertAndFind) {
    UnsortedTableOnTree<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);
    EXPECT_EQ(table.size(), 3);
}

TEST(UnsortedTableOnTreeTest2, ReplaceValue) {
    UnsortedTableOnTree<std::string, int> table;

    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);

    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnsortedTableOnTreeTest3, EraseElement) {
    UnsortedTableOnTree<std::string, int> table;

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

TEST(UnsortedTableOnTreeTest4, DuplicateKeyException) {
    UnsortedTableOnTree<std::string, int> table;

    table.insert("key", 100);

    EXPECT_THROW(table.insert("key", 200), std::logic_error);
    EXPECT_EQ(table.find("key"), 100);
}
