// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"
#define EPSILON 0.000001
#include "Stack.h"
#include "List.h"



TEST(TestLibLib, can_iterate) {

    List<int> list;
    for (int i = 0; i < 10; i++) {

        list.push_back(i + 1);

    }
    // Node<int>* cur = list._head;




}

TEST(TestStack1, can_create_stack) {

    Stack<int> stack(10);

    ASSERT_NO_THROW(stack);
}

TEST(TestStack2, can_push) {

    Stack<int> stack(3);
    stack.push(17);

    ASSERT_NO_THROW(stack);
}
TEST(TestStack3, can_pop) {

    Stack<int> stack(3);
    stack.push(17);
    stack.push(3);
    stack.push(2);
    stack.pop();

    ASSERT_NO_THROW(stack);
}

TEST(TestStack4, can_take_top) {

    Stack<int> stack(3);
    stack.push(17);
    stack.push(3);
    stack.push(2);

    EXPECT_EQ(stack.top(), 2);
}

TEST(TestStack5, check_is_full) {

    Stack<int> stack(3);
    stack.push(17);
    stack.push(3);
    stack.push(2);

    EXPECT_EQ(stack.is_full(), 1);
}

TEST(TestStack6, check_is_empty) {

    Stack<int> stack(3);

    EXPECT_EQ(stack.is_empty(), 1);
}


TEST(TestStack7, can_clear_steck) {

    Stack<int> stack(3);
    stack.push(17);
    stack.push(3);
    stack.push(2);

    stack.clear();

    EXPECT_EQ(stack.is_empty(), 1);
}


TEST(TestStack8, can_puch_after_clear) {

    Stack<int> stack(3);
    stack.push(17);
    stack.push(3);
    stack.push(2);

    stack.clear();

    stack.push(5);

    EXPECT_EQ(stack.top(), 5);
}
//TEST(TestBrackets1, 1) {
//    EXPECT_TRUE(check_algorithms("()"));
//}
//
//TEST(TestBrackets2, 2) {
//    EXPECT_TRUE(check_algorithms("(){}[]"));
//}
//
//TEST(TestBrackets3, 3) {
//    EXPECT_TRUE(check_algorithms("([{}])"));
//}
//
//TEST(TestBrackets4, 4) {
//    EXPECT_FALSE(check_algorithms("(]"));
//}
//
//TEST(TestBrackets5, 5) {
//    EXPECT_FALSE(check_algorithms("({[}])"));
//}
//
//TEST(TestBrackets6, 6) {
//    EXPECT_TRUE(check_algorithms(""));
//}
//
//TEST(TestBrackets7, 7) {
//    EXPECT_FALSE(check_algorithms("((("));
//}
//
//TEST(TestBrackets8, 8) {
//    EXPECT_FALSE(check_algorithms(")))"));
//}



