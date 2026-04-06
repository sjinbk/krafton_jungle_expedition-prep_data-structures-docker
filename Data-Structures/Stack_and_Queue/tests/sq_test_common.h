#ifndef SQ_TEST_COMMON_H
#define SQ_TEST_COMMON_H

#include <stdio.h>

#if defined(__unix__) || defined(__APPLE__)
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#define SQ_TEST_TIMEOUT_ENABLED 1
#else
#define SQ_TEST_TIMEOUT_ENABLED 0
#endif

static int g_test_count = 0;
static int g_fail_count = 0;

#define SQ_TEST_TIMEOUT_SECONDS 2
#define SQ_MAX_LIST_NODES_TO_CHECK 2048

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

static void init_basic_list(LinkedList *ll)
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

static void print_list_safely(LinkedList *ll)
{
	int steps = 0;
	int limit = ll->size;
	ListNode *current = ll->head;

	if (current == NULL) {
		printf("Empty");
		return;
	}

	if (limit < 0 || limit > SQ_MAX_LIST_NODES_TO_CHECK) {
		limit = SQ_MAX_LIST_NODES_TO_CHECK;
	}

	while (current != NULL && steps < limit) {
		printf("%d", current->item);
		current = current->next;
		steps++;
		if (current != NULL && steps < limit) {
			printf(" ");
		}
	}

	if (current != NULL) {
		printf(" ...");
	}
}

static void expect_list_equals(LinkedList *ll, const int *expected, int count, const char *message)
{
	g_test_count++;
	if (list_matches(ll, expected, count)) {
		printf("[PASS] %s\n", message);
	} else {
		printf("[FAIL] %s (expected size=%d, actual size=%d, actual list=", message, count, ll->size);
		print_list_safely(ll);
		printf(")\n");
		g_fail_count++;
	}
}

#if SQ_TEST_TIMEOUT_ENABLED
static jmp_buf g_test_timeout_env;

static void sq_test_alarm_handler(int signal_number)
{
	(void)signal_number;
	longjmp(g_test_timeout_env, 1);
}

static void run_test_with_timeout(void (*test_fn)(void), const char *test_name)
{
	void (*previous_handler)(int);

	previous_handler = signal(SIGALRM, sq_test_alarm_handler);

	if (setjmp(g_test_timeout_env) == 0) {
		alarm(SQ_TEST_TIMEOUT_SECONDS);
		test_fn();
		alarm(0);
	} else {
		alarm(0);
		g_test_count++;
		g_fail_count++;
		printf("[FAIL] %s timed out after %d seconds\n", test_name, SQ_TEST_TIMEOUT_SECONDS);
	}

	signal(SIGALRM, previous_handler);
}
#else
static void run_test_with_timeout(void (*test_fn)(void), const char *test_name)
{
	(void)test_name;
	test_fn();
}
#endif

#define RUN_TEST(test_fn) \
	do { \
		run_test_with_timeout((test_fn), #test_fn); \
	} while (0)

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
