#ifndef __LL_H
#define __LL_H
#include "headers.h"

struct Node{
	process data;
	struct Node *next;
};

typedef struct Node Node;

void createListNode(process n);
int count();
int deleteNodewithid(int id);
Node *getNodewithid(int id);
void printProcess();
void deleteAllNodes();

#endif
