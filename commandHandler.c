#include "headers.h"
#include "commands.h"
#include "commandHandler.h"

static int num_custom_commands=6;

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
    pid_t sid;
    for(i=0;i<num_custom_commands;i++)
        if(!strcmp(parsed[0], custom_commands[i])){
            command_id=i+1;
            break;
        }
    if(command_id)
        runOwnCommand(command_id, &input[strlen(custom_commands[command_id-1]) + 1 ], parsed);
    else{
        int is_and=isAnd(input);
        int f = fork();
        if(is_and){
            i=0;
            while(parsed[i]!=NULL)
                i+=1;
            parsed[i-1]=NULL;
        }
        if(f>0){
            if(!is_and)
                wait(NULL);
            else{
                signal(SIGCHLD, SIG_IGN);
            }
            return 0;
        }
            if(is_and){
                sid = setsid();
                    int fd;
                    if ((chdir("/")) < 0)  
                    {  
                    exit(EXIT_FAILURE);  
                    }  


                    fd = open("/dev/null",O_RDWR, 0);  

                    if (fd != -1)  
                    {  
                    dup2 (fd, STDIN_FILENO);  
                    dup2 (fd, STDOUT_FILENO);  
                    dup2 (fd, STDERR_FILENO);  

                    if (fd > 2)  
                    {  
                    close (fd);  
                    }  
                    }  

                    /*resettign File Creation Mask */  
                    umask(027);  
                fprintf(stderr, "\n%s started PID=%d\n", parsed[0], getpid());
                if(execvp(parsed[0], parsed)==-1)
                    printf("bash: %s: command not found\n", parsed[0]);
                fprintf(stderr, "\n%d exited %s\n", getpid(), parsed[0]);
                exit(0);
            }else{
                if(execvp(parsed[0], parsed)==-1)
                    printf("bash: %s: command not found\n", parsed[0]);
            }
    }
} 

int runOwnCommand(int command_id, char* input, char** parsed){
    switch(command_id){
        case 1: echo(input); break;
        case 2: ls(parsed); break;
        case 3: cd(input); break;
        case 4: print_history(); break;
        case 5: pwd(); break;
        case 6: pinfo(input); break;
        default: break;
    }
    return 0;
}
