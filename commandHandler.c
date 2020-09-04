#include "headers.h"
#include "commands.h"
#include "commandHandler.h"

static int num_custom_commands=4;

int runCommand(char **parsed){
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
        runOwnCommand(command_id);
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

int runOwnCommand(int command_id){
    switch(command_id){
        case 1: printf("Entered echo\n"); break;
        case 2: printf("Entered ls\n"); break;
        case 3: printf("Entered cd\n"); break;
        case 4: print_history(); break;
        default: break;
    }
    return 0;
}
