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
    setbuf(stdin,NULL);
    gets(file);
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

    openfile(file);
    
    free(user);
}

void openfile()
{
    FILE*fPtr;

    if((fPtr = fopen(dir, "w")) == NULL)
    {
        printf("Can not open file.\n");
    }
    else
    {
        fprintf(fPtr, "prueba");
        system("clear");
    }
    fclose(fPtr);
}

/*
Caso 1: guardado por defecto
caso 2: guardado por direccion
variante 1: nuevo archivo
variante 2: archivo existente
*/