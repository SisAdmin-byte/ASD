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

TEST(UnsortedTableOnTreeTest5, LargeNumberOfElements) {
    UnsortedTableOnTree<int, int> table;

    // Вставляем 500 элементов
    for (int i = 0; i < 500; i++) {
        table.insert(i, i * 10);
    }

    EXPECT_EQ(table.size(), 500);

    // Проверяем все элементы
    for (int i = 0; i < 500; i++) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), i * 10);
    }

    // Удаляем каждый второй элемент
    for (int i = 0; i < 500; i += 2) {
        table.erase(i);
    }

    EXPECT_EQ(table.size(), 250);

    // Проверяем результаты
    for (int i = 0; i < 500; i++) {
        if (i % 2 == 0) {
            EXPECT_FALSE(table.consist(i));
        }
        else {
            EXPECT_TRUE(table.consist(i));
            EXPECT_EQ(table.find(i), i * 10);
        }
    }
}

TEST(UnsortedTableOnTreeTest6, TreeTraversals) {
    UnsortedTableOnTree<std::string, int> table;

    table.insert("first", 1);
    table.insert("second", 2);
    table.insert("third", 3);

    // Проверяем, что можно вывести обходы (просто проверяем, что не падает)
    testing::internal::CaptureStdout();
    table.print_all_traversals();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST(UnsortedTableOnTreeTest7, PrettyPrint) {
    UnsortedTableOnTree<int, int> table;

    table.insert(5, 50);
    table.insert(1, 10);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(2, 20);
    table.insert(4, 40);

    // Проверяем, что красивый вывод работает
    testing::internal::CaptureStdout();
    table.print_tree_pretty();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}