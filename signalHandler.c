#include "headers.h"
#include "signalHandler.h"
extern int main_terminal_id;

void ctcHandler(int id) {
    return;
}

void ctzHandler(int id) {
    int status;
    int pid=waitpid(-1, &status, WNOHANG);
    if(pid==main_terminal_id){
        printf("Same\n");
        return;
    }
    kill(getpid(), SIGTSTP);
}
