#include <gtest/gtest.h>
#include <sstream>
#include "TableOnList.h"

TEST(UnsortedTableOnListTest1, BasicInsertAndFind) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);
    EXPECT_EQ(table.size(), 3);
}

TEST(UnsortedTableOnListTest2, ReplaceValue) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);

    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnsortedTableOnListTest3, EraseElement) {
    UnsortedTableOnList<std::string, int> table;

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

TEST(UnsortedTableOnListTest4, EraseFirstElement) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("first", 1);
    table.insert("second", 2);
    table.insert("third", 3);

    EXPECT_TRUE(table.consist("first"));
    table.erase("first");
    EXPECT_FALSE(table.consist("first"));
    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist("second"));
    EXPECT_TRUE(table.consist("third"));

    EXPECT_EQ(table.find("second"), 2);
    EXPECT_EQ(table.find("third"), 3);
}

TEST(UnsortedTableOnListTest5, EraseLastElement) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("first", 1);
    table.insert("second", 2);
    table.insert("last", 3);

    EXPECT_TRUE(table.consist("last"));
    table.erase("last");
    EXPECT_FALSE(table.consist("last"));
    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist("first"));
    EXPECT_TRUE(table.consist("second"));

    EXPECT_EQ(table.find("first"), 1);
    EXPECT_EQ(table.find("second"), 2);
}

TEST(UnsortedTableOnListTest6, EmptyAndConsist) {
    UnsortedTableOnList<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

    table.insert("test", 100);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist("test"));
    EXPECT_FALSE(table.consist("nonexistent"));
}

TEST(UnsortedTableOnListTest7, MultipleOperations) {
    UnsortedTableOnList<std::string, int> table;

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

    table.erase("c");
    EXPECT_FALSE(table.consist("c"));
    EXPECT_EQ(table.size(), 2);
}

TEST(UnsortedTableOnListTest8, DuplicateKeyException) {
    UnsortedTableOnList<std::string, int> table;

    table.insert("key", 100);

    EXPECT_THROW(table.insert("key", 200), std::logic_error);
    EXPECT_EQ(table.find("key"), 100);
}