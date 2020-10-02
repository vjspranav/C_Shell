#include "headers.h"
#include "commandHandler.h"

int BACKUP_STDOUT_FILENO_p, BACKUP_STDIN_FILENO_p;
int numPipes;

int parsePipes(char* inp, char** parsed){
    int i=0;    
    parsed[i] = strtok(inp, "|");
    i+=1;
    while(1){
        parsed[i] = strtok(NULL, "|");
        if(parsed[i]==NULL){
            numPipes=i;
            return 0;
        }
        i+=1;
    }
    return -1;
}

int parseCommands(char* inp, char** parsed){
    int i=0;    
    parsed[i] = strtok(inp, " ");
    i+=1;
    while(1){
        parsed[i] = strtok(NULL, " ");
        if(parsed[i]==NULL){
            return 0;
        }
        i+=1;
    }
    return -1;
}

int checkPipe(char *input){
    int i=0;
    for(i=0;input[i]!='\0';i++){
        if(input[i]=='|')
            return 1;
    }
    return 0;
}

int runPipe(char *input){
    char *commands[1000];
    parsePipes(input, commands);
    int i=0, pipe_des[2];
    start:
        // create a pipe
        if (pipe(pipe_des) < 0) {
            perror("Could not create pipe.");
            exit(1);
        }
        
        int f=fork();
        
        if(f==0){
            close(pipe_des[1]);
            //Setting stdin to read side of pipe
            if (dup2(pipe_des[0], STDIN_FILENO) < 0) {
                perror("Unable to duplicate file descriptor.");
                return -1;
            }
            
            if(commands[i]){
                i++;
                if(commands[i]){
                    goto start;
                }
            }
            close(pipe_des[0]);
            exit(0);
        }else{
            int isfinal=0;
            close(pipe_des[0]);
            // Setting stdout to pipe
            if (dup2(pipe_des[1], STDOUT_FILENO) < 0) {
                perror("Unable to duplicate file descriptor.");
                return -1;
            }
            if(commands[i+1]==NULL){
                if (dup2(BACKUP_STDOUT_FILENO_p, STDOUT_FILENO) < 0) {
                    perror("Could Not restore to original output stream");
                    exit(1);
                }      
                close(pipe_des[1]);
                isfinal=1;
            }

            char *parsed[1000]; 
            char temp[PATH_MAX];
            strcpy(temp, commands[i]);
            int j=0;
            while(temp[j]==' ') j++;

            parseCommands(&temp[j], parsed);
            runCommand(parsed, &commands[i][j]);
            if(isfinal){
                exit(0);
            }
            // Waiting for child
            int status;
            if(!isfinal){
                do{
                    waitpid(f, &status, WUNTRACED);
                }while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
            }
            if(f!=0)
                kill(f, SIGKILL);
            close(pipe_des[0]);
            close(pipe_des[1]);
        }
}


/* Code for Pipes (One with multiple childs and one which works for 2 pipes)
 * 
    int runPipe(char *input){
        char *commands[1000];
        parsePipes(input, commands);
        int i=0, pipe_des[2];
        start:
            // create a pipe
            if (pipe(pipe_des) < 0) {
                perror("Could not create pipe.");
                exit(1);
            }
            
            int f=fork();
            
            if(f==0){
                close(pipe_des[1]);
                //Setting stdin to read side of pipe
                if (dup2(pipe_des[0], STDIN_FILENO) < 0) {
                    perror("Unable to duplicate file descriptor.");
                    return -1;
                }
                
                if(commands[i]){
                    i++;
                    if(commands[i]){
                        goto start;
                    }
                }
                close(pipe_des[0]);
                exit(0);
            }else{
                int isfinal=0;
                close(pipe_des[0]);
                // Setting stdout to pipe
                if (dup2(pipe_des[1], STDOUT_FILENO) < 0) {
                    perror("Unable to duplicate file descriptor.");
                    return -1;
                }
                if(commands[i+1]==NULL){
                    if (dup2(BACKUP_STDOUT_FILENO_p, STDOUT_FILENO) < 0) {
                        perror("Could Not restore to original output stream");
                        exit(1);
                    }      
                    close(pipe_des[1]);
                    isfinal=1;
                    printf("Restored stdout for %s and final=%d\n", commands[i], isfinal);
                }

                char *parsed[1000]; 
                char temp[PATH_MAX];
                strcpy(temp, commands[i]);
                int j=0;
                while(temp[j]==' ') j++;

                parseCommands(&temp[j], parsed);
                runCommand(parsed, &commands[i][j]);
                if(isfinal){
                    exit(0);
                    fflush(stdout);
                }
                close(pipe_des[0]);
                close(pipe_des[1]);
                // Waiting for child
                int status;
                if(!isfinal){
                    do{
                        waitpid(f, &status, WUNTRACED);
                    }while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
                }
            }

        int i=0;
        char temp[PATH_MAX];
        while(commands[i]){
            char *parsed[1000];
            strcpy(temp, commands[i]);
            printf("%s\n", commands[i++]);
                int j=0;
                while(temp[j]==' ') j++;
            printf("%s and %d spaces\nparsed into: ", &temp[j], j);     
            parseCommands(&temp[j], parsed);
            int k=0;
            while(parsed[k]){
                printf("%s  ", parsed[k++]);
            }
            printf("\n\n");
        }
        fflush(stdout);
    }

int runPipeTwo(char *input){
    char *commands[1000], *parsed[1000], temp[PATH_MAX];
    parsePipes(input, commands);
    int i=0, pipe_des[2];
    pipe(pipe_des);
    int f=fork();
    if(f==0){
        close(pipe_des[0]);
        dup2(pipe_des[1], STDOUT_FILENO);
        strcpy(temp, commands[0]);
        int j=0;
        while(temp[j]==' ') j++;
        parseCommands(&temp[j], parsed);
        runCommand(parsed, &commands[0][j]);
        close(pipe_des[1]);
        exit(0);
    }else{
        close(pipe_des[1]);
        dup2(pipe_des[0], STDIN_FILENO);
        strcpy(temp, commands[1]);
        int j=0;
        while(temp[j]==' ') j++;
        parseCommands(&temp[j], parsed);
        // Waiting for child
        int status;
        do{
            waitpid(f, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
        runCommand(parsed, &commands[1][j]);
        close(pipe_des[0]);
    }
}
*/

int checkPipeandrunCommand(char **parsed, char *input){
    BACKUP_STDIN_FILENO_p=dup(STDIN_FILENO);
    BACKUP_STDOUT_FILENO_p=dup(STDOUT_FILENO);

    if(checkPipe(input)==0)
        runCommand(parsed, input);
    else{
        runPipe(input);
    }        
    //Restoring back to original
    if (dup2(BACKUP_STDOUT_FILENO_p, STDOUT_FILENO) < 0) {
        perror("Could Not restore to original output stream");
        exit(1);
    }    
    if (dup2(BACKUP_STDIN_FILENO_p, STDIN_FILENO) < 0) {
        perror("Could Not restore to original input stream");
        exit(1);
    }
}
