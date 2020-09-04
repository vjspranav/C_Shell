#include "commandHandler.h"
#include "headers.h"
#include "history.h"
#include "input.h"

int parseString(char* inp, char** parsed){
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

int input() {
        char *inp=NULL;
        char *parsed[1000];
        size_t len = 0;
        getline(&inp, &len, stdin);
        if(!strcmp("exit\n", inp))
            exit(0);
        inp[strlen(inp)-1]='\0';
        add_history(inp);
        parseString(inp, parsed);
        runCommand(parsed);
        return 0;
}
