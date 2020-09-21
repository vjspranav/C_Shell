#include "ll.h"
#include "headers.h"


Node *temp, last;

// Private functions
void delete_beg(Node *listptr){
	Node *t=listptr;
	listptr=listptr->next;
	free(t);	
}

void delete_last(Node *listptr){
	Node *t=listptr;
    while(t->next!=last) t=t->next;
    last=t;
    t=t->next;
    t->next=NULL;
    free(t);	
}

// Public Functions
void create(Node *listptr, process n){
	Node *newnode = malloc ( sizeof(Node) );
	newnode->data.inbg = n.inbg; // Handle  copy
	newnode->data.id = n.id; // Handle  copy
    strcpy(newnode->data.name, n.name);
	newnode->next = NULL;
	if(listptr==NULL)
		listptr = newnode;
	else
		temp->next = newnode;
	temp=newnode;
    last=newnode;
}

int count(){
	Node *t;
	int n=0;
	t = listptr;
	while(t!=NULL){
		n++;
		t = t->next;
	}
	return n;
}

int deleteNodewithid(Node *listptr, int id){
	Node *t=listptr, *t1;
    if(listptr->data.id==id)
        delete_beg(listptr);
    else if(last->data.id==id)
        delete_last(listptr);
    else{
        while(t->next->data.id!=id && t->next!=last) t=t->next;
        if(t->next->data.id!=id)
            printf("Child already killed\n");
        else{
            t1=t->next;
            t->next=t->next->next;
            free(t1);
        }
    }
}

Node *getNodewithid(Node *listptr, int id){
	Node *t=listptr, *t1;
    while(t->next!=NULL){
        if(t->data.id==id)
            return t;
        t1=t->next;
    }
    return NULL;
}

void printProcess(Node *listptr){
	int i=0;
    Node *t=listptr;
    if(t==NULL)
        printf("No Process in bg");
    else{
        while(t->next!=NULL){
            printf("[%d] %s with id=%d\n", i++, t->data.name, t->data.id)
            t=t->next;
        }
    }
}

void deleteAllNodes(Node *listptr){
    Node *t=listptr;
    while(t!=NULL){
        printf("[] %s Stopped pid: %d\n", t->data.name, t->data.id);
        delete_beg(listptr);
        t=listptr;
    }   
}
