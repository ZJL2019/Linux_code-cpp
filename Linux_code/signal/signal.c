#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int g_val=0;

void sigcallback(int sig)
{
    g_val++;
    printf("sig:%d\n",sig);
}

void sigcallback1(int sig)
{
    printf("sig:%d\n",sig);
}

int main()
{
    signal(2,sigcallback1);
    
    int count=100;
    while(count--)
    {
        g_val++;
        usleep(100000);
    }
    printf("g_val:%d\n",g_val);
    return 0;
}
