#include "history.h"
#include "headers.h"
char hist[40][PATH_MAX];
int nlines;

int stoi (char * input){
    int output;
    char * end;
    output = strtol (input, & end, 10);
    if (end == input) 
        return -1;
    if(strlen(input)<=2)
        return output;
    else
        return 10;
}

int add_history(char *command){
    FILE *fhi;
    char * line=NULL;
    int i=0, j=0;
    ssize_t read, len=0;
    fhi=fopen("history", "r");
    if (!fhi) {
        printf("Unable to save to history, history won't be logged\n");
        perror("Error: ");
        return -1;
    }
    while ((read = getline(&line, &len, fhi)) != -1) {
        strcpy(hist[i], line);
        i++;
    }
    nlines=i;
    if(nlines>=20){
        for(j=0;j<19;j++)
            strcpy(hist[j], hist[j+1]);
        fclose(fhi);
        fhi=fopen("history", "w");
        for(j=0;j<19;j++){
            fprintf(fhi, "%s", hist[j]);        
        }
        fclose(fhi);
    }
    fhi=fopen("history", "a");
    fprintf(fhi, "%s\n", command);
    fclose(fhi);
    return 0;
}

int print_history(char * input){
    int n=stoi(input);
    char * line=NULL;
    int i=0;
    ssize_t read, len=0;
    FILE *fhi;
    fhi=fopen("history", "r");
    if (!fhi) {
        printf("Unable to open history\n");
        return -1;
    }
    
    // Printing History
    while ((read = getline(&line, &len, fhi)) != -1) {
        strcpy(hist[i], line);
        i++;
    }
    for(i=20-n;i<20;i++)
        printf("%s", hist[i]);
    fclose(fhi);
    return 0;
}
