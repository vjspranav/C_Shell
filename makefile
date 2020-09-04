main:
	gcc -g main.c prompt.c input.c commandHandler.c history.c -o terminal
	./terminal
