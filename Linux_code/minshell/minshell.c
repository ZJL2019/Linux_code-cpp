#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
char g_Command[1024];

int GetCommand()
{
    memset(g_Command,'0',sizeof(g_Command));
    printf("[minshell@localhost]$ ");
    fflush(stdout);
     if(!fgets(g_Command,sizeof(g_Command)-1,stdin))
    {
        perror("fgets");
        return -1;
    }
    //gets(g_Command);
    return 0;
}

int ExecCommand(char* argv[])
{
    if(!argv[0])
    {
        return -1;
    }

    int pid=fork();
    if(pid<0)
    {
        perror("fork");
        return -1;
    }
    
    else if(pid==0)
    {
        //child
        execvp(argv[0],argv);
        perror("execvp");
        exit(0);
    }

    else
    {
        //father
        waitpid(pid,NULL,0);
    }
    return 0;
}

int DealCommand(char* command)
{
    if(!command||*command=='\0')
    {
        printf("DealCommand failed\n");
        return -1;
    }

    char* argv[32]={0};
    int argc=0;
    while(*command)
    {
        if(!isspace(*command))
        {
            argv[argc]=command;
            argc++;
            while(!isspace(*command)&&*command!='\0')
            {
                command++;
            }
            *command='\0';
        }
        command++;
    }
    
    //char *p=strtok(command," ");

    //while(p!=NULL)
    //{
    //    argv[argc]=p;
    //    ++argc;
    //    p=strtok(NULL," ");
    //}
    argv[argc]=NULL;
    //for(int i=0;i<argc;i++)
    //{
    //    printf("[%d]:[%s]\n",i,argv[i]);
    //}
    ExecCommand(argv);
    return 0;
}

int main()
{
    while(1)
    {
        if(GetCommand()!=0)
        {
            continue;
        }
        //切割命令
        DealCommand(g_Command);  
    }
    return 0;
}
