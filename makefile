main:
	gcc -g main.c prompt.c input.c commandHandler.c history.c cd.c echo.c ls.c pwd.c pinfo.c childHandler.c ll.c pipeHandler.c -o terminal
	./terminal
