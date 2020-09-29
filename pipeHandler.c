#include "headers.h"
#include "commandHandler.h"

int checkPipe(char *input){
    int i=0;
    for(i=0;input[i]!='\0';i++){
        if(input[i]=='|')
            return 1;
    }
    return 0;
}

int checkPipeandrunCommand(char **parsed, char *input){
    if(checkPipe(input)==0)
        runCommand(parsed, input);
    else{
        printf("Pipe(s) found yet to be implemented\n");
    }
}
