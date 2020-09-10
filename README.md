# Terminal Written in C
A custom terminal for Linux supporting bash commands with support for almost all built in functions either through system call or custom written built in function.

## Custom Functions

## How To Use


## Files Description
All headers files have Macros and function definations for global accesibility of the functions in the respective C files

* __makefile__
> Compiles all objects and starts the terminal

* __headers.h__
> Has all the header Files required across the complete Terminal code also has the inclusion for childHandler.

* __commands.h__
> Has all the header File inclusions required for custom functions.

* __main.c__
> Main Driver Code That displays prompt and accepts input in a loop, also ahs the signal handler for when a child exits.

* __prompt.c__
> Gets the username and host name and creates the prompt part of shell 

* __input.c__
> Takes the input from a string, parses it at semicolons and in a loop each command is space separated and sent to command handler as a 2d array.

* __commadHandler.c__
> has a few functions that take care of stripping whitespaces checking if the command is custom function or built in. If built in checks whether to execute in foreground or background.

* __childHandler.c__
> Has a killChild function that starts when a child process has completed successfully and has a kill all function that kills all paused childs in background on terminal exit.

* __cd.c__
> Has code for changing directory.

* __echo.c__
> Has a code for echoing whatever is given (Ignores '"' and environment variables)

* __history.c__
> Functions that store the history max upto 20 in a file across sessions.

* __ls.c__
> Functions for listing all files and folder with/without hiddem with/without all details.

* __pwd.c__
> Function that prints current absolute dir

* __pinfo.c__
> Prints Process info given pid else prints the info of terminal
