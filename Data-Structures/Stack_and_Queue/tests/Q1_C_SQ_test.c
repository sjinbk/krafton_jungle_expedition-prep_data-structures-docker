#define main q1_c_sq_original_main
#include "../Q1_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void init_queue(Queue *q)
{
	init_basic_list(&(q->ll));
}

static void test_create_queue_copies_list_order(void)
{
	LinkedList ll;
	Queue q;
	int values[] = {4, 1, 7, 2};

	init_basic_list(&ll);
	init_queue(&q);
	append_values(&ll, values, 4);

	createQueueFromLinkedList(&ll, &q);

	expect_list_equals(&(q.ll), values, 4, "createQueueFromLinkedList enqueues linked-list values in original order");
	expect_list_equals(&ll, values, 4, "createQueueFromLinkedList does not modify the source linked list");

	removeAllItemsFromQueue(&q);
	removeAllItems(&ll);
}

static void test_create_queue_clears_existing_queue_first(void)
{
	LinkedList ll;
	Queue q;
	int source[] = {9, 8, 7};
	int stale[] = {1, 2};

	init_basic_list(&ll);
	init_queue(&q);
	append_values(&ll, source, 3);
	append_values(&(q.ll), stale, 2);

	createQueueFromLinkedList(&ll, &q);

	expect_list_equals(&(q.ll), source, 3, "createQueueFromLinkedList clears old queue contents before enqueueing");

	removeAllItemsFromQueue(&q);
	removeAllItems(&ll);
}

static void test_create_queue_from_empty_list(void)
{
	LinkedList ll;
	Queue q;
	int stale[] = {5, 6};

	init_basic_list(&ll);
	init_queue(&q);
	append_values(&(q.ll), stale, 2);

	createQueueFromLinkedList(&ll, &q);

	EXPECT_INT_EQ(0, q.ll.size, "createQueueFromLinkedList leaves queue empty for an empty source list");
	EXPECT_NULL(q.ll.head, "createQueueFromLinkedList resets queue head for an empty source list");

	removeAllItemsFromQueue(&q);
	removeAllItems(&ll);
}

static void test_remove_odd_values_keeps_even_order(void)
{
	Queue q;
	int values[] = {1, 2, 3, 4, 5, 6};
	int expected[] = {2, 4, 6};

	init_queue(&q);
	append_values(&(q.ll), values, 6);

	removeOddValues(&q);

	expect_list_equals(&(q.ll), expected, 3, "removeOddValues removes odd queue items and preserves even order");

	removeAllItemsFromQueue(&q);
}

static void test_remove_odd_values_all_odd(void)
{
	Queue q;
	int values[] = {9, 7, 5};

	init_queue(&q);
	append_values(&(q.ll), values, 3);

	removeOddValues(&q);

	EXPECT_INT_EQ(0, q.ll.size, "removeOddValues empties the queue when every value is odd");
	EXPECT_NULL(q.ll.head, "removeOddValues leaves queue head NULL when every value is odd");

	removeAllItemsFromQueue(&q);
}

int main(void)
{
	printf("Running Q1_C_SQ tests...\n");

	RUN_TEST(test_create_queue_copies_list_order);
	RUN_TEST(test_create_queue_clears_existing_queue_first);
	RUN_TEST(test_create_queue_from_empty_list);
	RUN_TEST(test_remove_odd_values_keeps_even_order);
	RUN_TEST(test_remove_odd_values_all_odd);

	return finish_test_suite("Q1_C_SQ");
}
