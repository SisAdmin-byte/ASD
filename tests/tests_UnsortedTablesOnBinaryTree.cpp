// test_unsorted_table_on_tree.cpp
#include <gtest/gtest.h>
#include "UnsortedTableOnBinaryTree.h"

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


TEST(UnsortedTableOnTreeTest5, TreeTraversals) {
    UnsortedTableOnTree<std::string, int> table;

    table.insert("first", 1);
    table.insert("second", 2);
    table.insert("third", 3);

    testing::internal::CaptureStdout();
    table.print_all_traversals();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}
