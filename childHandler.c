#include "headers.h"
#include "commands.h"
#include "childHandler.h"

int numbgChilds=0;

//process bgProcess[50];

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
        if(status==0)
            printf("\n[%d] %s pid %d exited successfully\n",t->data.num, t->data.name, pid, status, id);
        else
            printf("\n[%d] %s pid %d exited abnormally with error: %d\n",t->data.num, t->data.name, pid, status);
        deleteNodewithid(pid);
    }
}

int killallChilds(){
    return deleteAllNodes();
}
