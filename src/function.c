#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "function.h"

void actualizar_fichero(char*file, int i)
{
    char cadena1[301];
    FILE*p;

    if((p = fopen(file, "a")) == NULL)
        printf("File couln't be opened\n");

    else
    {
        printf("Enter q! to end input:\n");
        printf("%d  ", i);
        setbuf(stdin,NULL);
        gets(cadena1);

        while(cadena1[0] != 'q' || cadena1[1] != '!')
        {
            fputs(cadena1, p);
            fputs("\n", p);
            i++;
            printf("%d  ", i);
            setbuf(stdin,NULL);
            gets(cadena1);
        }
        fclose(p);
    }
}

void llenar_fichero(char*file)
{
    char cadena1[301];
    unsigned short int i = 2;
    FILE*p;

    if((p = fopen(file, "w")) == NULL)
        printf("File couln't be opened\n");

    else
    {
        printf("Enter q! to end input:\n");
        setbuf(stdin,NULL);
        printf("1  ");
        gets(cadena1);

        while(cadena1[0] != 'q' || cadena1[1] != '!')
        {
            fputs(cadena1, p);
            fputs("\n", p);
            printf("%hu  ", i);
            i++;
            setbuf(stdin,NULL);
            gets(cadena1);
        }
        fclose(p);
    }
}

int leer_fichero(char*file, int i)
{
    char cadena1[301];

    FILE*p;

    if((p = fopen(file, "r")) == NULL)
        printf("Can't open file\n");

    else
    {
        while(!feof(p))
        {
            fgets(cadena1, 301, p);
            printf("%d  %s", i, cadena1);
            i++;
            
        }
        fclose(p);
    }
    return i;
}

