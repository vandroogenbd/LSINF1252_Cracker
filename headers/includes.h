
#ifndef INCLUDES_H
# define INCLUDES_H

// - - - - - Includes système - - - - -

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <getopt.h>

// - - - - - Structures de données - - - - -

// Une pile de type LIFO (last in first out)
typedef struct		stack
{
	char			*string;
	struct stack	*next;
}					stack;

// - - - - - Prototypes - - - - -

	// start_threads.c
int		start_threads(char *output, int n_threads, bool cons, char **input_files, int n_input_files);
	// thread_reader.c
void	*reader(void *arg);
	// thread_reverser.c
void	*reverser(void *arg);
	// thread_stacker.c
void	*stacker(void *arg);
	// buffer_functions.c
void	empty_buffer(char *buff, int buf_size);
void	init_tab(char **tab, int tab_size, int buf_size);
bool	is_empty(char *buff, int buf_size);
bool	is_empty_tab(char **tab, int tab_size, int buf_size);
bool	add_buff_tab(char **tab, char *buff, int tab_size, int buf_size);
void	buf_cpy(uint8_t *dest, uint8_t *src, int length);
int		buf_weight(char *buff, bool c);
	// stack_functions.c
stack	*new_stack_e();
stack	*new_stack_i(char *str, stack *next);
void	free_stack(stack *elem);
	// output.c
void	put_error(char *str);
void	output_stack(stack *elem, char *output);

#endif