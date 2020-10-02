#include "headers.h"
#include "signalHandler.h"
extern int main_terminal_id;

void ctcHandler(int id) {
    return;
}

void ctzHandler(int id) {
    if(getpid()==main_terminal_id)
        return;
    kill(getpid(), SIGTSTP);
}
