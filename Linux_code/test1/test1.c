//命令行版本的进度条
#include <stdio.h>
#include <unistd.h>
int main()
{
  char buf[100]={0};
  const char* label="/-\\|";
  int i=0;
  int j=0;
  for(;i<20;i++)
  {
    buf[i]='#';
    if(i<6)
    { 
    printf("\033[0;31m%d%%\033[0;39m[%c][%s]\r",j,label[i%4],buf);
    }
    else if(i>=6&&i<12)
    {  
    printf("\033[0;33m%d%%\033[0;39m[%c][%s]\r",j,label[i%4],buf);
    }
    else
    {
    printf("\033[0;32m%d%%\033[0;39m[%c][%s]\r",j,label[i%4],buf);
    }
    fflush(stdout);
    j= j+5;
    //sleep(2);
    usleep(500*1000);
  }
  return 0;
}
