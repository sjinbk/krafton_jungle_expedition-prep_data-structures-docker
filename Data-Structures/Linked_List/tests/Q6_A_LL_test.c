#define main q6_a_ll_original_main
#include "../Q6_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_move_max_to_front_from_middle(void)
{
	LinkedList ll;
	int values[] = {3, 1, 5, 2};
	int expected[] = {5, 3, 1, 2};

	init_list(&ll);
	append_values(&ll, values, 4);

	moveMaxToFront(&(ll.head));

	expect_list_equals(&ll, expected, 4, "moveMaxToFront moves the largest value from the middle to the head");

	removeAllItems(&ll);
}

static void test_move_max_to_front_when_already_head(void)
{
	LinkedList ll;
	int values[] = {9, 1, 4};

	init_list(&ll);
	append_values(&ll, values, 3);

	moveMaxToFront(&(ll.head));

	expect_list_equals(&ll, values, 3, "moveMaxToFront leaves the list unchanged when max is already first");

	removeAllItems(&ll);
}

static void test_move_max_to_front_single_node(void)
{
	LinkedList ll;
	int values[] = {7};

	init_list(&ll);
	append_values(&ll, values, 1);

	moveMaxToFront(&(ll.head));

	expect_list_equals(&ll, values, 1, "moveMaxToFront leaves a single-node list unchanged");

	removeAllItems(&ll);
}

static void test_move_max_to_front_empty_list(void)
{
	LinkedList ll;

	init_list(&ll);
	moveMaxToFront(&(ll.head));

	EXPECT_NULL(ll.head, "moveMaxToFront keeps an empty list head as NULL");
}

int main(void)
{
	printf("Running Q6_A_LL tests...\n");

	test_move_max_to_front_from_middle();
	test_move_max_to_front_when_already_head();
	test_move_max_to_front_single_node();
	test_move_max_to_front_empty_list();

	return finish_test_suite("Q6_A_LL");
}
