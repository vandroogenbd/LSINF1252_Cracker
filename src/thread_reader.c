#include <includes.h>

// Les paramètres du programme entrés par l'utilisateur
extern char				**ifiles;
extern int				n_ifiles;

// Le premier buffer partagé
extern uint8_t			**hashs;
extern int				hashs_size;

// Variables globales pour communiquer entre les threads
extern bool				read_end;

// Les mutex et sémaphores utiles dans ce thread
extern sem_t			empty1;
extern sem_t			full1;
extern pthread_mutex_t 	mutex1;

void	*reader(void *arg) {

	// Pour stocker le file descriptor du fichier actuel
	int fd;
	// Sert à vérifier si le thread est arrivé au bout du fichier actuel
	int read_val;
	// Buffer temporaire pour stocker les valeurs lues
	uint8_t *read_buf;

	read_end = false;

	// Protection du malloc
	if(!(read_buf = (uint8_t*)malloc(sizeof(uint8_t) * 32))) {
		put_error("Erreur malloc : thread_reader.c L? (fonc : reader | var : read_buf)\n");
		pthread_exit(NULL);
	}

	for (int cur_file = 0 ; cur_file < n_ifiles ; cur_file++) {

		// On ouvre le fichier et vérifie la valeur de retour
		fd = open(ifiles[cur_file], O_RDONLY);
		if (fd == -1) {
			put_error("Erreur lors de l'open d'un fichier\n");
			free(read_buf);
			exit(1);
		}

		// On force l'entrée dans la boucle de lecture du fichier
		read_val = 1;

		// Tant que la lecture n'a pas échoué, c'est que l'on peut
		// potentiellement encore lire dans le fichier
		while (read_val > 0) {
			read_val = read(fd, read_buf, 32);

			if (read_val == -1) {
				put_error("Erreur à la lecture : read_val < 0\n");
				free(read_buf);
				pthread_exit(NULL);
			}

			if (read_val > 0) {
				// On attend un slot libre dans le buffer pour aller stocker le contenu lu
				sem_wait(&empty1);

				// On entre dans la section critique
				pthread_mutex_lock(&mutex1);

				if (!(add_buff_tab((char**)hashs, (char*)read_buf, hashs_size, 32))) {
					put_error("Erreur lors de l'ajout d'un hash\n");
					free(read_buf);
					pthread_exit(NULL);
				}

				// On sort de la section critique
				pthread_mutex_unlock(&mutex1);

				sem_post(&full1);
			}
		}
	}

	free(read_buf);
	read_end = true;
	sem_post(&full1);
	pthread_exit(EXIT_SUCCESS);
}