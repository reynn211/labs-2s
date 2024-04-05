all: compile

compile:
	@gcc -o generate generate.c io.c -Wall -pedantic -std=c99
	@gcc -o print print.c io.c -Wall -pedantic -std=c99
	@gcc -o execute execute.c io.c -Wall -pedantic -std=c99

valgrind: compile run_valgrind

run_valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./generate input out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./print out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./execute out