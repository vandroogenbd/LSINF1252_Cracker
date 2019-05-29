/* *************************************************************************** #
#                                                                              #
#  							   Travail par David VD                            #
#                                                                              #
#  Solution du projet de SYSTINFO du Q2 de 2019 portant sur le multithreading  #
#  (des problèmes peuvent subsister, à charge de l'utilisateur de les régler)  #
#                                                                              #
# *************************************************************************** */

#include <includes.h>

int	main(int ac, char **av) {

	// On initialise les valeurs par défaut
	bool cons = false;
	char *output = NULL;
	int threads = 1;
	char **files;

	// Sert à gérer les inputs du programme avec getopt
	int opt;

	// On utilise getopt pour gérer les flags passés en arguments
	while ((opt = getopt(ac, av, "o:t:c")) != -1) {
		switch(opt) {

			// Si l'option o est spécifiée
			case 'o':
				if (optarg[0] == '-') {
					put_error("Sortie invalide\n");
					exit(EXIT_FAILURE);
				}
				// On protège le malloc pour stocker l'output
				if (!(output = (char*)malloc(strlen(optarg) + 1))) {
					put_error("Erreur malloc : main.c L35 (fonc : main | var : output)\n");
					exit(EXIT_FAILURE);
				}
				memcpy(output, optarg, strlen(optarg));
				output[strlen(optarg)] = '\0';
				break;

			// Si l'option t est spécifiée
			case 't':
				threads = atoi(optarg);
				if (threads < 1 || threads > 100) {
					put_error("Nombre de threads non compris entre 1 et 100\n");
					exit(EXIT_FAILURE);
				}
				break;

			// Si l'option c est spécifiée
			case 'c':
				cons = true;
				break;

			// Si une option non reconnue est détectée, ou qu'une option ne reçoit pas d'argument
			case '?':
				if (optopt == 'o') {
					put_error("Sortie non indiquée\n");
					exit(EXIT_FAILURE);
				}
				if (optopt == 't') {
					put_error("Nombre de threads non indiqué\n");
					exit(EXIT_FAILURE);
				}
				printf("Option inconnue : %c\n", (char)optopt);
				exit(EXIT_FAILURE);
		}
	}

	// Variable pour savoir combien de fichiers doivent être lus
	int n_files = ac - optind;

	// Si aucun fichier d'input n'est spécifié, on arrête le programme
	if (n_files < 1) {
		put_error("Pas d'input détecté, programme interrompu\n");
		exit(EXIT_FAILURE);
	}

	if (!(files = (char**)malloc(sizeof(char*) * (n_files)))) {
		put_error("Erreur malloc : main.c L75 (fonc : main | var : files)\n");
		exit(EXIT_FAILURE);
	}

	for (int iter = 0 ; iter < n_files ; iter++, optind++) {

		// Si le malloc échoue, on libère les noms des fichiers d'input
		if (!(files[iter] = (char*)malloc((sizeof(char) * strlen(av[optind])) + 1))) {
			put_error("Erreur malloc : main.c L83 (fonc : main | var : files)\n");
			for (int i = 0 ; i <= iter ; i++)
				free(files[i]);
			free(files);
			exit(EXIT_FAILURE);
		}

		// On stocke le fichier d'input dans le tableau
		memcpy(files[iter], av[optind], strlen(av[optind]));
		files[iter][strlen(av[optind])] = '\0';
	}

	// On lance les threads et stocke si le programme a rencontré une erreur
	int err = start_threads(output, threads, cons, files, n_files);

	// On libère la mémoire allouée avant de finir le programme
	if (output != NULL) {
		free(output);
	}
	for (int i = 0 ; i < n_files ; i++)
		free(files[i]);
	free(files);

	exit(err);
}