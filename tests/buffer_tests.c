#include <includes.h>
#include <tests.h>


void	test_empty_buffer() {
	char buf1[10] = "10 chars_l";
	char *buf2 = (char*)calloc(10, sizeof(char));

	empty_buffer(buf1, 10);
	CU_ASSERT_STRING_EQUAL(buf1, buf2);

	free(buf2);
}

void	test_init_tab() {
	char **buf1;
	char *buf2 = (char*)calloc(4, sizeof(char));

	buf1 = (char**)malloc(sizeof(char*)*4);
	for (int i = 0 ; i < 4 ; i++)
		buf1[i] = (char*)malloc(sizeof(char)*4);

	char c = 'a';
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			buf1[i][j] = c;
			c++;
		}
	}

	init_tab(buf1, 4, 4);
	for (int i = 0 ; i < 4 ; i++)
		CU_ASSERT_STRING_EQUAL(buf1[i], buf2);

	for (int i = 0 ; i < 4 ; i++)
		free(buf1[i]);
	free(buf1);
	free(buf2);
}

void	test_is_empty() {
	char buf1[10] = "10 chars_l";
	char *buf2 = (char*)calloc(10, sizeof(char));

	CU_ASSERT_FALSE(is_empty(buf1, 10));
	CU_ASSERT_TRUE(is_empty(buf2, 10));
	free(buf2);
}

void	test_is_empty_tab() {
	char **buf1;
	char **buf2;

	buf1 = (char**)malloc(sizeof(char*)*4);
	for (int i = 0 ; i < 4 ; i++)
		buf1[i] = (char*)malloc(sizeof(char)*4);

	char c = 'a';
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			buf1[i][j] = c;
			c++;
		}
	}

	buf2 = (char**)malloc(sizeof(char*)*4);
	for (int i = 0 ; i < 4 ; i++)
		buf2[i] = (char*)calloc(4, sizeof(char));

	CU_ASSERT_FALSE(is_empty_tab(buf1, 4, 4));
	CU_ASSERT_TRUE(is_empty_tab(buf2, 4, 4));

	for (int i = 0 ; i < 4 ; i++)
		free(buf1[i]);
	free(buf1);
	for (int i = 0 ; i < 4 ; i++)
		free(buf2[i]);
	free(buf2);
}

void	test_add_buff_tab() {
	char **buf1;
	char **buf2;

	buf1 = (char**)malloc(sizeof(char*)*4);
	for (int i = 0 ; i < 4 ; i++)
		buf1[i] = (char*)malloc(sizeof(char)*4);

	char c = 'a';
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			buf1[i][j] = c;
			c++;
		}
	}

	buf2 = (char**)malloc(sizeof(char*)*4);
	for (int i = 0 ; i < 4 ; i++)
		buf2[i] = (char*)calloc(4, sizeof(char));
	for (int i = 0 ; i < 3 ; i++)
		buf2[i][0] = 'a';

	CU_ASSERT_FALSE(add_buff_tab(buf1, "cont", 4, 4));
	CU_ASSERT_TRUE(add_buff_tab(buf2, "cont", 4, 4));
	CU_ASSERT_STRING_EQUAL(buf2[3], "cont");

	for (int i = 0 ; i < 4 ; i++)
		free(buf1[i]);
	free(buf1);
	for (int i = 0 ; i < 4 ; i++)
		free(buf2[i]);
	free(buf2);
}

void	test_buf_cpy() {
	char buf1[10] = "10 chars_l";

	buf_cpy((uint8_t*)buf1, (uint8_t*)"11 fcors", 8);
	CU_ASSERT_STRING_EQUAL(buf1, "11 fcors_l");
}

void	test_buf_weight() {
	CU_ASSERT_EQUAL(buf_weight("oyPLkmajhgu", false), 4);
	CU_ASSERT_EQUAL(buf_weight("oyPLihaxcgu", true), 6);
}