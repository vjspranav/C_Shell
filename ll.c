#include "ll.h"

Node *temp, *last;
Node *listptr=NULL;

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

char getState(int id){
    char buff[1000];
    char c;
    int d, i;
    struct stat state;
    snprintf(buff, 1000, "/proc/%d/stat", id);
    FILE* fp = fopen(buff, "r");
    if (fp) {
        if(!fscanf(fp, "%d %s %c", &d, &buff, &c)) {
            printf("%d Not accessible\n", d);
            perror("Error");
            return -1;
        }else{
            return c;
        }
    }
}

void printState(char st){
    if(st=='T')
        printf("Stopped");
    else if(st=='S')
        printf("Running");
    else if(st=='R')
        printf("Running");    
    else
        printf("Unknown");
}

// Public Functions
void createListNode(process n){
	Node *newnode = malloc ( sizeof(Node) );
	newnode->data.inbg = n.inbg; // Handle  copy
	newnode->data.id = n.id; // Handle  copy
 	newnode->data.num = n.num; // Handle  copy
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

int getidwithNum(int num){
	Node *t=listptr, *t1;
    while(t!=NULL){
        if(t->data.num==num)
            return t->data.id;
        t=t->next;
    }
    return -1;
}

void printProcess(){
	int i=0;
    Node *t=listptr;
    if(t==NULL)
        printf("No Process in bg\n");
    else{
        while(t->next!=NULL){
            char st=getState(t->data.id);
            printf("[%d] ", t->data.num);
            printState(st);
            printf(" %s with id=%d\n", t->data.name, t->data.id);
            t=t->next;
        }
        char st=getState(t->data.id);
        printf("[%d] ", t->data.num);
        printState(st);
        printf(" %s with id=%d\n", t->data.name, t->data.id);
    }
}

int deleteAllNodes(){
    Node *t=listptr;
    if(t==NULL)
        return 1;
    int i=0;
    while(t!=NULL){
        int id=t->data.id;
        kill(id, SIGKILL);
        //printf("[%d] %s with pid %d Stopped\n", i++, t->data.name, t->data.id);
        t=t->next;
        //free(t);
//        t=listptr;
    }
    return 0;
//    listptr=temp=last=NULL;
}
