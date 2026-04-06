#define main q2_a_ll_original_main
#include "../Q2_A_LL.c"
#undef main

#include "ll_test_common.h"

static void test_alternate_merge_equal_length(void)
{
	LinkedList ll1, ll2;
	int values1[] = {1, 3, 5};
	int values2[] = {2, 4, 6};
	int expected1[] = {1, 2, 3, 4, 5, 6};

	init_list(&ll1);
	init_list(&ll2);
	append_values(&ll1, values1, 3);
	append_values(&ll2, values2, 3);

	alternateMergeLinkedList(&ll1, &ll2);

	expect_list_equals(&ll1, expected1, 6, "alternateMergeLinkedList interleaves equal-length lists into ll1");
	EXPECT_INT_EQ(0, ll2.size, "alternateMergeLinkedList empties ll2 when all nodes are consumed");
	EXPECT_NULL(ll2.head, "alternateMergeLinkedList resets ll2 head when all nodes are consumed");

	removeAllItems(&ll1);
	removeAllItems(&ll2);
}

static void test_alternate_merge_second_longer(void)
{
	LinkedList ll1, ll2;
	int values1[] = {1, 3};
	int values2[] = {2, 4, 6, 8};
	int expected1[] = {1, 2, 3, 4};
	int expected2[] = {6, 8};

	init_list(&ll1);
	init_list(&ll2);
	append_values(&ll1, values1, 2);
	append_values(&ll2, values2, 4);

	alternateMergeLinkedList(&ll1, &ll2);

	expect_list_equals(&ll1, expected1, 4, "alternateMergeLinkedList leaves merged prefix in ll1");
	expect_list_equals(&ll2, expected2, 2, "alternateMergeLinkedList keeps leftover ll2 nodes in ll2");

	removeAllItems(&ll1);
	removeAllItems(&ll2);
}

static void test_alternate_merge_first_longer(void)
{
	LinkedList ll1, ll2;
	int values1[] = {1, 3, 5, 7};
	int values2[] = {2, 4};
	int expected1[] = {1, 2, 3, 4, 5, 7};

	init_list(&ll1);
	init_list(&ll2);
	append_values(&ll1, values1, 4);
	append_values(&ll2, values2, 2);

	alternateMergeLinkedList(&ll1, &ll2);

	expect_list_equals(&ll1, expected1, 6, "alternateMergeLinkedList preserves remaining ll1 tail nodes");
	EXPECT_INT_EQ(0, ll2.size, "alternateMergeLinkedList empties ll2 when it is shorter");

	removeAllItems(&ll1);
	removeAllItems(&ll2);
}

static void test_alternate_merge_with_empty_second(void)
{
	LinkedList ll1, ll2;
	int values1[] = {10, 20, 30};

	init_list(&ll1);
	init_list(&ll2);
	append_values(&ll1, values1, 3);

	alternateMergeLinkedList(&ll1, &ll2);

	expect_list_equals(&ll1, values1, 3, "alternateMergeLinkedList leaves ll1 unchanged when ll2 is empty");
	EXPECT_INT_EQ(0, ll2.size, "alternateMergeLinkedList keeps empty ll2 size at 0");

	removeAllItems(&ll1);
	removeAllItems(&ll2);
}

int main(void)
{
	printf("Running Q2_A_LL tests...\n");

	RUN_TEST(test_alternate_merge_equal_length);
	RUN_TEST(test_alternate_merge_second_longer);
	RUN_TEST(test_alternate_merge_first_longer);
	RUN_TEST(test_alternate_merge_with_empty_second);

	return finish_test_suite("Q2_A_LL");
}
