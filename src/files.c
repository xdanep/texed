#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "function.h"
#include "var.h"
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <ncurses.h>

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
        start(fPtr);
    }
    fclose(fPtr);
}

void start(FILE*fPtr)
{
    initscr();
    int x = 0, y = 0;
    int key;
    int key2;

    if(has_colors())
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));//activa pareja 1
    keypad(stdscr, 1); //activa teclas especiales
    cbreak(); //pulsacion instantanea
    refresh();

    while(1)
    {   
        echo();
        key2 = getch();
        refresh();

        if(key == KEY_UP)//up
        {
            y--;
            move(y, x);
            refresh();
        }
        if(key == KEY_DOWN)//down
        {
            y++;
            move(y, x);
            refresh();
        }
        if(key == KEY_LEFT)//left
        {
            x--;
            move(y, x);
            refresh();
        }
        if(key == KEY_RIGHT)//right
        {
            x++;
            move(y, x);
            refresh();
        }
        if(key == 27)
        {
            break;
        }
        if(key == 13)
        {
            y--;
            x = 0;
            move(y, x);
            fprintf(fPtr, "\r");
            refresh();
        }
        if(key == 8)
        {
            x--;
            move(y, x);
            refresh();
        }
    }
    clear();
    endwin();

    return;
}