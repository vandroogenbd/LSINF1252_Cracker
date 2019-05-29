#include <includes.h>

// Les paramètres du programme entrés par l'utilisateur
char				**ifiles;
int					n_ifiles;
bool				c;

// Les buffers partagés
uint8_t				**hashs;
int					hashs_size;
char				**dehashs;

// Variables globales pour communiquer entre les threads
bool				read_end;
int					reverse_end;
stack 				*final_stack;

// Les mutex et sémaphores pour les 2 relations producteur / consommateur
sem_t				empty1;
sem_t				full1;
pthread_mutex_t 	mutex1;
sem_t				empty2;
sem_t				full2;
pthread_mutex_t 	mutex2;

int	start_threads(char *output, int n_threads, bool cons, char **input_files, int n_input_files) {

	// On initialise les variables globales
	c = cons;
	ifiles = input_files;
	n_ifiles = n_input_files;
	hashs_size = n_threads;
	reverse_end = 0;

	// Les threads que le programme lancera
	pthread_t reader_thread;
	pthread_t reversers[n_threads];
	pthread_t stacker_thread;

	// Pour savoir si une erreur s'est produite pendant l'exécution
	int err = 0;

	// Protection du malloc du premier tableau partagé
	if (!(hashs = (uint8_t**)malloc(sizeof(uint8_t**)*hashs_size))) {
		put_error("Erreur malloc : start_threads.c L? (fonc : start_threads | var : hashs)\n");
		return(EXIT_FAILURE);
	}
	for (int i = 0 ; i < hashs_size ; i++) {
		if (!(hashs[i] = (uint8_t*)malloc(sizeof(uint8_t)*32))) {
			for (int iter = 0 ; iter < i ; iter++)
				free(hashs[iter]);
			free(hashs);
			put_error("Erreur malloc : start_threads.c L? (fonc : start_threads | var : hashs)\n");
			return(EXIT_FAILURE);
		}
	}

	// Protection du malloc du deuxième tableau partagé
	if (!(dehashs = (char**)malloc(sizeof(char**)*hashs_size))) {
		put_error("Erreur malloc : start_threads.c L? (fonc : start_threads | var : dehashs)\n");
		return(EXIT_FAILURE);
	}
	for (int i = 0 ; i < hashs_size ; i++) {
		if (!(dehashs[i] = (char*)malloc(sizeof(uint8_t)*16))) {
			for (int iter = 0 ; iter < i ; iter++)
				free(dehashs[iter]);
			free(dehashs);
			put_error("Erreur malloc : start_threads.c L? (fonc : start_threads | var : dehashs)\n");
			return(EXIT_FAILURE);
		}
	}


	// - - - Initialisation des mutex et sémaphores - - -
	err = pthread_mutex_init(&mutex1, NULL);
	if (err != 0) {
		put_error("Erreur mutex_init de mutex1 : start_threads.c\n");
		return (1);
	}
	err = sem_init(&empty1, 0, n_threads);
	if (err != 0) {
		put_error("Erreur sem_init de 'empty1' : start_threads.c\n");
		return (1);
	}
	err = sem_init(&full1, 0, 0);
	if (err != 0) {
		put_error("Erreur sem_init de 'full1' : start_threads.c\n");
		return (1);
	}
	err = pthread_mutex_init(&mutex2, NULL);
	if (err != 0) {
		put_error("Erreur mutex_init de mutex2 : start_threads.c\n");
		return (1);
	}
	err = sem_init(&empty2, 0, n_threads);
	if (err != 0) {
		put_error("Erreur sem_init de 'empty2' : start_threads.c\n");
		return (1);
	}
	err = sem_init(&full2, 0, 0);
	if (err != 0) {
		put_error("Erreur sem_init de 'full2' : start_threads.c\n");
		return (1);
	}


	// - - - - - Début : lancement et join des threads - - - - -

	// Lancement du thread qui lit dans les fichiers d'input
	err = pthread_create(&reader_thread, NULL, &reader, NULL);
	if (err != 0) {
		put_error("Erreur pthread_create de 'reader_thread' : start_threads.c\n");
		return (1);
	}

	// Lancement des threads de reverse
	for (int i = 0 ; i < n_threads ; i++) {
		err = pthread_create(&reversers[i], NULL, &reverser, NULL);
		if (err != 0) {
			put_error("Erreur pthread_create de 'reversers' : start_threads.c\n");
			return (1);
		}
	}

	// Lancement du thread qui crée la stack finale
	err = pthread_create(&stacker_thread, NULL, &stacker, NULL);
	if (err != 0) {
		put_error("Erreur pthread_create de 'stacker_thread' : start_threads.c\n");
		return (1);
	}

	// Join du thread de lecture
	err = pthread_join(reader_thread, NULL);
	if (err != 0) {
		put_error("Erreur pthread_join de 'reader_thread' : start_threads.c\n");
		return (1);
	}

	// Join des threads de reverse
	for (int i = 0 ; i < n_threads ; i++) {
		err = pthread_join(reversers[i], NULL);
		if (err != 0) {
			put_error("Erreur pthread_join de 'reversers' : start_threads.c\n");
			return (1);
		}
	}

	// Join du thread qui crée la stack finale
	err = pthread_join(stacker_thread, NULL);
	if (err != 0) {
		put_error("Erreur pthread_join de 'stacker_thread' : start_threads.c\n");
		return (1);
	}

	// - - - - - Fin : lancement et join des threads - - - - -


	// - - - Destruction des mutex et sémaphores - - -
	err = pthread_mutex_destroy(&mutex1);
	if (err != 0) {
		put_error("Erreur pthread_mutex_destroy de mutex1 : start_threads.c\n");
		return (1);
	}
	err = sem_destroy(&empty1);
	if (err != 0) {
		put_error("Erreur sem_destroy de 'empty1' : start_threads.c\n");
		return (1);
	}
	err = sem_destroy(&full1);
	if (err != 0) {
		put_error("Erreur sem_destroy de 'full1' : start_threads.c\n");
		return (1);
	}
	err = pthread_mutex_destroy(&mutex2);
	if (err != 0) {
		put_error("Erreur pthread_mutex_destroy de mutex2 : start_threads.c\n");
		return (1);
	}
	err = sem_destroy(&empty2);
	if (err != 0) {
		put_error("Erreur sem_destroy de 'empty2' : start_threads.c\n");
		return (1);
	}
	err = sem_destroy(&full2);
	if (err != 0) {
		put_error("Erreur sem_destroy de 'full2' : start_threads.c\n");
		return (1);
	}


	// Free des ressources allouées pour les threads
	for (int i = 0 ; i < hashs_size ; i++) {
		free(hashs[i]);
		free(dehashs[i]);
	}
	free(hashs);
	free(dehashs);
	
	output_stack(final_stack, output);

	return (0);
}