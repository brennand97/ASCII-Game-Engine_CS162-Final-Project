/**
 * Author:      Brennan Douglas
 * Date:        03/11/2017
 * Description: This is the header file for linux input functions
 */

#ifndef FINAL_PROJECT_LINUX_INPUT_HPP
#define FINAL_PROJECT_LINUX_INPUT_HPP

#include <termios.h>
#include <stdio.h>

static struct termios old, t_new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    t_new = old; /* make new settings same as old settings */
    t_new.c_lflag &= ~ICANON; /* disable buffered i/o */
    t_new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &t_new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}

#endif //FINAL_PROJECT_LINUX_INPUT_HPP
