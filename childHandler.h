#ifndef __CHILDHANDLER_H
#define __CHILDHANDLER_H

struct process{
    int id;
    char name[PATH_MAX];
    int inbg;
};

typedef struct process process;

void killChilds(int id);
int killallChilds();


#endif
