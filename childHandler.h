#ifndef __CHILDHANDLER_H
#define __CHILDHANDLER_H

struct process{
    int id;
    char name[PATH_MAX];
};

typedef struct process process;

int killChilds();
int killallChilds();


#endif
