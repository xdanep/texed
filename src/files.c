#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "function.h"
#include "var.h"
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

void filename(char*file)
{
    char dirl[7];
    int i;

    system("clear");
    printf("Open file\n");
    printf(">");
    setbuf(stdin,NULL);
    gets(file);

    for(i = 0; i < 6; i++)
        dirl[i] = file[i];

    if(strcmp(dirl, "/home/") == 0)
    {
        strcpy(dir, file);
        savefile();
    }
    else
        savedefault(file);
}

void savedefault(char*file)
{
    errno = 0;
    char *user;
    unsigned short int i;

    strcpy(dir, "/home/");

    i = strlen(getlogin());
    user = malloc(i);

    if(user == NULL)
    {
        printf("Cannot allocate dynamic memory");
        free(user);
        EXIT_FAILURE;
    }

    strcpy(user, getlogin());
    strcat(dir, user);

    strcat(dir, "/texed/");

    if (mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO) == -1) 
    {
        if(errno != EEXIST)
        {
            printf("Error: %s, enter to exit\n", strerror(errno), errno);
            getchar();
        }
    }

    char dirl[200];

    strcpy(dirl,dir);
    strcat(dirl, file);
    strcpy(dir, dirl);

    savefile();
    
    free(user);
}

void savefile()
{
    FILE*fPtr;

    if((fPtr = fopen(dir, "a+")) == NULL)
    {
        printf("Can not open the file\n");
    }
    else
    {
        system("clear");
        fclose(fPtr);
        startf();
    }
}
