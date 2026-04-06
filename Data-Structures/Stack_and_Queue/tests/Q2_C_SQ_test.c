#define main q2_c_sq_original_main
#include "../Q2_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void init_stack(Stack *s)
{
	init_basic_list(&(s->ll));
}

static void test_create_stack_pushes_in_list_traversal_order(void)
{
	LinkedList ll;
	Stack s;
	int values[] = {10, 20, 30, 40};
	int expected_stack[] = {40, 30, 20, 10};

	init_basic_list(&ll);
	init_stack(&s);
	append_values(&ll, values, 4);

	createStackFromLinkedList(&ll, &s);

	expect_list_equals(&(s.ll), expected_stack, 4, "createStackFromLinkedList pushes first list node first and last list node becomes stack top");
	expect_list_equals(&ll, values, 4, "createStackFromLinkedList does not modify the source linked list");

	removeAllItemsFromStack(&s);
	removeAllItems(&ll);
}

static void test_create_stack_clears_existing_stack_first(void)
{
	LinkedList ll;
	Stack s;
	int values[] = {1, 2, 3};
	int stale_stack[] = {99, 88};
	int expected_stack[] = {3, 2, 1};

	init_basic_list(&ll);
	init_stack(&s);
	append_values(&ll, values, 3);
	append_values(&(s.ll), stale_stack, 2);

	createStackFromLinkedList(&ll, &s);

	expect_list_equals(&(s.ll), expected_stack, 3, "createStackFromLinkedList clears old stack contents before pushing new values");

	removeAllItemsFromStack(&s);
	removeAllItems(&ll);
}

static void test_create_stack_from_empty_list(void)
{
	LinkedList ll;
	Stack s;
	int stale_stack[] = {4, 5};

	init_basic_list(&ll);
	init_stack(&s);
	append_values(&(s.ll), stale_stack, 2);

	createStackFromLinkedList(&ll, &s);

	EXPECT_INT_EQ(0, s.ll.size, "createStackFromLinkedList leaves stack empty for an empty source list");
	EXPECT_NULL(s.ll.head, "createStackFromLinkedList resets stack head for an empty source list");

	removeAllItemsFromStack(&s);
	removeAllItems(&ll);
}

static void test_remove_even_values_keeps_odd_stack_order(void)
{
	Stack s;
	int initial_stack[] = {7, 6, 5, 4, 3, 2};
	int expected[] = {7, 5, 3};

	init_stack(&s);
	append_values(&(s.ll), initial_stack, 6);

	removeEvenValues(&s);

	expect_list_equals(&(s.ll), expected, 3, "removeEvenValues removes even stack items and preserves odd top-to-bottom order");

	removeAllItemsFromStack(&s);
}

static void test_remove_even_values_all_even(void)
{
	Stack s;
	int initial_stack[] = {8, 6, 4};

	init_stack(&s);
	append_values(&(s.ll), initial_stack, 3);

	removeEvenValues(&s);

	EXPECT_INT_EQ(0, s.ll.size, "removeEvenValues empties the stack when every value is even");
	EXPECT_NULL(s.ll.head, "removeEvenValues leaves stack head NULL when every value is even");

	removeAllItemsFromStack(&s);
}

int main(void)
{
	printf("Running Q2_C_SQ tests...\n");

	RUN_TEST(test_create_stack_pushes_in_list_traversal_order);
	RUN_TEST(test_create_stack_clears_existing_stack_first);
	RUN_TEST(test_create_stack_from_empty_list);
	RUN_TEST(test_remove_even_values_keeps_odd_stack_order);
	RUN_TEST(test_remove_even_values_all_even);

	return finish_test_suite("Q2_C_SQ");
}
