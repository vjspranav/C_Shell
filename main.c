#include "headers.h"
#include "prompt.h"
#include "input.h"
char homedir[PATH_MAX];
char historypath[PATH_MAX];
int BACKUP_STDOUT_FILENO, BACKUP_STDIN_FILENO;

extern Node *listptr;

void addhistory(){
    int n=strlen(historypath);
    historypath[n]='/';
    historypath[n+1]='h';
    historypath[n+2]='i';
    historypath[n+3]='s';
    historypath[n+4]='t';
    historypath[n+5]='o';
    historypath[n+6]='r';
    historypath[n+7]='y';
    historypath[n+8]='\0';

}

int main()
{
    // Backing up file descriptors of STDIN and STDOUT 
    BACKUP_STDIN_FILENO=dup(STDIN_FILENO);
    BACKUP_STDOUT_FILENO=dup(STDOUT_FILENO);
    
    // Getting the homedir
    if (getcwd(homedir, sizeof(homedir)) == NULL)
        exit(0);
    if (getcwd(historypath, sizeof(historypath)) == NULL)
        exit(0);
    addhistory();
    signal(SIGCHLD, killChilds);
    while (1)
    {
        prompt();
        input();
    }
}
