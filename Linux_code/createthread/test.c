#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_start(void* arg)
{
    (void) arg;
    while(1)
    {
        sleep(1);
        printf("i am thread_start:%s\n",(char*)arg);
    }
    sleep(30);
    return NULL;
}

int main()
{
    //creatr thread
    pthread_t tid;
    char arr[1024]={0};
    sprintf(arr,"%s","nihao!");
    pthread_create(&tid,NULL,thread_start,(void*)arr);
    while(1)
    {
        sleep(1);
        printf("i am main thread\n");
    }
    return 0;
}
