#define main q6_c_sq_original_main
#include "../Q6_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void init_stack(Stack *s)
{
	init_basic_list(&(s->ll));
}

static void push_top_to_bottom(Stack *s, const int *top_values, int count)
{
	int index;

	for (index = count - 1; index >= 0; index--) {
		push(s, top_values[index]);
	}
}

static void test_remove_until_stops_with_target_on_top(void)
{
	Stack s;
	int top_to_bottom[] = {9, 7, 5, 3};
	int expected[] = {5, 3};

	init_stack(&s);
	push_top_to_bottom(&s, top_to_bottom, 4);

	removeUntil(&s, 5);

	expect_list_equals(&(s.ll), expected, 2, "removeUntil pops values above the first target occurrence and keeps the target in the stack");

	removeAllItemsFromStack(&s);
}

static void test_remove_until_when_target_already_top(void)
{
	Stack s;
	int top_to_bottom[] = {4, 2, 1};

	init_stack(&s);
	push_top_to_bottom(&s, top_to_bottom, 3);

	removeUntil(&s, 4);

	expect_list_equals(&(s.ll), top_to_bottom, 3, "removeUntil leaves the stack unchanged when the target is already on top");

	removeAllItemsFromStack(&s);
}

static void test_remove_until_missing_value_empties_stack(void)
{
	Stack s;
	int top_to_bottom[] = {6, 5, 4};

	init_stack(&s);
	push_top_to_bottom(&s, top_to_bottom, 3);

	removeUntil(&s, 42);

	EXPECT_INT_EQ(0, s.ll.size, "removeUntil empties the stack when the chosen value does not occur");
	EXPECT_NULL(s.ll.head, "removeUntil leaves stack head NULL when the chosen value does not occur");

	removeAllItemsFromStack(&s);
}

int main(void)
{
	printf("Running Q6_C_SQ tests...\n");

	RUN_TEST(test_remove_until_stops_with_target_on_top);
	RUN_TEST(test_remove_until_when_target_already_top);
	RUN_TEST(test_remove_until_missing_value_empties_stack);

	return finish_test_suite("Q6_C_SQ");
}
