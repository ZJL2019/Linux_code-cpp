#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int sig)
{
    printf("sig:%d\n",sig);
}


int main()
{
    signal(2,sigcallback);
    signal(40,sigcallback);
    sigset_t set,oldset;
    sigemptyset(&set);
    sigemptyset(&oldset);

    sigfillset(&set);

    sigprocmask(SIG_BLOCK,&set,&oldset);
    getchar();
    sigprocmask(SIG_UNBLOCK,&set,NULL);
    while(1)
    {
        ;
    }

    return 0;
}
