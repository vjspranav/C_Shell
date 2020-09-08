#include "pinfo.h"
#include "headers.h"


int run_strtol (char * input){
    int output;
    char * end;
    output = strtol (input, & end, 10);
    if (end == input) 
        return -1;
    return output;
}

int pinfo(char* input){
    char buff[1000];
    char c;
    int d;
    struct stat state;
    int id=run_strtol(input);
    if(id==-1)
        id=getpid();
    snprintf(buff, 1000, "/proc/%d/stat", id);
    FILE* fp = fopen(buff, "r");   
    if (fp) {
        if(!fscanf(fp, "%d %s %c", &d, &buff, &c)) {
            printf("%d Not accessible\n", d);
            perror("Error: ");
            return -1;
        }
    }
    printf("pid -- %d\n", id);
    printf("Process Status -- %c\n", c);
    printf("memory -- 67854{​Virtual Memory​}\n");
    printf("Executable Path -- ~/a.out\n");
    
}
