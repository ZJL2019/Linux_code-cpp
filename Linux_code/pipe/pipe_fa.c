#include <stdio.h>
#include <unistd.h>
int main()
{
    int fd[2];
    int ret= pipe(fd);
    if(ret!=0)
    {
        perror("pipe");
    }
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
    }
    //只读不写
    
    //else if(pid==0)
    //{
    //    //child
    //    sleep(50);
    //    write(fd[1],"hello",5);
    //}
    
    //只写不读

    else if(pid==0)
    {
        //child
        write(fd[1],"hello",5);
    }
    else
    {
        //father
        sleep(50);
        char buf[1024]={0};
        read(fd[0],buf,sizeof(buf));
        printf("buf=%s\n",buf);
    }

    return 0;
}
