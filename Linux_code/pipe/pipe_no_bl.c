#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd[2];
    int ret= pipe(fd);
    if(ret!=0)
    {
        perror("pipe");
    }
    int flags=fcntl(fd[0],F_GETFL);
    flags|=O_NONBLOCK;
    fcntl(fd[0],F_SETFL,flags);

    char buf[1024]={0};
    int ret_size =read(fd[0],buf,sizeof(buf)-1);
    printf("%d\n",ret_size);

    return 0;
}
