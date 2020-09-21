#include "ll.h"

Node *temp, *last;
extern Node *listptr;

// Private functions
void delete_beg(){
	Node *t=listptr;
	listptr=listptr->next;
	free(t);	
}

void delete_last(){
	Node *t=listptr;
    while(t->next!=last) t=t->next;
    last=t;
    t=t->next;
    last->next=NULL;
    free(t);	
}

// Public Functions
void createListNode(process n){
	Node *newnode = malloc ( sizeof(Node) );
	newnode->data.inbg = n.inbg; // Handle  copy
	newnode->data.id = n.id; // Handle  copy
    strcpy(newnode->data.name, n.name);
	newnode->next = NULL;
    temp=last;
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

int deleteNodewithid(int id){
	Node *t=listptr, *t1;
    if(listptr->data.id==id)
        delete_beg();
    else if(last->data.id==id)
        delete_last();
    else{
        while(t->next->data.id!=id && t->next!=last) t=t->next;
        if(t->next->data.id!=id)
            printf("Child already killed\n");
        else{
            t1=t->next;
            t->next=t1->next;
            free(t1);
        }
    }
}

Node *getNodewithid(int id){
	Node *t=listptr, *t1;
    while(t!=NULL){
        if(t->data.id==id)
            return t;
        t=t->next;
    }
    return NULL;
}

void printProcess(){
	int i=0;
    Node *t=listptr;
    if(t==NULL)
        printf("No Process in bg\n");
    else{
        while(t->next!=NULL){
            printf("[%d] %s with id=%d\n", i++, t->data.name, t->data.id);
            t=t->next;
        }
        printf("[%d] %s with id=%d\n", i++, t->data.name, t->data.id);
    }
}

void deleteAllNodes(){
    Node *t=listptr;
    int i=0;
    while(t!=NULL){
        kill(t->data.id, SIGKILL);
        printf("[%d] %s with pid %d Stopped\n", i++, t->data.name, t->data.id);
        listptr=t->next;
        //free(t);
        t=listptr;
    }   
}
