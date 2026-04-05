#include <gtest/gtest.h>
#include "SortedTableOnVec.h"


TEST(SortedTableTest1, BasicInsertAndFind) {
    SortedTableOnVec<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);

    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.size(), 2);
}

TEST(SortedTableTest2, InsertionMaintainsOrder) {
    SortedTableOnVec<int, std::string> table;

    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(4, "four");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
    EXPECT_EQ(table.find(4), "four");
    EXPECT_EQ(table.find(5), "five");
    EXPECT_EQ(table.size(), 5);
}

TEST(SortedTableTest3, ReplaceValue) {
    SortedTableOnVec<std::string, int> table;

    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);

    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);
    EXPECT_EQ(table.size(), 1);
}

TEST(SortedTableTest4, EraseElement) {
    SortedTableOnVec<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist(2));

    table.erase(2);

    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(3));
}

TEST(SortedTableTest5, EmptyAndConsist) {
    SortedTableOnVec<std::string, int> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);

    table.insert("test", 100);
    EXPECT_FALSE(table.is_empty());
    EXPECT_TRUE(table.consist("test"));
    EXPECT_FALSE(table.consist("nonexistent"));
}

TEST(SortedTableTest6, DuplicateKeyThrowsException) {
    SortedTableOnVec<std::string, int> table;

    table.insert("key", 100);

    EXPECT_THROW(table.insert("key", 200), std::logic_error);
    EXPECT_EQ(table.find("key"), 100);
}

TEST(SortedTableTest7, BinarySearchPerformance) {
    SortedTableOnVec<int, int> table;

    for (int i = 0; i < 100; i++) {
        table.insert(i, i * 10);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(table.find(i), i * 10);
    }

    EXPECT_EQ(table.size(), 100);
}