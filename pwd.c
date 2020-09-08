#include "pwd.h"
#include "headers.h"

int pwd(){
     char cwd[PATH_MAX];
     if (getcwd(cwd, sizeof(cwd)) == NULL){
        perror("Failed to get dir");
        exit(0);   
     }
     printf("%s\n", cwd);
}
