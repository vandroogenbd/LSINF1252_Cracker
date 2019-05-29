#include <includes.h>

// Crée une pile vide
stack	*new_stack_e() {
	stack	*temp;

	if (!(temp = (stack*)malloc(sizeof(stack))))
		return (NULL);
	temp->string = NULL;
	temp->next = NULL;
	return (temp);
}

// Crée une pile avec les arguments comme valeurs
stack	*new_stack_i(char *str, stack *next) {
	stack	*temp;
	char	*buf;

	if (!(temp = (stack*)malloc(sizeof(stack))))
		return (NULL);
	if (!(buf = (char*)malloc(sizeof(char)*16)))
		return (NULL);
	buf_cpy(buf, str, 16);
	temp->string = buf;
	temp->next = next;
	return (temp);
}

// Vide récursivement la pile passée en argument
void	free_stack(stack *elem) {
	if (elem != NULL) {
		stack	*temp;
	
		temp = elem->next;
		free(elem->string);
		free(elem);
		free_stack(temp);
	}
}
