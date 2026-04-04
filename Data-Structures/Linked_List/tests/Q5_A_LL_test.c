#define main q5_a_ll_original_main
#include "../Q5_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_front_back_split_even_count(void)
{
	LinkedList ll, front, back;
	int values[] = {1, 2, 3, 4};
	int expected_front[] = {1, 2};
	int expected_back[] = {3, 4};

	init_list(&ll);
	init_list(&front);
	init_list(&back);
	append_values(&ll, values, 4);

	frontBackSplitLinkedList(&ll, &front, &back);

	expect_list_equals(&front, expected_front, 2, "frontBackSplitLinkedList stores the first half in front list");
	expect_list_equals(&back, expected_back, 2, "frontBackSplitLinkedList stores the second half in back list");

	removeAllItems(&ll);
	removeAllItems(&front);
	removeAllItems(&back);
}

static void test_front_back_split_odd_count(void)
{
	LinkedList ll, front, back;
	int values[] = {1, 2, 3, 4, 5};
	int expected_front[] = {1, 2, 3};
	int expected_back[] = {4, 5};

	init_list(&ll);
	init_list(&front);
	init_list(&back);
	append_values(&ll, values, 5);

	frontBackSplitLinkedList(&ll, &front, &back);

	expect_list_equals(&front, expected_front, 3, "frontBackSplitLinkedList gives the extra node to the front list");
	expect_list_equals(&back, expected_back, 2, "frontBackSplitLinkedList keeps the remaining nodes in the back list");

	removeAllItems(&ll);
	removeAllItems(&front);
	removeAllItems(&back);
}

static void test_front_back_split_empty_list(void)
{
	LinkedList ll, front, back;

	init_list(&ll);
	init_list(&front);
	init_list(&back);

	frontBackSplitLinkedList(&ll, &front, &back);

	EXPECT_INT_EQ(0, front.size, "frontBackSplitLinkedList keeps empty front size at 0");
	EXPECT_INT_EQ(0, back.size, "frontBackSplitLinkedList keeps empty back size at 0");

	removeAllItems(&ll);
	removeAllItems(&front);
	removeAllItems(&back);
}

int main(void)
{
	printf("Running Q5_A_LL tests...\n");

	test_front_back_split_even_count();
	test_front_back_split_odd_count();
	test_front_back_split_empty_list();

	return finish_test_suite("Q5_A_LL");
}
