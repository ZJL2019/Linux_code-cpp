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
    write(fd[1],"hello",5);

    char buf[1024]={0};
    read(fd[0],buf,sizeof(buf));
    printf("buf=%s\n",buf);
    return 0;
}
