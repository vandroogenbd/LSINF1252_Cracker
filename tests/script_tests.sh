#!/bin/bash
#!/bin/sh


# Description du protocole de test
printf '\nProtocole de test :\n\n'

printf '1. Tests unitaires des fonctions définies dans les fichiers stack_functions.c et buffer_functions.c\n'

printf "2. Tests de robustesse du programme cracker en cas d'inputs incorrects\n"

printf "3. Vérification des outputs du programme cracker\n"

printf "4. Analyse de la variation des performances en fonction du nombre de threads\n"

printf "\nNB: L'ensemble des tests peut prendre plusieurs minutes\n\n"

# Les tests commencent quand l'utilisateur le souhaite
read -p "Appuyer sur enter pour lancer les tests " var
clear


# Lancement des tests unitaires
printf "\n1. --- Tests unitaires ---\n"

./tester



read -p "Appuyer sur enter pour continuer " var
clear


# Lancement des tests de robustesse
printf "\n2. --- Tests de robustesse ---\n"

printf "\n2.1 Nombre de threads non indiqué / incorrect\n\n"
printf "Commande entrée : ./cracker -t inputs/010.bin\n"
printf "Réponse du programme :\n"
# Le || true permet au script de continuer malgré le fait que le programme renvoie
# un signal d'erreur
./cracker -t inputs/010.bin || true
printf "Commande entrée : ./cracker -t -50 inputs/010.bin\n"
printf "Réponse du programme :\n"
./cracker -t -50 inputs/010.bin || true

printf "\n2.2 Output non indiqué\n\n"
printf "Commande entrée : ./cracker -o -t 4 inputs/010.bin\n"
printf "Réponse du programme :\n"
./cracker -o -t 4 inputs/010.bin || true

printf "\n2.3 Fichier d'input inexistant\n\n"
printf "Commande entrée : ./cracker fichierInexistant\n"
printf "Réponse du programme :\n"
./cracker fichierInexistant || true
printf '\n'



read -p "Appuyer sur enter pour continuer " var
clear


# Lancement de la vérification des outputs
printf "\n3. --- Vérification des outputs ---\n"

# /!\ LANCER AVEC PLUS D'UN THREAD PEUT CHANGER L'ORDRE DES MOTS EN OUTPUT
printf "\nDifférence entre 010.bin passé dans cracker et 010_voy.txt :\n"
./cracker -t 1 inputs/010.bin -o test_voy_010.txt
diff test_voy_010.txt tests/010_voy.txt
rm test_voy_010.txt
printf '\nCette ligne devrait directement suivre le lancement du test\n'

printf "\nDifférence entre 010.bin passé dans cracker (avec -c) et 010_cons.txt :\n"
./cracker -t 1 inputs/010.bin -o test_cons_010.txt -c
diff test_cons_010.txt tests/010_cons.txt
rm test_cons_010.txt
printf '\nCette ligne devrait directement suivre le lancement du test\n'

printf "\nDifférence entre 020.bin passé dans cracker et 020_voy.txt :\n"
./cracker -t 1 inputs/020.bin -o test_voy_020.txt
diff test_voy_020.txt tests/020_voy.txt
rm test_voy_020.txt
printf '\nCette ligne devrait directement suivre le lancement du test\n'

printf "\nDifférence entre 020.bin passé dans cracker (avec -c) et 020_cons.txt :\n"
./cracker -t 1 inputs/020.bin -o test_cons_020.txt -c
diff test_cons_020.txt tests/020_cons.txt
rm test_cons_020.txt
printf '\nCette ligne devrait directement suivre le lancement du test\n\n'



read -p "Appuyer sur enter pour continuer " var
clear


# Lancement de la comparaison de performances
printf "\n4. --- Analyse de performances ---\n"

printf "\n\n- - - - - TEST VOYELLES - - - - -\n\n"

printf "Temps total pris pour 10 exécutions du programme  avec 1 thread, basé sur les voyelles, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 1 inputs/050.bin
done | grep real

printf "\nTemps total pris pour 10 exécutions du programme  avec 2 threads, basé sur les voyelles, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 2 inputs/050.bin
done | grep real

printf "\nTemps total pris pour 10 exécutions du programme  avec 3 threads, basé sur les voyelles, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 3 inputs/050.bin
done | grep real

printf "\nTemps total pris pour 10 exécutions du programme  avec 4 threads, basé sur les voyelles, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 4 inputs/050.bin
done | grep real

printf "\n- - - - - TEST CONSONNES - - - - -\n\n"

printf "\nTemps total pris pour 10 exécutions du programme  avec 1 thread, basé sur les consonnes, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 1 inputs/050.bin -c
done | grep real

printf "\nTemps total pris pour 10 exécutions du programme  avec 2 threads, basé sur les consonnes, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 2 inputs/050.bin -c
done | grep real

printf "\nTemps total pris pour 10 exécutions du programme  avec 3 threads, basé sur les consonnes, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 3 inputs/050.bin -c
done | grep real

printf "\nTemps total pris pour 10 exécutions du programme  avec 4 threads, basé sur les consonnes, pas d'output specifié\n\n"
time for ((i = 1 ; i < 11 ; i = i+1))
do
	./cracker -t 4 inputs/050.bin -c
done | grep real



printf 'Fin des tests!'