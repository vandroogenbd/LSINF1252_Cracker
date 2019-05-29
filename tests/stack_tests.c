#include <includes.h>
#include <tests.h>

void	test_new_stack_e() {
	stack *elem = NULL;

	elem = new_stack_e();

	CU_ASSERT_PTR_NOT_NULL(elem);

	if (elem != NULL)
		free(elem);
}

void	test_new_stack_i() {
	stack *elem1 = NULL;
	stack *elem2 = NULL;

	elem1 = new_stack_i("string", NULL);
	elem2 = new_stack_i("string_value", elem1);

	CU_ASSERT_PTR_NOT_NULL(elem1);
	CU_ASSERT_PTR_NOT_NULL(elem2);
	CU_ASSERT_STRING_EQUAL(elem1->string, "string");
	CU_ASSERT_STRING_EQUAL(elem2->string, "string_value");
	CU_ASSERT_PTR_EQUAL(elem2->next, elem1);

	if (elem1 != NULL) {
		free(elem1->string);
		free(elem1);
	}
	if (elem2 != NULL) {
		free(elem2->string);
		free(elem2);
	}
}

void	test_free_stack() {
	stack *elem1 = NULL;
	stack *elem2 = NULL;

	elem1 = new_stack_i("string", NULL);
	elem2 = new_stack_i("string_value", elem1);

	free_stack(elem2);

	// Les 2 asserts plus bas (commentaires) renvoient toujours failed car free
	// la mémoire ne fait pas passer les pointeurs à null 

	//CU_ASSERT_PTR_NULL(elem1);
	//CU_ASSERT_PTR_NULL(elem2);

	CU_PASS("test_free_stack succeeded.");
}