#define main q4_a_ll_original_main
#include "../Q4_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_move_even_items_to_back_partition(void)
{
	LinkedList ll;
	int values[] = {1, 2, 3, 4, 5, 6};
	int expected[] = {1, 3, 5, 2, 4, 6};

	init_list(&ll);
	append_values(&ll, values, 6);

	moveEvenItemsToBack(&ll);

	expect_list_equals(&ll, expected, 6, "moveEvenItemsToBack keeps odds first and evens at the back");

	removeAllItems(&ll);
}

static void test_move_even_items_to_back_all_even(void)
{
	LinkedList ll;
	int values[] = {2, 4, 6};

	init_list(&ll);
	append_values(&ll, values, 3);

	moveEvenItemsToBack(&ll);

	expect_list_equals(&ll, values, 3, "moveEvenItemsToBack leaves an all-even list unchanged");

	removeAllItems(&ll);
}

static void test_move_even_items_to_back_all_odd(void)
{
	LinkedList ll;
	int values[] = {1, 3, 5};

	init_list(&ll);
	append_values(&ll, values, 3);

	moveEvenItemsToBack(&ll);

	expect_list_equals(&ll, values, 3, "moveEvenItemsToBack leaves an all-odd list unchanged");

	removeAllItems(&ll);
}

static void test_move_even_items_to_back_empty(void)
{
	LinkedList ll;

	init_list(&ll);
	moveEvenItemsToBack(&ll);

	EXPECT_INT_EQ(0, ll.size, "moveEvenItemsToBack keeps an empty list size at 0");
	EXPECT_NULL(ll.head, "moveEvenItemsToBack keeps an empty list head as NULL");
}

int main(void)
{
	printf("Running Q4_A_LL tests...\n");

	RUN_TEST(test_move_even_items_to_back_partition);
	RUN_TEST(test_move_even_items_to_back_all_even);
	RUN_TEST(test_move_even_items_to_back_all_odd);
	RUN_TEST(test_move_even_items_to_back_empty);

	return finish_test_suite("Q4_A_LL");
}
