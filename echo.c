#include "echo.h"
#include "headers.h"

int removWhiteSpaces(char *text){
    int start=0, end=strlen(text);
    char nText[strlen(text)];
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
    printf("%s\n", nText);    
}
 

int echo(char* text){
    removWhiteSpaces(text);
}
