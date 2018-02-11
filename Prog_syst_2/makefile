test: manager.o listener.o worker_functions.o
	gcc manager.o listener.o worker_functions.o -o

manager.o: manager.c
	gcc -c manager.c

listener.o: listener.c
	gcc -c listener.c

worker_functions.o: worker_functions.c
	gcc -c worker_functions.c