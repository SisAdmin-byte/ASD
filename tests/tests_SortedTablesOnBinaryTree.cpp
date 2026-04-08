// test_sorted_table_on_bst.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "SortedTableOnBinaryTree.h"

TEST(SortedTableOnBSTTest1, BasicInsertAndFind) {
    SortedTableOnBST<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);
    EXPECT_EQ(table.size(), 3);
}

TEST(SortedTableOnBSTTest2, ReplaceValue) {
    SortedTableOnBST<std::string, int> table;

    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);

    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableOnBSTTest3, EraseElement) {
    SortedTableOnBST<std::string, int> table;

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

TEST(SortedTableOnBSTTest4, EraseRoot) {
    SortedTableOnBST<int, int> table;

    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(1, 10);
    table.insert(4, 40);

    table.erase(5);

    EXPECT_EQ(table.size(), 4);
    EXPECT_FALSE(table.consist(5));
    EXPECT_TRUE(table.consist(3));
    EXPECT_TRUE(table.consist(7));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(4));
}

TEST(SortedTableOnBSTTest5, EmptyAndConsist) {
    SortedTableOnBST<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

    table.insert("test", 100);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist("test"));
    EXPECT_FALSE(table.consist("nonexistent"));
}

TEST(SortedTableOnBSTTest6, MultipleOperations) {
    SortedTableOnBST<std::string, int> table;

    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    EXPECT_EQ(table.find("a"), 1);
    EXPECT_EQ(table.find("b"), 2);
    EXPECT_EQ(table.find("c"), 3);

    table.replace("b", 20);
    EXPECT_EQ(table.find("b"), 20);

    table.erase("a");
    EXPECT_FALSE(table.consist("a"));
    EXPECT_TRUE(table.consist("b"));
    EXPECT_TRUE(table.consist("c"));
    EXPECT_EQ(table.size(), 2);

    table.insert("d", 4);
    EXPECT_EQ(table.find("d"), 4);
    EXPECT_EQ(table.size(), 3);
}

TEST(SortedTableOnBSTTest7, DuplicateKeyException) {
    SortedTableOnBST<std::string, int> table;

    table.insert("key", 100);

    EXPECT_THROW(table.insert("key", 200), std::logic_error);
    EXPECT_EQ(table.find("key"), 100);
}

TEST(SortedTableOnBSTTest8, FindNonexistentException) {
    SortedTableOnBST<std::string, int> table;

    table.insert("exists", 42);

    EXPECT_THROW(table.find("nonexistent"), std::logic_error);
    EXPECT_NO_THROW(table.find("exists"));
}

TEST(SortedTableOnBSTTest9, EraseNonexistentException) {
    SortedTableOnBST<std::string, int> table;

    table.insert("exists", 42);

    EXPECT_THROW(table.erase("nonexistent"), std::logic_error);
    EXPECT_NO_THROW(table.erase("exists"));
}

TEST(SortedTableOnBSTTest10, ReplaceNonexistentException) {
    SortedTableOnBST<std::string, int> table;

    table.insert("exists", 42);

    EXPECT_THROW(table.replace("nonexistent", 100), std::logic_error);
    EXPECT_NO_THROW(table.replace("exists", 100));
}

TEST(SortedTableOnBSTTest11, PrintIsSorted) {
    SortedTableOnBST<int, int> table;

    table.insert(5, 50);
    table.insert(1, 10);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(2, 20);
    table.insert(4, 40);

    std::ostringstream oss;
    table.print(oss);

    std::string output = oss.str();
    size_t pos1 = output.find("1 : 10");
    size_t pos2 = output.find("2 : 20");
    size_t pos3 = output.find("3 : 30");
    size_t pos4 = output.find("4 : 40");
    size_t pos5 = output.find("5 : 50");
    size_t pos6 = output.find("7 : 70");

    EXPECT_LT(pos1, pos2);
    EXPECT_LT(pos2, pos3);
    EXPECT_LT(pos3, pos4);
    EXPECT_LT(pos4, pos5);
    EXPECT_LT(pos5, pos6);
}

TEST(SortedTableOnBSTTest12, LargeNumberOfElements) {
    SortedTableOnBST<int, int> table;

    for (int i = 0; i < 1000; i++) {
        table.insert(i, i * 10);
    }

    EXPECT_EQ(table.size(), 1000);

    for (int i = 0; i < 1000; i++) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), i * 10);
    }

    for (int i = 0; i < 1000; i += 2) {
        table.erase(i);
    }

    EXPECT_EQ(table.size(), 500);

    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            EXPECT_FALSE(table.consist(i));
        }
        else {
            EXPECT_TRUE(table.consist(i));
            EXPECT_EQ(table.find(i), i * 10);
        }
    }
}

TEST(SortedTableOnBSTTest13, DifferentDataTypes) {
    SortedTableOnBST<double, std::string> table;

    table.insert(3.14, "pi");
    table.insert(2.718, "e");
    table.insert(1.618, "phi");

    EXPECT_EQ(table.find(3.14), "pi");
    EXPECT_EQ(table.find(2.718), "e");
    EXPECT_EQ(table.find(1.618), "phi");
    EXPECT_EQ(table.size(), 3);
}

TEST(SortedTableOnBSTTest14, InsertAfterErase) {
    SortedTableOnBST<std::string, int> table;

    table.insert("a", 1);
    table.insert("b", 2);
    table.erase("a");
    table.insert("c", 3);

    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("a"));
    EXPECT_TRUE(table.consist("b"));
    EXPECT_TRUE(table.consist("c"));
    EXPECT_EQ(table.find("b"), 2);
    EXPECT_EQ(table.find("c"), 3);
}
