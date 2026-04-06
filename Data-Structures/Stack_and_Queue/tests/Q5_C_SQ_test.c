#define main q5_c_sq_original_main
#include "../Q5_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void init_queue(Queue *q)
{
	init_basic_list(&(q->ll));
}

static void test_recursive_reverse_multiple_items(void)
{
	Queue q;
	int values[] = {3, 1, 4, 1};
	int expected[] = {1, 4, 1, 3};

	init_queue(&q);
	append_values(&(q.ll), values, 4);

	recursiveReverse(&q);

	expect_list_equals(&(q.ll), expected, 4, "recursiveReverse reverses a queue recursively");

	removeAllItemsFromQueue(&q);
}

static void test_recursive_reverse_single_item(void)
{
	Queue q;
	int values[] = {8};

	init_queue(&q);
	append_values(&(q.ll), values, 1);

	recursiveReverse(&q);

	expect_list_equals(&(q.ll), values, 1, "recursiveReverse leaves a single-item queue unchanged");

	removeAllItemsFromQueue(&q);
}

static void test_recursive_reverse_empty_queue(void)
{
	Queue q;

	init_queue(&q);
	recursiveReverse(&q);

	EXPECT_INT_EQ(0, q.ll.size, "recursiveReverse keeps an empty queue size at 0");
	EXPECT_NULL(q.ll.head, "recursiveReverse keeps an empty queue head NULL");

	removeAllItemsFromQueue(&q);
}

int main(void)
{
	printf("Running Q5_C_SQ tests...\n");

	RUN_TEST(test_recursive_reverse_multiple_items);
	RUN_TEST(test_recursive_reverse_single_item);
	RUN_TEST(test_recursive_reverse_empty_queue);

	return finish_test_suite("Q5_C_SQ");
}
