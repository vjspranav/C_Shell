#include "pipeHandler.h"
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

int is_empty(char s[]) {
    int i=0;
    while (s[i] != '\0') {
        if (s[i]!=' ')    
            return 0;
        i++;
    }
    return 1;
}

int input() {
        char *inp=NULL;
        size_t len = 0;
        getline(&inp, &len, stdin);
        if(!inp[0]){
            printf("\n");
            exit(0);
        }
        // Fixes for pressing enter without any command
        if(inp[0]=='\n')
            return 0;
        if(is_empty(inp))
            return 0;
        inp[strlen(inp)-1]='\0';
        add_history(inp);
        checkMulti(inp);
        inp=NULL;
        return 0;
}

int checkMulti(char* inp){
    char *temp=NULL;
    int i=0;
/**
    command[i] = strtok(inp, ";");
    i+=1;
    while(1){
        char *parsed[1000];
        char og[strlen(inp)];            
        strcpy(og, command[i-1]);
        if(!strcmp("exit", command[i-1])){
            exit(0);
        }
        parseString(command[i-1], parsed);    
        runCommand(parsed, og);
        command[i] = strtok(NULL, ";");
        printf("%s\n", command[i]);
        if(command[i]==NULL){
            return 0;
        }
        i+=1;
            
    }
*/
    do {
        // Splitting at next ; if exists
        for( temp = inp; *inp && *inp != ';'; inp++ )
                ;
        if(*inp == ';'){
            *inp='\0';
        }
        while(*(inp+1)==' ') *inp++; //Removing leading whitespaces
        *inp++ = '\0';  
        if (temp) {
            if(is_empty(temp))
                continue;
            char *parsed[1000];
            char og[strlen(temp)];            
            strcpy(og, temp);
            if(!strcmp("exit", temp) || !strcmp("quit", temp)){
                killallChilds();
                exit(0);
            }
            int i=0;
            while(temp[i]==' ') i++;
            parseString(&temp[i], parsed);    
            checkPipeandrunCommand(parsed, &og[i]);
            memset(og, 0, strlen(og));
        }
    } while( *inp );
}
