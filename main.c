#include "headers.h"
#include "prompt.h"
#include "input.h"
char homedir[PATH_MAX];

int main()
{
    // Getting the homedir
    if (getcwd(homedir, sizeof(homedir)) == NULL)
        exit(0);
    while (1)
    {
        prompt();
        input();
    }
}
