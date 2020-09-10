#include "headers.h"
#include "commands.h"
#include "childHandler.h"

int numbgChilds=0;

process bgProcess[50];

int killChilds(){
    int i, status;
    for(i=0;i<numbgChilds;i++){
        printf("%d \n", waitpid(bgProcess[i].id, &status, 0));
        fprintf(stderr, "%s exited successfully pid: %d ", bgProcess[i].name, bgProcess[i].id);
    }
    numbgChilds=0;
}

int killallChilds(){
    int i;
    for(i=0;i<numbgChilds;i++){
        kill(bgProcess[i].id, SIGKILL);
    }    
}
