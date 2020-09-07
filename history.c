#include "history.h"
#include "headers.h"

int add_history(char *command){
    FILE *fhi;
    fhi=fopen("history", "a");
    if (!fhi) {
        printf("Unable to save to history, history won't be logged\n");
        perror("Error: ");
        return -1;
    }
    fprintf(fhi, "%s\n", command);
    fclose(fhi);
    return 0;
}

int print_history(){
    FILE *fhi;
    fhi=fopen("history", "r");
    if (!fhi) {
        printf("Unable to open history\n");
        return -1;
    }
    
    // Get File Size
    fseek(fhi, 0L, SEEK_END);
    off_t tsize = ftell(fhi);
    fseek(fhi, 0L, SEEK_SET);
    char *cmd = malloc(tsize);

    // Printing History
    while(fgets(cmd, sizeof(cmd), fhi))
        printf("%s", cmd);

    fclose(fhi);
    return 0;
}
