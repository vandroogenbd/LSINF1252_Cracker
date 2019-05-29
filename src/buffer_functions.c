#include <includes.h>

// Vide le buffer passé en argument
void	empty_buffer(char *buff, int buf_size) {
	for (int iter = 0 ; iter < buf_size ; iter++)
		*(buff + iter) = 0;
}

// Initialise tous les buffers du tableau passé en argument à 0
void	init_tab(char **tab, int tab_size, int buf_size) {
	for (int iter = 0 ; iter < tab_size ; iter++)
		empty_buffer(tab[iter], buf_size);
}

// Regarde si le buffer passé en argument est vide
bool	is_empty(char *buff, int buf_size) {
	for (int iter = 0 ; iter < buf_size ; iter++)
		if (*(buff + iter) != 0)
			return (false);
	return (true);
}

// Regarde si tous les buffers du tableau passé en premier argument sont vides
bool	is_empty_tab(char **tab, int tab_size, int buf_size) {
	for (int iter = 0 ; iter < tab_size ; iter++) {
		if (!(is_empty(tab[iter], buf_size)))
			return (false);
	}
	return (true);
}

// Ajoute buf dans le premier emplacement vide de tab
// Renvoie false si le tableau ne contient pas d'emplacement vide, true sinon
bool	add_buff_tab(char **tab, char *buff, int tab_size, int buf_size) {
	int first_empty;

	first_empty = 0;
	while (first_empty < tab_size && !(is_empty(tab[first_empty], buf_size)))
		first_empty++;
	if (first_empty == tab_size) {
		return (false);
	}

	for (int iter = 0 ; iter < buf_size ; iter++)
		tab[first_empty][iter] = buff[iter];
	return (true);
}

void	buf_cpy(uint8_t *dest, uint8_t *src, int length) {
	for (int i = 0 ; i < length ; i++)
		*(dest + i) = *(src + i);
}

// Calcule le poids d'un string basé sur les voyelles ou consonnes
int		buf_weight(char *buff, bool c) {
	int count = 0;

	for (int i = 0 ; i < strlen(buff) ; i++)
		if (buff[i]=='a' || buff[i]=='e' || buff[i]=='i' || 
				buff[i]=='o' || buff[i]=='u' || buff[i]=='y')
			count++;
	if (c)
		return (strlen(buff) - count);
	return count;
}