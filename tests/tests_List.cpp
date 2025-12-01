#include <gtest/gtest.h>
#include "List.h"


TEST(TestList1, can_iterate) {

	List<int> list;
	ASSERT_NO_THROW(list);


}

TEST(TestList2, can_push_front) {

	List<int> list;
	list.push_front(20);
	EXPECT_EQ(list.front(), 20);


}

TEST(TestList3, can_push_back) {

	List<int> list;
	list.push_front(20);
	list.push_back(10);
	EXPECT_EQ(list.back(), 10);


}


TEST(TestList4, can_delete_when_empty) {

	List<int> list;
	
	ASSERT_ANY_THROW(list.pop_front());


}

TEST(TestList5, can_delete_when_empty) {

	List<int> list;

	ASSERT_ANY_THROW(list.pop_back());


}

