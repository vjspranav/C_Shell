#include "cd.h"
#include "headers.h"

int cd(char* path){
    extern char homedir[PATH_MAX];
    /*
     * If Dir starts with ~ changw ith respect to homedir
     * 
     */
    if('~'==path[0]){
        int i=0, j=1;
        char npath[strlen(homedir)+strlen(path)];
        while(homedir[i]){
            npath[i]=homedir[i];
            i++;
        }
        while(path[j]){
            npath[i]=path[j];
            i++;
            j++;
        }
        npath[i]='\0';
        cd(npath);
    }else if(chdir(path)==-1){
        if(errno==ENOENT)
            printf("Path Doesn't Exist\n");
        else if(errno==ENOTDIR)
            printf("A component is Not Dir\n");
        else if(errno==EACCES)
            printf("Permission Denied\n");
        else
            perror("Error: ");
        return -1;
    }else{
        return 0;
    }
}
