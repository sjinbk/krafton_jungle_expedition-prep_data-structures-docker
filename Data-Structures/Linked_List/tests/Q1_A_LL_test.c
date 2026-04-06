#define main q1_a_ll_original_main
#include "../Q1_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_insert_sorted_empty(void)
{
	LinkedList ll;
	int actual_index;
	int expected[] = {5};

	init_list(&ll);
	actual_index = insertSortedLL(&ll, 5);

	EXPECT_INT_EQ(0, actual_index, "insertSortedLL inserts first value at index 0");
	EXPECT_INT_EQ(1, ll.size, "insertSortedLL updates size for first insertion");
	expect_list_equals(&ll, expected, 1, "insertSortedLL stores the first value correctly");

	removeAllItems(&ll);
}

static void test_insert_sorted_positions(void)
{
	LinkedList ll;
	int expected[] = {1, 3, 5, 7};

	init_list(&ll);

	EXPECT_INT_EQ(0, insertSortedLL(&ll, 3), "insertSortedLL returns index 0 for first insert");
	EXPECT_INT_EQ(0, insertSortedLL(&ll, 1), "insertSortedLL inserts smaller value at head");
	EXPECT_INT_EQ(2, insertSortedLL(&ll, 7), "insertSortedLL inserts larger value at tail");
	EXPECT_INT_EQ(2, insertSortedLL(&ll, 5), "insertSortedLL inserts middle value at correct index");
	expect_list_equals(&ll, expected, 4, "insertSortedLL keeps list sorted across head, middle, tail inserts");

	removeAllItems(&ll);
}

static void test_insert_sorted_duplicates(void)
{
	LinkedList ll;
	int expected[] = {2, 4, 4, 4, 6};

	init_list(&ll);

	insertSortedLL(&ll, 4);
	insertSortedLL(&ll, 2);
	insertSortedLL(&ll, 6);
	EXPECT_INT_EQ(2, insertSortedLL(&ll, 4), "insertSortedLL appends duplicate after existing equal value");
	EXPECT_INT_EQ(3, insertSortedLL(&ll, 4), "insertSortedLL keeps duplicate insertion order stable");
	expect_list_equals(&ll, expected, 5, "insertSortedLL preserves sorted order with duplicates");

	removeAllItems(&ll);
}

static void test_insert_sorted_mixed_signs(void)
{
	LinkedList ll;
	int expected[] = {-10, -3, 0, 7, 8};

	init_list(&ll);

	insertSortedLL(&ll, 7);
	insertSortedLL(&ll, -3);
	insertSortedLL(&ll, 0);
	insertSortedLL(&ll, 8);
	EXPECT_INT_EQ(0, insertSortedLL(&ll, -10), "insertSortedLL places negative minimum at head");
	expect_list_equals(&ll, expected, 5, "insertSortedLL keeps mixed negative and positive values sorted");

	removeAllItems(&ll);
}

static void test_insert_sorted_null_list(void)
{
	EXPECT_INT_EQ(-1, insertSortedLL(NULL, 42), "insertSortedLL returns -1 for NULL list");
}

int main(void)
{
	printf("Running Q1_A_LL tests...\n");

	RUN_TEST(test_insert_sorted_empty);
	RUN_TEST(test_insert_sorted_positions);
	RUN_TEST(test_insert_sorted_duplicates);
	RUN_TEST(test_insert_sorted_mixed_signs);
	RUN_TEST(test_insert_sorted_null_list);

	return finish_test_suite("Q1_A_LL");
}
