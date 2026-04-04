#ifndef LL_TEST_COMMON_H
#define LL_TEST_COMMON_H

#include <stdio.h>

static int g_test_count = 0;
static int g_fail_count = 0;

#define EXPECT_TRUE(condition, message) \
	do { \
		g_test_count++; \
		if (condition) { \
			printf("[PASS] %s\n", message); \
		} else { \
			printf("[FAIL] %s\n", message); \
			g_fail_count++; \
		} \
	} while (0)

#define EXPECT_INT_EQ(expected, actual, message) \
	do { \
		int expected_value = (expected); \
		int actual_value = (actual); \
		g_test_count++; \
		if (expected_value == actual_value) { \
			printf("[PASS] %s\n", message); \
		} else { \
			printf("[FAIL] %s (expected=%d, actual=%d)\n", message, expected_value, actual_value); \
			g_fail_count++; \
		} \
	} while (0)

#define EXPECT_NULL(ptr, message) \
	do { \
		g_test_count++; \
		if ((ptr) == NULL) { \
			printf("[PASS] %s\n", message); \
		} else { \
			printf("[FAIL] %s (expected=NULL)\n", message); \
			g_fail_count++; \
		} \
	} while (0)

static void init_list(LinkedList *ll)
{
	ll->head = NULL;
	ll->size = 0;
}

static void append_values(LinkedList *ll, const int *values, int count)
{
	int index;

	for (index = 0; index < count; index++) {
		insertNode(ll, ll->size, values[index]);
	}
}

static int list_matches(LinkedList *ll, const int *expected, int count)
{
	int index = 0;
	ListNode *current = ll->head;

	if (ll->size != count) {
		return 0;
	}

	while (current != NULL && index < count) {
		if (current->item != expected[index]) {
			return 0;
		}
		current = current->next;
		index++;
	}

	return current == NULL && index == count;
}

static void expect_list_equals(LinkedList *ll, const int *expected, int count, const char *message)
{
	g_test_count++;
	if (list_matches(ll, expected, count)) {
		printf("[PASS] %s\n", message);
	} else {
		ListNode *current = ll->head;

		printf("[FAIL] %s (expected size=%d, actual size=%d, actual list=", message, count, ll->size);
		if (current == NULL) {
			printf("Empty");
		}
		while (current != NULL) {
			printf("%d", current->item);
			current = current->next;
			if (current != NULL) {
				printf(" ");
			}
		}
		printf(")\n");
		g_fail_count++;
	}
}

static int finish_test_suite(const char *suite_name)
{
	printf("\n[%s] Total checks: %d\n", suite_name, g_test_count);
	printf("[%s] Failed checks: %d\n", suite_name, g_fail_count);

	if (g_fail_count == 0) {
		printf("[%s] All tests passed.\n", suite_name);
		return 0;
	}

	printf("[%s] Some tests failed.\n", suite_name);
	return 1;
}

#endif
