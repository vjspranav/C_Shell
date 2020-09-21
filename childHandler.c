#include "headers.h"
#include "commands.h"
#include "childHandler.h"

int numbgChilds=0;

//process bgProcess[50];
Node *listptr=NULL;

/*
   int getiofid(int id){
    int i;
    for(i=0;i<numbgChilds;i++)
        if(bgProcess[i].id==id)
            return i;
}
*/

void killChilds(int id){
    int status;
    int pid=waitpid(-1, &status, WNOHANG);
    if(pid>0){
        Node *t=getNodewithid(pid);
        printf("[] %s pid %d exited successfully\n", t->data.name, pid);
        deleteNodewithid(pid);
    }
}

int killallChilds(){
    deleteAllNodes();
}
