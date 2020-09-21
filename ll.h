#ifndef __LL_H
#define __LL_H

struct Node{
	process data;
	struct Node *next;
};

typedef struct Node Node;

void create(Node *listptr, process n);
int count();
int deleteNodewithid(Node *listptr, int id);
Node *getNodewithid(Node *listptr, int id);
void printProcess(Node *listptr);
void deleteAllNodes(Node *listptr);

#endif
