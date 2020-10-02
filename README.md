# Terminal Written in C
A custom terminal for Linux supporting bash commands with support for almost all built in functions either through system call or custom written built in function.
Takes care of input output redirection with
```
ls > test.txt
sort < in.txt > out.txt
```
Does pipe handling (with IO redirection too)
```
ls | cat | grep test > out.txt
```

## Requirements
__GCC Version >= 10.2.0__  
Will work for lower Versions also but there could be unexpected warnings and errors.

## How To Use
__Run The Following command in the dir where you cloned the repo__
```
make
./terminal
```
or
__Copy Paste the following__
```
git clone https://github.com/vjspranav/C_Shell -b v1
cd C_Shell
make
./terminal
```

## Custom Functions
1. __echo__
```
echo string
```
> Ignoring extra whitespaces prints on shell

2. __ls__
```
ls <dirname> <dir2name> <filename> [options]
```
> ls or ls -a or ls -l or ls -al/la with dirname(s) and/or filename(s) and/or no arguments list it out.
> Tried to mimic actuall shell output/performace with multiple folders given or files given.

3. __cd__
```
cd dirpath
```
> dir path could be relative or absolute. '.' would be in same dir, '..' to previous dir, '\~' for terminal execute dir. 
Relative wrt to '\~' is also allowed.

4. __history__
```
history <num>
```
> last 10 commands in history would be printed if no num is provided else last num number of commands will be printed. (Stores only last 20 commands)

5. __pwd__
```
pwd
```
> Print current dir path

6. __pinfo__
```
pinfo
```
will give
```
pid -- 231
Process Status -- {R/S/S+/Z}
memory -- 67854{​Virtual Memory​}
Executable Path -- ~/a.out
```
or
```
pinfo pid
```
will give
```
pid -- (pid)
Process Status -- {R/S/S+/Z}
memory --123456 {​Virtual Memory​}
Executable Path -- /usr/bin/gcc
```
>> Gives info of the process with process id pid, if no pid is given the info of shell is shown.

7. __setenv__
```
setenv <name> <value>
```
> Set value to to variable name, if variable exists it's value is not overwritten, if no value is provided string.

8. __unsetenv__
```
unsetenv <name>
```
> Clears value of variable name.

9. __jobs__
```
jobs
```
will give
```
<vjspranav@archlinux:~>$ jobs
[1] Stopped nano with id=21076
[2] Stopped vim with id=21078 
[3] Running sleep with id=21081
```
> Will print a list of background running processes with jobnumber and pid

10. __kjob__
```
kjob <jobnumber> <signal>
```
> Will send kill signal __signal__ to process id with __job number__ which we get from jobs  

11. __fg__
```
fg <job number>
```
> Brings the running or stopped background job corresponding to ​jobnumber​ to the foreground, and changes its state to ​running​. The shellshould throw an error if no job with the given job number exists

12. __bg__
```
bg <job number>
```
> Changes the state of a stopped background job to running (in thebackground). The shell should throw an error if no background jobcorresponding to the given job number exists.

13. __overkill__
```
overkill
```
> Kills all created background processes.

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

* __pipeHandler.c__
> Has the code that handles pipes.

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

* __env.c__
> Has code for setenv and unsetenv

* __fgbg.c__
> Has code for fg bg and kjob

* __signalHandler__
> Handles signal interrupts ctrl+C and ctrl+Z
