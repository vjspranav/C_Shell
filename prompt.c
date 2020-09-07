#include "prompt.h"
#include "headers.h"

void prompt() {
    extern char homedir[PATH_MAX];
    char hostname[1024];
    char cwd[PATH_MAX];
    // int num=0
    int i=0;
    gethostname(hostname, 1024);
    
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        exit(0);
    if(!strncmp(homedir, cwd, strlen(homedir)))
        printf("<%s@%s:~%s>$ ", getenv("USER"), hostname, &cwd[strlen(homedir)]);
    else
        printf("<%s@%s:%s>$ ", getenv("USER"), hostname, cwd);        
 
    
    /* *
     * The Code snippet to only print Dir name in prompt instead of absolute/relative dir.
     *   
     * if(strcmp(homedir, cwd)){
     *    while(cwd[i]!='\0'){
     *        if( cwd[i]=='\\' || cwd[i]=='/')
     *            num=i+1;
     *        i+=1;
     * }
     *    printf("<%s@%s:%s>$ ", getenv("USER"), hostname, &cwd[num]);
     * }else{
     *    printf("<%s@%s:~>$ ", getenv("USER"), hostname);        
     * }
     */
}
