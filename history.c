#include "history.h"
#include "headers.h"
char hist[40][PATH_MAX];
int nlines;
extern char homedir[PATH_MAX];
extern char historypath[PATH_MAX];

int stoi (char * input){
    int output;
    char * end;
    output = strtol (input, & end, 10);
    if (end == input) 
        return 10;
    if(output>=1 || output<=20)
        return output;
    else
        return 10;
}

int add_history(char *command){
    FILE *fhi;
    char * line=NULL;
    int i=0, j=0, k=0, nf=0;
    ssize_t read, len=0;
    fhi=fopen(historypath, "r");
    if (!fhi) {
        nf=1;
        fhi=fopen(historypath, "w");
        if (!fhi) {
            printf("Unable to save to history, history won't be logged\n");
            perror("Error: ");
            return -1;
        }
        fclose(fhi);
    }
    if(nf!=1){
        while ((read = getline(&line, &len, fhi)) != -1) {
            strcpy(hist[i], line);
            i++;
        }
        nlines=i;
        if(nlines>=20){
            for(j=0;j<19;j++)
                strcpy(hist[j], hist[j+1]);
            fclose(fhi);
            fhi=fopen(historypath, "w");
            for(j=0;j<19;j++){
                fprintf(fhi, "%s", hist[j]);        
            }
            fclose(fhi);
        }
    }
    fhi=fopen(historypath, "a");
    fprintf(fhi, "%s\n", command);
    fclose(fhi);
    return 0;
}

int print_history(char * input){
    int n=stoi(input);
    char * line=NULL;
    int i=0, j=0, cmdInHistory=0;
    ssize_t read, len=0;
    n=n>20?20:n; // If input is greater than 20, print only 20;
    FILE *fhi;
    fhi=fopen(historypath, "r");
    if (!fhi) {
        printf("Unable to open history\n");
        return -1;
    }
    
    // Printing History
    while ((read = getline(&line, &len, fhi)) != -1) {
        strcpy(hist[i], line);
        i++;
    }
    if(n>i){
        printf("Only %d entries\n", i);
        for(j=0;j<i;j++)
            printf("%s", hist[j]);
        fclose(fhi);
        return 0;
    }else{
        for(j=i-n;j<i;j++)
            printf("%s", hist[j]);
        fclose(fhi);
        return 0;        
    }
}
