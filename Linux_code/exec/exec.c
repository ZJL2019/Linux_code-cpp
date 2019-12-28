#include <stdio.h>
#include <unistd.h>

int main()
{
    //程序替换
    //1、execl
    
    //execl("/usr/bin/ls","ls","-l",NULL);
    
    execlp("getargv","getargv","-a","-b",NULL);
    
    printf("ok\n");
    return 0;
}
