/* signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int alarm_flag = 0;

void handler(int signum)
{
    printf("Hello World!\n");
    alarm_flag = 1;
    alarm(5);
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, handler);
    alarm(5);

    while (1)
    {
        if (alarm_flag)
        {
            printf("Turing was right!\n");
            alarm_flag = 0;  // Reset the flag
        }
    }
    return 0;
}