main:
	gcc -g main.c prompt.c input.c commandHandler.c history.c cd.c echo.c ls.c pwd.c pinfo.c -o terminal
	./terminal
