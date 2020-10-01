#include "headers.h"
#include "signalHandler.h"
extern main_terminal_id;

void ctcHandler(int id) {
    return;
}

void ctzHandler(int id) {
    if(getpid()!=main_terminal_id)
        kill(getpid(), SIGTSTP);
    return;
}
