#define main q4_c_sq_original_main
#include "../Q4_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void init_queue(Queue *q)
{
	init_basic_list(&(q->ll));
	q->ll.tail = NULL;
}

static void test_reverse_multiple_items(void)
{
	Queue q;
	int values[] = {1, 2, 3, 4};
	int expected[] = {4, 3, 2, 1};

	init_queue(&q);
	append_values(&(q.ll), values, 4);

	reverse(&q);

	expect_list_equals(&(q.ll), expected, 4, "reverse flips a queue with multiple items");

	removeAllItems(&(q.ll));
}

static void test_reverse_single_item(void)
{
	Queue q;
	int values[] = {9};

	init_queue(&q);
	append_values(&(q.ll), values, 1);

	reverse(&q);

	expect_list_equals(&(q.ll), values, 1, "reverse leaves a single-item queue unchanged");

	removeAllItems(&(q.ll));
}

static void test_reverse_empty_queue(void)
{
	Queue q;

	init_queue(&q);
	reverse(&q);

	EXPECT_INT_EQ(0, q.ll.size, "reverse keeps an empty queue size at 0");
	EXPECT_NULL(q.ll.head, "reverse keeps an empty queue head NULL");

	removeAllItems(&(q.ll));
}

int main(void)
{
	printf("Running Q4_C_SQ tests...\n");

	RUN_TEST(test_reverse_multiple_items);
	RUN_TEST(test_reverse_single_item);
	RUN_TEST(test_reverse_empty_queue);

	return finish_test_suite("Q4_C_SQ");
}
