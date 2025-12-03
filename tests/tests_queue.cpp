#include <gtest/gtest.h>
#include "Queue.h"

TEST(QueueTest, DefaultConstructor) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.capacity(), 15);
}

TEST(QueueTest, ParameterizedConstructor) {
    Queue<int> q(10);
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_EQ(q.capacity(), 10);
}

TEST(QueueTest, EnqueueAndSize) {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQ(q.size(), 3);
    EXPECT_FALSE(q.empty());
}

TEST(QueueTest, Dequeue) {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    EXPECT_EQ(q.dequeue(), 10);
    EXPECT_EQ(q.dequeue(), 20);
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, FrontAndBack) {
    Queue<int> q;
    q.enqueue(100);
    q.enqueue(200);
    q.enqueue(300);
    EXPECT_EQ(q.front(), 100);
    EXPECT_EQ(q.back(), 300);
    q.dequeue();
    EXPECT_EQ(q.front(), 200);
    EXPECT_EQ(q.back(), 300);
}

TEST(QueueTest, FullAndEmpty) {
    Queue<int> q(3);
    EXPECT_TRUE(q.empty());
    EXPECT_FALSE(q.full());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_FALSE(q.empty());
    EXPECT_TRUE(q.full());
}

TEST(QueueTest, Clear) {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> q1(5);
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.dequeue();
    Queue<int> q2(q1);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 2);
    EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, CopyAssignment) {
    Queue<int> q1(5);
    q1.enqueue(10);
    q1.enqueue(20);
    Queue<int> q2;
    q2 = q1;
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 10);
    EXPECT_EQ(q2.back(), 20);
    q1.dequeue();
    EXPECT_EQ(q2.size(), 2);
}

TEST(QueueTest, MoveAssignment) {
    Queue<int> q1(5);
    q1.enqueue(100);
    q1.enqueue(200);
    Queue<int> q2;
    q2 = std::move(q1);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 100);
    EXPECT_EQ(q2.back(), 200);
    EXPECT_EQ(q1.size(), 0);
    EXPECT_EQ(q1.capacity(), 0);
}

TEST(QueueTest, CircularBehavior) {
    Queue<int> q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.dequeue();
    q.enqueue(4);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, ExceptionOnEmptyDequeue) {
    Queue<int> q;
    EXPECT_THROW(q.dequeue(), std::runtime_error);
}

TEST(QueueTest, ExceptionOnEmptyFront) {
    Queue<int> q;
    EXPECT_THROW(q.front(), std::runtime_error);
}

TEST(QueueTest, ExceptionOnEmptyBack) {
    Queue<int> q;
    EXPECT_THROW(q.back(), std::runtime_error);
}

TEST(QueueTest, ConstFrontAndBack) {
    Queue<int> q;
    q.enqueue(42);
    q.enqueue(99);
    const Queue<int>& const_q = q;
    EXPECT_EQ(const_q.front(), 42);
    EXPECT_EQ(const_q.back(), 99);
}

TEST(QueueTest, MultipleEnqueueDequeue) {
    Queue<int> q(5);
    for (int i = 0; i < 100; ++i) {
        q.enqueue(i);
        q.enqueue(i + 1);
        q.dequeue();
    }
    EXPECT_EQ(q.size(), 1);
}