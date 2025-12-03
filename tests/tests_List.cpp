#include <gtest/gtest.h>
#include "List.h"

TEST(ListTest1, DefaultConstructor) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest2, PushFrontSingle) {
    List<int> list;
    list.push_front(42);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.back(), 42);
}

TEST(ListTest3, PushBackSingle) {
    List<int> list;
    list.push_back(42);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.back(), 42);
}

TEST(ListTest4, PushFrontMultiple) {
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest5, PushBackMultiple) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest6, MixedPushOperations) {
    List<int> list;
    list.push_front(2);
    list.push_back(3);
    list.push_front(1);
    list.push_back(4);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 4);
}

TEST(ListTest7, PopFront) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);

    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

TEST(ListTest8, PopBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);

    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(ListTest9, PopFrontEmptyThrows) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), const char*);
}

TEST(ListTest10, PopBackEmptyThrows) {
    List<int> list;
    EXPECT_THROW(list.pop_back(), const char*);
}

TEST(ListTest11, FrontEmptyThrows) {
    List<int> list;
    EXPECT_THROW(list.front(), const char*);
}

TEST(ListTest12, BackEmptyThrows) {
    List<int> list;
    EXPECT_THROW(list.back(), const char*);
}

TEST(ListTest13, FindExisting) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* found = list.find(2);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->value, 2);
}

TEST(ListTest14, FindNonExisting) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    Node<int>* found = list.find(3);
    EXPECT_EQ(found, nullptr);
}

TEST(ListTest15, FindInEmpty) {
    List<int> list;
    Node<int>* found = list.find(1);
    EXPECT_EQ(found, nullptr);
}

TEST(ListTest16, InsertAtFront) {
    List<int> list;
    list.push_back(2);
    list.insert(0, 1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}
