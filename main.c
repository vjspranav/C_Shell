#include "headers.h"
#include "prompt.h"
#include "input.h"
char homedir[PATH_MAX];
char historypath[PATH_MAX];
int BACKUP_STDOUT_FILENO, BACKUP_STDIN_FILENO;
int main_terminal_id;
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
    main_terminal_id=getpid();
    // Getting the homedir
    if (getcwd(homedir, sizeof(homedir)) == NULL)
        exit(0);
    if (getcwd(historypath, sizeof(historypath)) == NULL)
        exit(0);
    addhistory();

    // For andling bg childs
    signal(SIGCHLD, killChilds);
    // Ctr+C
    signal(SIGINT, ctcHandler);
    // Ctrl+Z
    // signal(SIGTSTP, ctzHandler);
    
    while (1)
    {
        prompt();
        input();
    }
}
