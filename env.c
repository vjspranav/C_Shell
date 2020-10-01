#include "env.h"
#include "headers.h"

int csetenv(char **parsed){
    int i=0;
    while(parsed[i]) i++;
    if(i<2 || i>3){
        printf("Error Wrong number of args expected 2 got %d\n", i-1);
        return -1;
    }
    if(parsed[2])
        i=setenv(parsed[1], parsed[2], 0);
    else
        i=setenv(parsed[1], " ", 0);
    if(i!=0)
        perror("Setting value failed: ");
    // For testing if set
    //printf("Values of %s is %s\n", parsed[1], getenv(parsed[1]));
    return 0;
}

int cunsetenv(char **parsed){
    int i=0;
    while(parsed[i]) i++;
    if(i!=2){
        printf("Error Wrong number of args expected 2 got %d\n", i-1);
        return -1;
    }
    i=unsetenv(parsed[1]);
    if(i!=0)
        perror("Clearing value failed: ");
    return 0;
}

