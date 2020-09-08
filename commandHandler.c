#include "headers.h"
#include "commands.h"
#include "commandHandler.h"

static int num_custom_commands=4;

int runCommand(char **parsed, char* input){
    char* custom_commands[num_custom_commands];
    custom_commands[0]="echo";
    custom_commands[1]="ls";
    custom_commands[2]="cd";
    custom_commands[3]="history";

    int i, command_id=0;
    for(i=0;i<num_custom_commands;i++)
        if(!strcmp(parsed[0], custom_commands[i])){
            command_id=i+1;
            break;
        }
    if(command_id)
        runOwnCommand(command_id, &input[strlen(custom_commands[command_id-1]) + 1 ], parsed);
    else{
        int f = fork();
        if(f==0){
            execvp(parsed[0], parsed);
            exit(0);
        }
        else{
            wait(NULL);
            return 0;
        }
    }
} 

int runOwnCommand(int command_id, char* input, char** parsed){
    switch(command_id){
        case 1: echo(input); break;
        case 2: ls(parsed); break;
        case 3: cd(input); break;
        case 4: print_history(); break;
        default: break;
    }
    return 0;
}
