#ifndef __CHILDHANDLER_H
#define __CHILDHANDLER_H
#include <linux/limits.h>

struct process{
    int id;
    char name[PATH_MAX];
    int inbg;
};

typedef struct process process;

void killChilds(int id);
int killallChilds();


#endif
