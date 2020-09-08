#include "echo.h"
#include "headers.h"

int checkDir(int dir[], int numArg){
    int i=0;
    for(i=0;i<numArg;i++)
        if(dir[i]==1)
            return 1;
    return 0;
}

int lsdir(char* path, int l, int a){
    int i;
    char *c;
    DIR* d;
    struct passwd *pw;
    struct group *gp;
    struct stat fs;
    d = opendir(path);
    struct dirent *dir;
    if (d) {
        if(!l){
            while ((dir = readdir(d)) != NULL) {
                if(dir->d_name[0]!='.' || a==1)
                    printf("%s\n", dir->d_name);
            }
        }else{
            while ((dir = readdir(d)) != NULL) {            
                if(dir->d_name[0]!='.' || a==1){
                    stat(dir->d_name,&fs);  
                    printf((S_ISDIR(fs.st_mode)) ? "d" : "-");
                    printf((fs.st_mode & S_IRUSR) ? "r" : "-");
                    printf((fs.st_mode & S_IWUSR) ? "w" : "-");
                    printf((fs.st_mode & S_IXUSR) ? "x" : "-");
                    printf((fs.st_mode & S_IRGRP) ? "r" : "-");
                    printf((fs.st_mode & S_IWGRP) ? "w" : "-");
                    printf((fs.st_mode & S_IXGRP) ? "x" : "-");
                    printf((fs.st_mode & S_IROTH) ? "r" : "-");
                    printf((fs.st_mode & S_IWOTH) ? "w" : "-");
                    printf((fs.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    printf("%d ",fs.st_nlink);
                    pw=getpwuid(fs.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fs.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%10d ",fs.st_size);
                    c=ctime(&fs.st_mtime);
                    for(i=4;i<=15;i++)
                        printf("%c",c[i]);
                    printf(" ");
                    printf("%s\n",dir->d_name); 
                }
            }
        }
        closedir(d);
  }
}


int ls(char** parsed){
    int a=0, l=0, i=0, j=0, numArg=0;
    while(parsed[numArg]) numArg++;
    int dir[numArg];
    
    // Test
    // printf("Number of arguments=%d\n", numArg);

    dir[0]=0;
    if(numArg>1){
        for(i=1;i<numArg;i++){

            // Test
            // printf("Argument is %s\n", parsed[i]);

            if(parsed[i][0]=='-'){
                l=(parsed[i][1]=='l')?1:(parsed[i][2]=='l'?1:l);
                a=(parsed[i][1]=='a')?1:(parsed[i][2]=='a'?1:a);

                // Handling Invalid Arguments: Defaulting to ls
                if(parsed[i][1]!='l'&& parsed[i][1]!='a'){
                    printf("ls: Invalid Option %c, doing ls\n", parsed[i][1]);                
                    l=a=0;
                }else if(strlen(parsed[i])>2){
                    if(parsed[i][2]!='l'&& parsed[i][2]!='a'){
                        printf("ls: Invalid Option %c, doing ls\n", parsed[i][2]);                    
                        l=a=0;
                    }
                }else if(strlen(parsed[i])>2){
                        printf("ls: Invalid Option %s, doing ls\n", &parsed[i][1]);                    
                        l=a=0;                    
                }
                
                // Test
                // printf("l=%d a=%d\n", l, a);
                if(l==1||a==1)
                    dir[i]=0;
                else
                    dir[i]=1;
            }else
                dir[i]=1;
            
            // Test
            // printf("Is Dir=%d\n", dir[i]);
        }
        if(checkDir(dir, numArg)){
            for(i=0;i<numArg;i++){
                if(dir[i]){
                    lsdir(parsed[i], l, a);
                }
            }
        }else{
            lsdir(".", l, a);
        }
    }else{
        lsdir(".", 0, 0);
    }
}

