#include <gtest/gtest.h>
#include "Stack.h"


TEST(StackTest, ConstructorWithSize) {
    Stack<int> stack(5);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.is_empty());
    EXPECT_TRUE(stack.is_full());
}

TEST(StackTest, PushElements) {
    Stack<int> stack(3);

    stack.push(10);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.top(), 20);

    stack.push(30);
    EXPECT_TRUE(stack.is_full());
    EXPECT_EQ(stack.top(), 30);
}

TEST(StackTest, PopElements) {
    Stack<int> stack(3);
    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.top(), 30);
    stack.pop();

    EXPECT_EQ(stack.top(), 20);
    stack.pop();

    EXPECT_EQ(stack.top(), 10);
    stack.pop();

    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, ClearStack) {
    Stack<int> stack(3);
    stack.push(10);
    stack.push(20);

    EXPECT_FALSE(stack.is_empty());
    stack.clear();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, DifferentDataTypes) {
    Stack<double> doubleStack(3);
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    EXPECT_DOUBLE_EQ(doubleStack.top(), 2.71);

    Stack<std::string> stringStack(2);
    stringStack.push("Hello");
    stringStack.push("World");
    EXPECT_EQ(stringStack.top(), "World");
}

TEST(StackTest, SequenceOfOperations) {
    Stack<int> stack(5);

    for (int i = 1; i <= 5; ++i) {
        stack.push(i * 10);
    }

    EXPECT_TRUE(stack.is_full());
    EXPECT_EQ(stack.top(), 50);

    stack.pop();
    stack.pop();

    EXPECT_EQ(stack.top(), 30);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());

    stack.push(60);
    stack.push(70);

    EXPECT_EQ(stack.top(), 70);
    EXPECT_TRUE(stack.is_full());

    stack.clear();
    EXPECT_TRUE(stack.is_empty());

    stack.push(100);
    EXPECT_EQ(stack.top(), 100);
}

TEST(StackTest, IsEmptyMethod) {
    Stack<int> stack(2);

    EXPECT_TRUE(stack.is_empty());

    stack.push(1);
    EXPECT_FALSE(stack.is_empty());

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, IsFullMethod) {
    Stack<int> stack(3);

    EXPECT_FALSE(stack.is_full());

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_TRUE(stack.is_full());

    stack.pop();
    EXPECT_FALSE(stack.is_full());
}