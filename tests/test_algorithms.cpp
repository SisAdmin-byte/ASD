#include <gtest/gtest.h>
#include "Algorithms.h"

TEST(CheckBalancedBracketsTest1, BalancedSimpleParentheses) {
    EXPECT_TRUE(check_balanced_brackets("()"));
    EXPECT_TRUE(check_balanced_brackets("(())"));
    EXPECT_TRUE(check_balanced_brackets("()()"));
}

TEST(CheckBalancedBracketsTest2, BalancedMixedBrackets) {
    EXPECT_TRUE(check_balanced_brackets("{}"));
    EXPECT_TRUE(check_balanced_brackets("[]"));
    EXPECT_TRUE(check_balanced_brackets("{[()]}"));
    EXPECT_TRUE(check_balanced_brackets("[{()}]"));
}

TEST(CheckBalancedBracketsTest3, BalancedComplexExpressions) {
    EXPECT_TRUE(check_balanced_brackets("({[]})"));
    EXPECT_TRUE(check_balanced_brackets("{([])}"));
    EXPECT_TRUE(check_balanced_brackets("([{}])"));
}

TEST(CheckBalancedBracketsTest4, BalancedWithOtherCharacters) {
    EXPECT_TRUE(check_balanced_brackets("(a + b)"));
    EXPECT_TRUE(check_balanced_brackets("{a * [b + c]}"));
    EXPECT_TRUE(check_balanced_brackets("if (x > 0) { y = x * 2; }"));
}

TEST(CheckBalancedBracketsTest5, UnbalancedMissingClosing) {
    EXPECT_FALSE(check_balanced_brackets("("));
    EXPECT_FALSE(check_balanced_brackets("{"));
    EXPECT_FALSE(check_balanced_brackets("["));
    EXPECT_FALSE(check_balanced_brackets("(()"));
}

TEST(CheckBalancedBracketsTest6, UnbalancedMissingOpening) {
    EXPECT_FALSE(check_balanced_brackets(")"));
    EXPECT_FALSE(check_balanced_brackets("}"));
    EXPECT_FALSE(check_balanced_brackets("]"));
    EXPECT_FALSE(check_balanced_brackets("())"));
}

TEST(CheckBalancedBracketsTest7, UnbalancedWrongOrder) {
    EXPECT_FALSE(check_balanced_brackets(")("));
    EXPECT_FALSE(check_balanced_brackets("]["));
    EXPECT_FALSE(check_balanced_brackets("}{"));
}

TEST(CheckBalancedBracketsTest8, UnbalancedMismatchedTypes) {
    EXPECT_FALSE(check_balanced_brackets("(]"));
    EXPECT_FALSE(check_balanced_brackets("{]"));
    EXPECT_FALSE(check_balanced_brackets("[}"));
    EXPECT_FALSE(check_balanced_brackets("{)"));
}

TEST(CheckBalancedBracketsTest9, UnbalancedNestedMismatch) {
    EXPECT_FALSE(check_balanced_brackets("{[}]"));
    EXPECT_FALSE(check_balanced_brackets("({[}])"));
    EXPECT_FALSE(check_balanced_brackets("[(])"));
}

TEST(CheckBalancedBracketsTest10, EmptyString) {
    EXPECT_TRUE(check_balanced_brackets(""));
}

TEST(CheckBalancedBracketsTest11, NoBrackets) {
    EXPECT_TRUE(check_balanced_brackets("abc"));
    EXPECT_TRUE(check_balanced_brackets("123"));
    EXPECT_TRUE(check_balanced_brackets("hello world"));
}

TEST(CheckBalancedBracketsTest12, MixedBalanced) {
    EXPECT_TRUE(check_balanced_brackets("([]){()}"));
    EXPECT_TRUE(check_balanced_brackets("({[]})()"));
    EXPECT_TRUE(check_balanced_brackets("(([]){})"));
}