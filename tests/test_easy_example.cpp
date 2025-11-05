// Copyright 2024 Marina Usova

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"
#define EPSILON 0.000001
#include "Queue.h"
#include "Stack.h"
#include "List.h"



TEST(TestLibLib, can_iterate) {

    List<int> list;
    for (int i = 0; i < 10; i++) {

        list.push_back(i + 1);

    }
    // Node<int>* cur = list._head;




}

TEST(TestQueue1, can_create_queue) {
    Queue<int> queue(10);
    ASSERT_NO_THROW(queue);
}

TEST(TestQueue2, can_enqueue) {
    Queue<int> queue(3);
    queue.enqueue(17);
    ASSERT_NO_THROW(queue);
}

TEST(TestQueue3, can_dequeue) {
    Queue<int> queue(3);
    queue.enqueue(17);
    queue.enqueue(3);
    queue.enqueue(2);
    int result = queue.dequeue();
    ASSERT_NO_THROW(queue);
    EXPECT_EQ(result, 17);
}

TEST(TestQueue4, can_take_front) {
    Queue<int> queue(3);
    queue.enqueue(17);
    queue.enqueue(3);
    queue.enqueue(2);
    EXPECT_EQ(queue.front(), 17);
}

TEST(TestQueue6, check_is_empty) {
    Queue<int> queue(3);
    EXPECT_EQ(queue.empty(), true);
}

TEST(TestQueue7, check_is_full) {
    Queue<int> queue(3);
    queue.enqueue(17);
    queue.enqueue(3);
    queue.enqueue(2);
    EXPECT_EQ(queue.full(), true);
}

TEST(TestQueue8, can_clear_queue) {
    Queue<int> queue(3);
    queue.enqueue(17);
    queue.enqueue(3);
    queue.enqueue(2);
    queue.clear();
    EXPECT_EQ(queue.empty(), true);
}

TEST(TestQueue9, can_enqueue_after_clear) {
    Queue<int> queue(3);
    queue.enqueue(17);
    queue.enqueue(3);
    queue.enqueue(2);
    queue.clear();
    queue.enqueue(5);
    EXPECT_EQ(queue.front(), 5);
}

TEST(TestQueue10, can_get_size) {
    Queue<int> queue(3);
    queue.enqueue(17);
    queue.enqueue(3);
    EXPECT_EQ(queue.size(), 2);
}

TEST(TestQueue11, can_get_capacity) {
    Queue<int> queue(7);
    EXPECT_EQ(queue.capacity(), 7);
}

TEST(TestQueue12, fifo_order) {
    Queue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_EQ(queue.dequeue(), 1);
    EXPECT_EQ(queue.dequeue(), 2);
    EXPECT_EQ(queue.dequeue(), 3);
}



TEST(TestQueue16, auto_resize) {
    Queue<int> queue(2);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.capacity(), 4);
}

TEST(TestQueue17, circular_behavior) {
    Queue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();
    queue.enqueue(4);
    EXPECT_EQ(queue.front(), 2);
    EXPECT_EQ(queue.back(), 4);
}

TEST(TestQueue18, dequeue_from_empty) {
    Queue<int> queue(3);
    EXPECT_THROW(queue.dequeue(), std::runtime_error);
}

TEST(TestQueue19, front_from_empty) {
    Queue<int> queue(3);
    EXPECT_THROW(queue.front(), std::runtime_error);
}

TEST(TestQueue20, back_from_empty) {
    Queue<int> queue(3);
    EXPECT_THROW(queue.back(), std::runtime_error);
}

TEST(TestQueue21, multiple_operations) {
    Queue<int> queue(5);
    for (int i = 0; i < 10; i++) {
        queue.enqueue(i);
        if (i % 3 == 0) {
            queue.dequeue();
        }
    }
    ASSERT_NO_THROW(queue);
}

TEST(TestQueue24, clear_preserves_capacity) {
    Queue<int> queue(7);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    int old_capacity = queue.capacity();
    queue.clear();
    EXPECT_EQ(queue.capacity(), old_capacity);
    EXPECT_TRUE(queue.empty());
}

TEST(TestQueue25, size_after_multiple_dequeues) {
    Queue<int> queue(5);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();
    queue.dequeue();
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 3);
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



