// Tests adaptés de : http://wpollock.com/CPlus/CUnitNotes.htm

#include <includes.h>
#include <tests.h>

/* Test Suite setup and cleanup functions: */
int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main() {

	if ( CUE_SUCCESS != CU_initialize_registry() )
    	return CU_get_error();

    // --- Première suite de tests ---

    CU_pSuite buffSuite = CU_add_suite("Tests pour buffer_functions", init_suite, clean_suite);
    if (buffSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de empty_buffer", test_empty_buffer) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de init_tab", test_init_tab) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de is_empty", test_is_empty) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de is_empty_tab", test_is_empty_tab) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de test_add_buff_tab", test_add_buff_tab) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de test_buf_cpy", test_buf_cpy) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(buffSuite, "Test de test_buf_weight", test_buf_weight) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}


	// --- Deuxième suite de tests ---

	CU_pSuite stackSuite = CU_add_suite("Tests pour stack_functions", init_suite, clean_suite);
    if (stackSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(stackSuite, "Test de test_new_stack_e", test_new_stack_e) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(stackSuite, "Test de test_new_stack_i", test_new_stack_i) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (CU_add_test(stackSuite, "Test de test_free_stack", test_free_stack) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}


	// --- Lancement & display des tests ---

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());

	// --- Fin des tests ---

	CU_cleanup_registry();

	printf("\n");

	return (CU_get_error());
}	
