#include <includes.h>

// Les paramètres du programme entrés par l'utilisateur
extern bool				c;

// Les buffers partagés
extern int				hashs_size;
extern char				**dehashs; // dehashs est de même longueur que hashs

// Variables globales pour communiquer entre les threads
extern int				reverse_end;
extern stack 			*final_stack;

// Les mutex et sémaphores utiles dans ce thread
extern sem_t			empty2;
extern sem_t			full2;
extern pthread_mutex_t 	mutex2;

void	*stacker(void *arg) {

	// Servira à itérer sur le buffer
	int iter;

	// Stack dans laquelle seront ultimement stockés les résultats
	stack *answers = NULL;

	// Plus grand poids trouvé
	int	best_weight = 0;

	// Booléen pour stocker la condition d'arrêt
	bool stop_cond = false;

	// Buffers temporaires
	char temp_buf[16];
	stack *stack_temp;

	while (!stop_cond) {

		// On attend qu'il y ait un nouvel élément dans le buffer
		sem_wait(&full2);

		// On entre dans la section critique
		pthread_mutex_lock(&mutex2);

		if (!(is_empty_tab(dehashs, hashs_size, 16))) {

			// On cherche le premier emplacement plein, on sait qu'il y en a au moins 1
			iter = 0;
			while (is_empty(dehashs[iter], 16))
				iter++;

			buf_cpy(temp_buf, dehashs[iter], 16);

			empty_buffer(dehashs[iter], 16);

			pthread_mutex_unlock(&mutex2);
			// Sortie de la section critique

			sem_post(&empty2);

			// Si le mdp trouvé est meilleur que tous les précédents
			if (buf_weight(temp_buf, c) > best_weight) {
				free_stack(answers);
				best_weight = buf_weight(temp_buf, c);
				stack_temp = new_stack_i(temp_buf, NULL);
				answers = stack_temp;
			} // Si le mdp trouvé est de poids égal aux précédents
			else if (buf_weight(temp_buf, c) == best_weight) {
				stack_temp = new_stack_i(temp_buf, answers);
				answers = stack_temp;
			} // Tout mdp ne satisfaisant pas une des deux conditions est négligé
			
			empty_buffer(temp_buf, 16);
		}
		else {
			pthread_mutex_unlock(&mutex2);
			// Sortie de la section critique

			stop_cond = (reverse_end == hashs_size);
		}
	}

	final_stack = answers;
	pthread_exit(answers);
}