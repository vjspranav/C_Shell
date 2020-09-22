#include "headers.h"
#include "commands.h"
#include "commandHandler.h"

static int num_custom_commands=6;
extern int BACKUP_STDOUT_FILENO, BACKUP_STDIN_FILENO;
extern int numbgChilds;
//extern process bgProcess[50]; Moved to Linked List
extern Node *listptr;
process tempProcess;
char nText[PATH_MAX];

void removeWhiteSpaces(char *text){
    int start=0, end=strlen(text);
    while(text[start]==' ') start+=1;
    while(text[end]==' '){
        text[end]=='\0';
        end-=1;
    }
    int i=start, j=0;
    while(text[i]!='\0'){
        if(!(text[i]==' ' && text[i+1]==' ')){
            nText[j]=text[i];
            j++;
        }
        i++;
    }
    nText[j]='\0';
}

int isAnd(char *input){
    int i=strlen(input)-1;
    *input=*(input+i);
    while(input[i]==' ')
        i-=1;
     if(input[i]=='&'){
         input[i]=='\0';
         return 1;
     }
     return 0;
        
}

int runCommand(char **parsed, char* input){
    removeWhiteSpaces(input); // Stores Command without whitespaces in nText
    char* custom_commands[num_custom_commands];
    custom_commands[0]="echo";
    custom_commands[1]="ls";
    custom_commands[2]="cd";
    custom_commands[3]="history";
    custom_commands[4]="pwd";
    custom_commands[5]="pinfo";

    int i, command_id=0;
    for(i=0;i<num_custom_commands;i++){
        if(!strcmp(parsed[0], custom_commands[i])){
            command_id=i+1;
            break;
        }
    }
    // Check for input Output Redirection
    char inpfile[PATH_MAX], opfile[PATH_MAX];
    int l=0, inp=0, op=0, opc=0, inflag=0, outflag=0;
    while(nText[l]!='\0'){
        if(nText[l]=='>'){
            if(nText[l+1]=='>'){
                opc=1;
                op=l+3;
            }else{
                op=l+2;
            }
            nText[l]='\0';
            outflag+=1;
            if(opc)
                l+=1;
        }
        if(nText[l]=='<'){
            inp=l+2;
            nText[l]='\0';
            inflag+=1;
        }
        l++;
    }
    if(outflag <=1 && inflag <=1){
        if(inflag){
            strcpy(inpfile, &nText[inp]);
        }
        if(outflag){
            strcpy(opfile, &nText[op]);
        }
    }else{
        printf("More than one of input or output Redirection detected. Aborting...\n");
        return -1;
    }
    // if inflag or outflag are > 1  then multiple in and out Redirection which is not supported and hence will error.
    // Making sure redirection parts aare removed from 2d array
    l=0;
    while(parsed[l]!=NULL){
        if(parsed[l][0]=='<' || parsed[l][0]=='>' ){
            parsed[l]=NULL;
            break;
        }
        l++;
    }
    // Running Commands
    if(command_id)
        runOwnCommand(command_id, &nText[strlen(custom_commands[command_id-1]) + 1 ], parsed);
    else{
        int is_and=isAnd(input);
        if(is_and){
            int i=0, j=0;
            while(parsed[i]!=NULL)
                i+=1;
            j=strlen(parsed[i-1]);
            if(j<=1)
                parsed[i-1]=NULL;
            else{
                while(parsed[i-1][j]!='&') j--;
                if(parsed[i-1][j]=='&')
                    parsed[i-1][j]='\0';
            }
        }
        int f = fork();
        if (f>0){
            if(!is_and){
                int status;
                do{
                    waitpid(f, &status, WUNTRACED);
                }while(!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status));
            }else{
                tempProcess.id=f;
                tempProcess.inbg=0;
                strcpy(tempProcess.name, parsed[0]);
                numbgChilds+=1;
                createListNode(tempProcess);
            }
            return 0;
        }else if(f<0){
            printf("\nFork Failed\n");
        }else {
            if(is_and){
                setpgid(0, 0);
            }
            if(execvp(parsed[0], parsed)==-1){
                printf("\nbash: %s: command not found\n", parsed[0]);
                exit(1);
            }
            exit(0);
        }
    }
}

int runOwnCommand(int command_id, char* input, char** parsed){
    switch(command_id){
        case 1: echo(input); break;
        case 2: ls(parsed); break;
        case 3: cd(input); break;
        case 4: print_history(input); break;
        case 5: pwd(); break;
        case 6: pinfo(input); break;
        default: break;
    }
    return 0;
}
