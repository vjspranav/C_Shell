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

int runPipeCommand(char *input, int in_des, int out_des){
    char *parsed[1000]; 
    char temp[PATH_MAX];
    strcpy(temp, input);
    int j=0;
    while(temp[j]==' ') j++;
    parseCommands(&temp[j], parsed);
    //if (in_des != 0){
    //    dup2(in_des, STDIN_FILENO);
    //}
    //if (out_des != 1){
    //    dup2(out_des, STDOUT_FILENO);
    //}
    //printf("Running First Command %s\n", &input[j]);
    runCommand(parsed, &input[j], in_des, out_des);
}

int runPipe(char *input){
    int pipefd[2];
    int in_des = 0, i=0;
    char *commands[1000];
    parsePipes(input, commands);
    int no=numPipes;
    for (i=0; i<no-1; i++){
        printf("%d/%d\n", i, no);
        pipe(pipefd);
        //fprintf(0, "Executing %s\n", commands[i]);
        runPipeCommand(commands[i], in_des, pipefd[1]);
        close(pipefd[1]);
        in_des = pipefd[0];
    }
    printf("Running Final command %s\n", commands[i]);
    runPipeCommand(commands[i], in_des, BACKUP_STDOUT_FILENO_p);
    printf("Running Final command %s\n", commands[i]);
}

int checkPipeandrunCommand(char **parsed, char *input){
    BACKUP_STDIN_FILENO_p=dup(STDIN_FILENO);
    BACKUP_STDOUT_FILENO_p=dup(STDOUT_FILENO);

    if(checkPipe(input)==0)
        runCommand(parsed, input, 0, 1);
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
