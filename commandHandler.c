#include "headers.h"
#include "commands.h"
#include "commandHandler.h"

static int num_custom_commands=6;
extern int numbgChilds;
extern process bgProcess[50];

int isAnd(char *input){
    int i=strlen(input)-1;
    *input=*(input+i);
    while(*input==' ')
        *input-=1;
     if(*input=='&'){
         *input=='\0';
         return 1;
     }
     return 0;
        
}

int runCommand(char **parsed, char* input){
    char* custom_commands[num_custom_commands];
    custom_commands[0]="echo";
    custom_commands[1]="ls";
    custom_commands[2]="cd";
    custom_commands[3]="history";
    custom_commands[4]="pwd";
    custom_commands[5]="pinfo";

    int i, command_id=0;
    for(i=0;i<num_custom_commands;i++)
        if(!strcmp(parsed[0], custom_commands[i])){
            command_id=i+1;
            break;
        }
    if(command_id)
        runOwnCommand(command_id, &input[strlen(custom_commands[command_id-1]) + 1 ], parsed);
    else{
        int is_and=isAnd(input);
        if(is_and){
            int i=0;
            while(parsed[i]!=NULL)
                i+=1;
            parsed[i-1]=NULL;
            if(numbgChilds>50){
                printf("More than 50 childs in background, request terminated");
                return -1;
            }
        }
        int f = fork();
        if (f>0){
            if(!is_and){
                int status;
                do{
                    waitpid(f, &status, WUNTRACED);
                }while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
            }else{
                bgProcess[numbgChilds].id=f;
                bgProcess[numbgChilds].inbg=0;
                strcpy(bgProcess[numbgChilds].name, parsed[0]);
                numbgChilds+=1;
            }
            return 0;
        }else if(f<0){
            printf("Fork Failed\n");
        }else {
            if(is_and){
                setpgid(0, 0);
            }
            if(execvp(parsed[0], parsed)==-1){
                printf("bash: %s: command not found\n", parsed[0]);
                exit(0);
            }
            exit(0);
        }
        
    }
} 

int runOwnCommand(int command_id, char* input, char** parsed){
    switch(command_id){
        case 1: echo(input); break;
        case 2: ls(parsed); break;
        case 3: cd(input); break;
        case 4: print_history(input); break;
        case 5: pwd(); break;
        case 6: pinfo(input); break;
        default: break;
    }
    return 0;
}
