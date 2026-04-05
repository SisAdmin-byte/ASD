#include <gtest/gtest.h>
#include "UnsortedTableOnVec.h"


TEST(UnsortedTableTest1, BasicInsertAndFind) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.size(), 2);
}

TEST(UnsortedTableTest2, ReplaceValue) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);

    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);
    EXPECT_EQ(table.size(), 1);
}

TEST(UnsortedTableTest3, EraseElement) {
    UnsortedTableOnVec<std::string, int> table;

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

TEST(UnsortedTableTest4, EmptyAndConsist) {
    UnsortedTableOnVec<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

    table.insert("test", 100);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist("test"));
    EXPECT_FALSE(table.consist("nonexistent"));
}

TEST(UnsortedTableTest5, MultipleOperations) {
    UnsortedTableOnVec<std::string, int> table;

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
}

TEST(UnsortedTableTest6, DuplicateKeyException) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("key", 100);

    EXPECT_THROW(table.insert("key", 200), std::logic_error);
    EXPECT_EQ(table.find("key"), 100); 
}

TEST(UnsortedTableTest7, FindNonexistentException) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("exists", 42);

    EXPECT_THROW(table.find("nonexistent"), std::logic_error);
    EXPECT_NO_THROW(table.find("exists"));
}

TEST(UnsortedTableTest8, EraseNonexistentException) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("exists", 42);

    EXPECT_THROW(table.erase("nonexistent"), std::logic_error);
    EXPECT_NO_THROW(table.erase("exists"));
}

TEST(UnsortedTableTest9, ReplaceNonexistentException) {
    UnsortedTableOnVec<std::string, int> table;

    table.insert("exists", 42);

    EXPECT_THROW(table.replace("nonexistent", 100), std::logic_error);
    EXPECT_NO_THROW(table.replace("exists", 100));
}