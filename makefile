onegin: onegin.cpp main.cpp onegin.h
	gcc onegin.cpp -c -g
	gcc main.cpp -c -g
	gcc onegin.o main.o -g -o onegin