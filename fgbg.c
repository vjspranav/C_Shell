#include "env.h"
#include "headers.h"

extern int numbgChilds;

int sttoi (char * input){
    int output;
    char * end;
    output = strtol (input, & end, 0);
    return output;
}

int fg(char **parsed){
    int i=0;
    while(parsed[i]) i++;
    if(i!=2){
        printf("Error Wrong number of args expected 2 got %d\n", i-1);
        return -1;
    }
    int num = sttoi(parsed[1]);
    int pid=getidwithNum(num);
    if(num>numbgChilds || pid==-1){
        printf("Process with job number %d doesn't exist\n", num);
        return -1;
    }
    Node *curProcess=getNodewithid(pid);
    if(pid!=-1){
        deleteNodewithid(pid);
        setpgid(pid, getpgid(0));
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, pid);
        kill(pid, SIGCONT);
        int status;
        do{
            waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
        tcsetpgrp(STDIN_FILENO, getpgrp());
        
        //for Ctrl + Z
        if (WIFSTOPPED(status))
        {
            if (pid != -1)
                createListNode(curProcess->data);
        }
            
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        return 0;
    }
    return -1;
}

int bg(char **parsed){
    int i=0;
    while(parsed[i]) i++;
    if(i!=2){
        printf("Error Wrong number of args expected 1 got %d\n", i-1);
        return -1;
    }
    int num = sttoi(parsed[1]);
    int pid=getidwithNum(num);
    if(num>numbgChilds || pid==-1){
        printf("Process with job number %d doesn't exist\n", num);
        return -1;
    }
    Node *curProcess=getNodewithid(pid);
    kill(pid, SIGCONT);
    return 0;
}

int kjob(char **parsed){
    int i=0;
    while(parsed[i]) i++;
    if(i!=3){
        printf("Error Wrong number of args expected 3 got %d\n", i-1);
        return -1;
    }
    int num = sttoi(parsed[1]);
    int sig = sttoi(parsed[2]);
    int pid=getidwithNum(num);
    if(num>numbgChilds || pid==-1){
        printf("Process with job number %d doesn't exist\n", num);
        return -1;
    }
    if (kill(pid, sig) == -1) {
        perror("Error: ");
    }
}
