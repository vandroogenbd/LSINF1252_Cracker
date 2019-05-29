
#ifndef TESTS_H
# define TESTS_H

// - - - - - Includes système - - - - -

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// - - - - - Prototypes - - - - -

	// buffer_tests.c
void	test_empty_buffer();
void	test_init_tab();
void	test_is_empty();
void	test_is_empty_tab();
void	test_add_buff_tab();
void	test_buf_cpy();
void	test_buf_weight();
	// stack_tests.c
void	test_new_stack_e();
void	test_new_stack_i();
void	test_free_stack();

#endif