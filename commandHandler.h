#ifndef __COMMANDHANDLER_H
#define __COMMANDHANDLER_H

int runCommand(char **parsed, char* input);
int runOwnCommand(int command_id, char* input, char** parsed);
#endif
