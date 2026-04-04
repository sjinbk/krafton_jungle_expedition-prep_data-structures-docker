#define main q3_a_ll_original_main
#include "../Q3_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_move_odd_items_to_back_partition(void)
{
	LinkedList ll;
	int values[] = {1, 2, 3, 4, 5, 6};
	int expected[] = {2, 4, 6, 1, 3, 5};

	init_list(&ll);
	append_values(&ll, values, 6);

	moveOddItemsToBack(&ll);

	expect_list_equals(&ll, expected, 6, "moveOddItemsToBack keeps evens first and odds at the back");

	removeAllItems(&ll);
}

static void test_move_odd_items_to_back_all_odd(void)
{
	LinkedList ll;
	int values[] = {1, 3, 5};

	init_list(&ll);
	append_values(&ll, values, 3);

	moveOddItemsToBack(&ll);

	expect_list_equals(&ll, values, 3, "moveOddItemsToBack leaves an all-odd list unchanged");

	removeAllItems(&ll);
}

static void test_move_odd_items_to_back_all_even(void)
{
	LinkedList ll;
	int values[] = {2, 4, 6};

	init_list(&ll);
	append_values(&ll, values, 3);

	moveOddItemsToBack(&ll);

	expect_list_equals(&ll, values, 3, "moveOddItemsToBack leaves an all-even list unchanged");

	removeAllItems(&ll);
}

static void test_move_odd_items_to_back_empty(void)
{
	LinkedList ll;

	init_list(&ll);
	moveOddItemsToBack(&ll);

	EXPECT_INT_EQ(0, ll.size, "moveOddItemsToBack keeps an empty list size at 0");
	EXPECT_NULL(ll.head, "moveOddItemsToBack keeps an empty list head as NULL");
}

int main(void)
{
	printf("Running Q3_A_LL tests...\n");

	test_move_odd_items_to_back_partition();
	test_move_odd_items_to_back_all_odd();
	test_move_odd_items_to_back_all_even();
	test_move_odd_items_to_back_empty();

	return finish_test_suite("Q3_A_LL");
}
