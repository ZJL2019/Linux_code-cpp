#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    int fd[2];
    int ret=pipe(fd);
    if(ret<0)
    {
        perror("pipe");
    }
    //fork子进程
    
    pid_t pid1=fork();
    if(pid1<0)
    {
        perror("fork");
    }
    else if(pid1==0)
    {
        //子进程1  ps aux
        dup2(fd[1],1);
        execl("/usr/bin/ps","ps","aux",NULL);
        exit(0);
    }
    
    pid_t pid2=fork();
    if(pid2<0)
    {
        perror("fork");
    }
    else if(pid2==0)
    {
        //子进程2 grep
        dup2(fd[0],0);
        close(fd[1]);
        execl("/usr/bin/grep","grep","sshd",NULL);
        exit(0);
    }

    //父进程
    close(fd[0]);//读端不使用
    close(fd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);

    return 0;
}
