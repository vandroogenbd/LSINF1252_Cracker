# **************************************************************************** #
#                                                                              #
#  							   Travail par David VD                            #
#                                                                              #
#  Solution du projet de SYSTINFO du Q2 de 2019 portant sur le multithreading  #
#  (des problèmes peuvent subsister, à charge de l'utilisateur de les régler)  #
#                                                                              #
# **************************************************************************** #

#   --- Variables ---

NAME = cracker
FLAGS = -lpthread -std=c99 -Werror -Wall
HDIR = headers/
	# Les fichiers source
SRCS = reverse sha256 main output start_threads thread_reader buffer_functions \
		thread_reverser thread_stacker stack_functions
CFILES = $(addsuffix .c,$(SRCS))
CDIR = src/
	# Les fichiers source testés individuellement
SRC_TESTS = buffer_functions stack_functions
SRC_CTESTS = $(addsuffix .c,$(SRC_TESTS))
	# Les fichiers de test
TESTS = main_test buffer_tests stack_tests
CTESTS = $(addsuffix .c,$(TESTS))
TDIR = tests/

#   --- Methodes ---

all:
	@((make -s clean)&&(make -s cracker)&&(make -s test)) || \
		((make -s cracker)&&(make -s test)) || (make -s test)

$(NAME):
	@gcc -o $(NAME) $(addprefix $(CDIR),$(CFILES)) -I$(HDIR) $(FLAGS)
	@printf 'Programme cracker compilé\n'

clean: clean_c clean_t

clean_c:
	@rm $(NAME)
	@printf 'Cracker a été supprimé\n'

clean_t:
	@rm tester
	@printf 'Tester a été supprimé\n'

tester:
	@printf 'Compilation des tests unitaires\n'
	@gcc -o tester $(addprefix $(TDIR),$(CTESTS)) $(addprefix $(CDIR),$(SRC_CTESTS)) \
		-I$(HDIR) $(FLAGS) -lcunit
	
test: tester
	@tests/script_tests.sh
