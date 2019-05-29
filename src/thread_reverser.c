#include <includes.h>
#include <reverse.h>

// Les buffers partagés
extern uint8_t			**hashs;
extern int				hashs_size;
extern char				**dehashs; // dehashs est de même longueur que hashs

// Variables globales pour communiquer entre les threads
extern bool				read_end;
extern int				reverse_end;

// Les mutex et sémaphores utiles dans ce thread
extern sem_t			empty1;
extern sem_t			full1;
extern pthread_mutex_t 	mutex1;
extern sem_t			empty2;
extern sem_t			full2;
extern pthread_mutex_t 	mutex2;

void	*reverser(void *arg) {

	// Servira à itérer sur le buffer
	int iter;

	// Buffer temporaire pour stocker un hash à reverse
	uint8_t temp_buf_hash[32];

	// Buffer temporaire pour stocker le résultat du reverse
	char temp_buf_char[16];

	// Booléen pour stocker la condition d'arrêt
	bool stop_cond = false;

	while (!(stop_cond)) {

		// On attend que le reader ait stocké qqch dans le buffer partagé
		sem_wait(&full1);

		// On entre dans la section critique
		pthread_mutex_lock(&mutex1);

		if (!(is_empty_tab((char **)hashs, hashs_size, 32))) {

			// On cherche le premier emplacement plein, on sait qu'il y en a au moins 1
			iter = 0;
			while (is_empty((char*)hashs[iter], 32))
				iter++;

			// On stocke la valeur dans le buffer temporaire
			buf_cpy(temp_buf_hash, hashs[iter], 32);

			// On vide le buffer qu'on a lu
			empty_buffer((char*)hashs[iter], 32);

			pthread_mutex_unlock(&mutex1);
			// Sortie de la section critique

			sem_post(&empty1);

			// On va maintenant tenter de reverse le hash
			if (reversehash(temp_buf_hash, temp_buf_char, 16)) {
				
				iter = 0;

				// On attend un slot libre dans le deuxième buffer
				sem_wait(&empty2);

				// On entre dans la section critique
				pthread_mutex_lock(&mutex2);

				if (!(add_buff_tab(dehashs, temp_buf_char, hashs_size, 16))) {
					put_error("Erreur lors de l'ajout d'un dehash");
					pthread_exit(NULL);
				}

				pthread_mutex_unlock(&mutex2);
				// Sortie de la section critique
				
				sem_post(&full2);

			}
			else {
				put_error("Un hash n'a pas pu être reverse");
				pthread_exit(NULL);
			}

		}
		else {			
			pthread_mutex_unlock(&mutex1);
			// Sortie de la section critique

			stop_cond = read_end;

			// On assure que les threads suivants passent le wait
			sem_post(&full1);
		}	
	}

	pthread_mutex_lock(&mutex2);
	reverse_end++;
	if (reverse_end == hashs_size)
		sem_post(&full2);
	pthread_mutex_unlock(&mutex2);

	pthread_exit(EXIT_SUCCESS);
}