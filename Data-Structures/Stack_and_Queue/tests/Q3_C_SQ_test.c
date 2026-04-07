#define main q3_c_sq_original_main
#include "../Q3_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void init_stack(Stack *s)
{
	init_basic_list(&(s->ll));
	s->ll.tail = NULL;
}

static void push_top_to_bottom(Stack *s, const int *top_values, int count)
{
	int index;

	for (index = count - 1; index >= 0; index--) {
		push(s, top_values[index]);
	}
}

static void test_pairwise_consecutive_even_count_true(void)
{
	Stack s;
	int top_to_bottom[] = {8, 7, 4, 5};

	init_stack(&s);
	push_top_to_bottom(&s, top_to_bottom, 4);

	EXPECT_TRUE(isStackPairwiseConsecutive(&s), "isStackPairwiseConsecutive returns true when every adjacent pair differs by 1");
	expect_list_equals(&(s.ll), top_to_bottom, 4, "isStackPairwiseConsecutive restores the original stack order after checking");

	removeAllItems(&(s.ll));
}

static void test_pairwise_consecutive_false(void)
{
	Stack s;
	int top_to_bottom[] = {9, 7, 4, 5};

	init_stack(&s);
	push_top_to_bottom(&s, top_to_bottom, 4);

	EXPECT_TRUE(!isStackPairwiseConsecutive(&s), "isStackPairwiseConsecutive returns false when a pair is not consecutive");
	expect_list_equals(&(s.ll), top_to_bottom, 4, "isStackPairwiseConsecutive still restores the stack when returning false");

	removeAllItems(&(s.ll));
}

static void test_pairwise_consecutive_odd_count_false(void)
{
	Stack s;
	int top_to_bottom[] = {6, 5, 2};

	init_stack(&s);
	push_top_to_bottom(&s, top_to_bottom, 3);

	EXPECT_TRUE(!isStackPairwiseConsecutive(&s), "isStackPairwiseConsecutive returns false when the stack size is odd");
	expect_list_equals(&(s.ll), top_to_bottom, 3, "isStackPairwiseConsecutive restores the original stack order when rejecting an odd-sized stack");

	removeAllItems(&(s.ll));
}

static void test_pairwise_consecutive_empty_true_singleton_false(void)
{
	Stack empty_stack;
	Stack single_stack;
	int single_value[] = {42};

	init_stack(&empty_stack);
	init_stack(&single_stack);
	push_top_to_bottom(&single_stack, single_value, 1);

	EXPECT_TRUE(isStackPairwiseConsecutive(&empty_stack), "isStackPairwiseConsecutive treats an empty stack as pairwise consecutive");
	EXPECT_TRUE(!isStackPairwiseConsecutive(&single_stack), "isStackPairwiseConsecutive returns false for a single-item stack because its size is odd");
	expect_list_equals(&(single_stack.ll), single_value, 1, "isStackPairwiseConsecutive preserves a single-item stack when returning false");

	removeAllItems(&(empty_stack.ll));
	removeAllItems(&(single_stack.ll));
}

int main(void)
{
	printf("Running Q3_C_SQ tests...\n");

	RUN_TEST(test_pairwise_consecutive_even_count_true);
	RUN_TEST(test_pairwise_consecutive_false);
	RUN_TEST(test_pairwise_consecutive_odd_count_false);
	RUN_TEST(test_pairwise_consecutive_empty_true_singleton_false);

	return finish_test_suite("Q3_C_SQ");
}
