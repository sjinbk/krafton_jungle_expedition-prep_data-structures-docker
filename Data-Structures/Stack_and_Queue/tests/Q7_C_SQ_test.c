#define main q7_c_sq_original_main
#include "../Q7_C_SQ.c"
#undef main

#include "sq_test_common.h"

static void test_balanced_simple_pairs(void)
{
	EXPECT_INT_EQ(0, balanced("()[]{}"), "balanced returns 0 for a flat balanced expression");
}

static void test_balanced_nested_expression(void)
{
	EXPECT_INT_EQ(0, balanced("{[()()]}"), "balanced returns 0 for a nested balanced expression");
}

static void test_balanced_rejects_mismatched_types(void)
{
	EXPECT_TRUE(balanced("([)]") != 0, "balanced returns non-zero for mismatched bracket types");
}

static void test_balanced_rejects_early_closing(void)
{
	EXPECT_TRUE(balanced(")(") != 0, "balanced returns non-zero when a closing bracket appears before an opener");
}

static void test_balanced_rejects_leftover_openers(void)
{
	EXPECT_TRUE(balanced("(()") != 0, "balanced returns non-zero when open brackets remain on the stack");
}

static void test_balanced_empty_expression(void)
{
	EXPECT_INT_EQ(0, balanced(""), "balanced returns 0 for an empty expression");
}

int main(void)
{
	printf("Running Q7_C_SQ tests...\n");

	RUN_TEST(test_balanced_simple_pairs);
	RUN_TEST(test_balanced_nested_expression);
	RUN_TEST(test_balanced_rejects_mismatched_types);
	RUN_TEST(test_balanced_rejects_early_closing);
	RUN_TEST(test_balanced_rejects_leftover_openers);
	RUN_TEST(test_balanced_empty_expression);

	return finish_test_suite("Q7_C_SQ");
}
