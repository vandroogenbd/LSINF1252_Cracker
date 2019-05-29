#include <includes.h>

// Ecrit le string passé en argument sur la sortie erreur
void	put_error(char *str) {
	int i;

	i = -1;
	while (str[++i])
		write(2, str+i, 1);
}

// Output le contenu de la stack dans le fichier désigné par output,
//  ou sur la sortie standard si output == NULL
void	output_stack(stack *elem, char *output) {
	stack	*temp;
	stack	*temp_to_free;
	int		fd;

	fd = 1;
	if (output != NULL)
		fd = open(output, O_RDWR | O_CREAT | O_APPEND, 0666);

	if (fd == -1) {
		put_error("Erreur open dans output_stack");
		exit(1);
	}

	temp = elem;
	while(temp != NULL) {
		write(fd, temp->string, strlen(temp->string));
		write(fd, "\n", 1);
		temp_to_free = temp;
		temp = temp->next;
		free(temp_to_free->string);
		free(temp_to_free);
	}
}