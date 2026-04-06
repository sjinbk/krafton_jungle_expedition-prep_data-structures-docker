#define main q7_a_ll_original_main
#include "../Q7_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_recursive_reverse_multiple_nodes(void)
{
	LinkedList ll;
	int values[] = {1, 2, 3, 4};
	int expected[] = {4, 3, 2, 1};

	init_list(&ll);
	append_values(&ll, values, 4);

	RecursiveReverse(&(ll.head));

	expect_list_equals(&ll, expected, 4, "RecursiveReverse reverses a multi-node list");

	removeAllItems(&ll);
}

static void test_recursive_reverse_single_node(void)
{
	LinkedList ll;
	int values[] = {5};

	init_list(&ll);
	append_values(&ll, values, 1);

	RecursiveReverse(&(ll.head));

	expect_list_equals(&ll, values, 1, "RecursiveReverse leaves a single-node list unchanged");

	removeAllItems(&ll);
}

static void test_recursive_reverse_empty_list(void)
{
	LinkedList ll;

	init_list(&ll);
	RecursiveReverse(&(ll.head));

	EXPECT_NULL(ll.head, "RecursiveReverse keeps an empty list head as NULL");
	EXPECT_INT_EQ(0, ll.size, "RecursiveReverse keeps an empty list size at 0");
}

int main(void)
{
	printf("Running Q7_A_LL tests...\n");

	RUN_TEST(test_recursive_reverse_multiple_nodes);
	RUN_TEST(test_recursive_reverse_single_node);
	RUN_TEST(test_recursive_reverse_empty_list);

	return finish_test_suite("Q7_A_LL");
}
