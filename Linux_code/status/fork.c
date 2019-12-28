#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
int main()
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        return 0;
    }

    else if(pid==0)
    {
        //子进程
        printf("child process!\n");
        sleep(3);
        exit(88);
    }

    else
    {
        //父进程
        int status;
        wait(&status);
        printf("%d\n",(status)>>8&0xff);
        sleep(100);
        while(1)
        {
            printf("father process!\n");
        }
    }

    return 0;
}
