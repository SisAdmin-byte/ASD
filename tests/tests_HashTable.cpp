#include <gtest/gtest.h>
#include "HashTable.h"
#include <string>

TEST(HashTableTest1, BasicInsertAndFind) {
    HashTable<int> table;
    table.insert("one", 1);
    table.insert("two", 2);
    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.size(), 2);
}

TEST(HashTableTest2, InsertDuplicateThrows) {
    HashTable<int> table;
    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);
    EXPECT_THROW(table.insert("key", 20), std::logic_error);
    EXPECT_EQ(table.find("key"), 10);
    EXPECT_EQ(table.size(), 1);
}

TEST(HashTableTest3, ReplaceValue) {
    HashTable<int> table;
    table.insert("key", 10);
    EXPECT_EQ(table.find("key"), 10);
    table.replace("key", 20);
    EXPECT_EQ(table.find("key"), 20);
    EXPECT_EQ(table.size(), 1);
}

TEST(HashTableTest4, ReplaceNonExistent) {
    HashTable<int> table;
    EXPECT_THROW(table.replace("nonexistent", 100), std::logic_error);
}

TEST(HashTableTest5, EraseElement) {
    HashTable<int> table;

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

TEST(HashTableTest6, EraseNonExistent) {
    HashTable<int> table;
    EXPECT_THROW(table.erase("nonexistent"), std::logic_error);
}

TEST(HashTableTest7, FindNonExistent) {
    HashTable<int> table;
    EXPECT_THROW(table.find("nothing"), std::logic_error);
}

TEST(HashTableTest8, ConsistCheck) {
    HashTable<int> table;
    EXPECT_FALSE(table.consist("anything"));
    table.insert("key", 42);
    EXPECT_TRUE(table.consist("key"));
    EXPECT_FALSE(table.consist("other"));
    table.erase("key");
    EXPECT_FALSE(table.consist("key"));
}

TEST(HashTableTest9, IsEmpty) {
    HashTable<int> table;
    EXPECT_TRUE(table.is_empty());
    table.insert("a", 1);
    EXPECT_FALSE(table.is_empty());
    table.erase("a");
    EXPECT_TRUE(table.is_empty());
}

TEST(HashTableTest10, ManyElements) {
    HashTable<int> table(10);

    for (int i = 0; i < 100; ++i) {
        table.insert("key" + std::to_string(i), i);
    }
    EXPECT_EQ(table.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(table.consist("key" + std::to_string(i)));
        EXPECT_EQ(table.find("key" + std::to_string(i)), i);
    }
}
TEST(HashTableTest11, CollisionTest) {

    HashTable<int> table(2);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    table.insert("four", 4);
    table.insert("five", 5);

    EXPECT_EQ(table.size(), 5);
    EXPECT_EQ(table.find("one"), 1);
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("three"), 3);
    EXPECT_EQ(table.find("four"), 4);
    EXPECT_EQ(table.find("five"), 5);

    table.erase("three");
    EXPECT_EQ(table.size(), 4);
    EXPECT_FALSE(table.consist("three"));

    EXPECT_TRUE(table.consist("one"));
    EXPECT_TRUE(table.consist("two"));
    EXPECT_TRUE(table.consist("four"));
    EXPECT_TRUE(table.consist("five"));

    table.erase("one");
    EXPECT_EQ(table.size(), 3);
    EXPECT_FALSE(table.consist("one"));

    EXPECT_TRUE(table.consist("two"));
    EXPECT_TRUE(table.consist("four"));
    EXPECT_TRUE(table.consist("five"));

    table.erase("five");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("five"));

    EXPECT_TRUE(table.consist("two"));
    EXPECT_TRUE(table.consist("four"));
    EXPECT_EQ(table.find("two"), 2);
    EXPECT_EQ(table.find("four"), 4);

    EXPECT_FALSE(table.is_empty());

    table.erase("two");
    table.erase("four");
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}