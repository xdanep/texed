#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "var.h"

void startf()
{
    char string[2], string1[301];
    FILE*fPtr;
    int i = 1;

    if((fPtr = fopen(dir, "r")) == NULL)
    {
        system("clear");
        writef(dir);
    }
    else
    {
        system("clear");
        setbuf(stdin,NULL);
        fgets(string, 2, fPtr);
        if(string[0] == '\0')
        {
            fclose(fPtr);
            writef(dir);
        }
        else
        {
            fclose(fPtr);
            i = readf(dir, i);
            editf(dir, i);
        }
    }
}

void writef(char*dir)
{
    char string1[301];
    unsigned short int i = 2;
    FILE*p;

    if((p = fopen(dir, "w")) == NULL)
        printf("File couln't be opened\n");

    else
    {
        printf("Enter q! to end input:\n\n");
        setbuf(stdin,NULL);
        printf("1  ");
        gets(string1);

        while(string1[0] != 'q' || string1[1] != '!')
        {
            fputs(string1, p);
            fputs("\n", p);
            printf("%hu  ", i);
            i++;
            setbuf(stdin,NULL);
            gets(string1);
        }
        fclose(p);
    }
}

void editf(char*dir, int i)
{
    char string1[301];
    FILE*p;

    if((p = fopen(dir, "a")) == NULL)
        printf("File couln't be opened\n");

    else
    {
        printf("Enter q! to end input:\n");
        printf("%d  ", i);
        setbuf(stdin,NULL);
        gets(string1);

        while(string1[0] != 'q' || string1[1] != '!')
        {
            fputs(string1, p);
            fputs("\n", p);
            i++;
            printf("%d  ", i);
            setbuf(stdin,NULL);
            gets(string1);
        }
        fclose(p);
    }
}

int readf(char*dir, int i)
{
    char string1[301];

    FILE*p;

    if((p = fopen(dir, "r")) == NULL)
        printf("Can't open file\n");

    else
    {
        while(!feof(p))
        {
            fgets(string1, 301, p);
            printf("%d  %s", i, string1);
            i++;
        }
        fclose(p);
    }
    return i;
}