#include <gtest/gtest.h>
#include "doublyList.h"


TEST(IteratorTest1, ForwardTraversal) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(IteratorTest2, PostIncrement) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    auto it = list.begin();
    EXPECT_EQ(*(it++), 10);
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*(it++), 20);
    EXPECT_EQ(it, list.end());
}

TEST(IteratorTest3, ReverseTraversal) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto rit = list.rbegin();
    EXPECT_EQ(*rit, 3);
    ++rit;
    //EXPECT_EQ(*rit, 2);
    //++rit;
    //EXPECT_EQ(*rit, 1);
    //++rit;
    //EXPECT_EQ(rit, list.rend());

}

TEST(IteratorTest4, Modification) {
    List<int> list;
    list.push_back(5);
    list.push_back(15);

    auto it = list.begin();
    *it = 50;
    EXPECT_EQ(list.front(), 50);

    ++it;
    *it = 150;
    EXPECT_EQ(list.back(), 150);
}

TEST(IteratorTest6, EmptyList) {
    List<int> list;
    EXPECT_EQ(list.begin(), list.end());
    EXPECT_EQ(list.rbegin(), list.rend());

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

TEST(IteratorTest7, Equality) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2);

    ++it1;
    EXPECT_NE(it1, it2);

    ++it2;
    EXPECT_EQ(it1, it2);
}