#include "doublyList.h"
#include <gtest/gtest.h>

TEST(ListCycleTest, FloydMethod_NoCycleInNormalList) {
    List<int> list;
    for (int i = 1; i <= 5; i++) {
        list.push_back(i);
    }
    EXPECT_FALSE(list.has_cycle_floyd());
}

TEST(ListCycleTest, FloydMethod_FindsCycle) {
    List<int> list;
    for (int i = 1; i <= 5; i++) {
        list.push_back(i);
    }


}

//TEST(ListCycleTest, ReverseMethod_NoCycleInEmptyList) {
//    List<int> list;
//    EXPECT_FALSE(list.has_cycle_reverse());
//}
//
//TEST(ListCycleTest, ReverseMethod_FindsCycleAtStart) {
//    List<int> list;
//    for (int i = 1; i <= 5; i++) {
//        list.push_back(i);
//    }
//    EXPECT_TRUE(list.has_cycle_reverse());
//}
//
//TEST(ListCycleTest, FindCycleStart_ReturnsEndWhenNoCycle) {
//    List<int> list;
//    for (int i = 1; i <= 3; i++) {
//        list.push_back(i);
//    }
//    auto result = list.find_cycle_start();
//    EXPECT_EQ(result, list.end());
//}
//
//TEST(ListCycleTest, FindCycleStart_ReturnsCorrectNode) {
//    List<int> list;
//    for (int i = 1; i <= 5; i++) {
//        list.push_back(i);
//    }
//    auto result = list.find_cycle_start();
//    EXPECT_NE(result, list.end());
//    EXPECT_EQ(*result, 2);
//}