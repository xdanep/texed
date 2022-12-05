#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void crear_dir(char*archivo)
{
    printf("Introduzca el archivo a abrir: ");
    setbuf(stdin,NULL);
    gets(archivo);
}

void actualizar_fichero(char*archivo, int i)
{
    char cadena1[301];
    FILE*p;

    if((p = fopen(archivo, "a")) == NULL)
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

void llenar_fichero(char*archivo)
{
    char cadena1[301];
    unsigned short int i = 2;
    FILE*p;

    if((p = fopen(archivo, "w")) == NULL)
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

int leer_fichero(char*archivo, int i)
{
    char cadena1[301];

    FILE*p;

    if((p = fopen(archivo, "r")) == NULL)
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

void prueba(char*archivo)
{
    char cadena[2], cadena1[301];
    FILE*fPtr;
    int i = 1;

    if((fPtr = fopen(archivo, "r")) == NULL)
    {
        system("clear");
        llenar_fichero(archivo);
    }
    else
    {
        system("clear");
        setbuf(stdin,NULL);
        fgets(cadena, 2, fPtr);
        if(cadena[0] == '\0')
        {
            fclose(fPtr);
            llenar_fichero(archivo);
        }
        else
        {
            fclose(fPtr);
            i = leer_fichero(archivo, i);
            actualizar_fichero(archivo, i);
        }
    }
}