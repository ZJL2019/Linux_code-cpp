#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int g_tickets=100;
#define THREADCOUNT 4

pthread_mutex_t g_mutex;

typedef struct ThreadPara
{
    int Threadld_;
}TP;


void* ThreadStart(void* arg)
{
    TP* tp=(TP*)arg;
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
        if(g_tickets > 0)
        {
            usleep(1000);
            printf("i am thread[%d],i am ticket is [%d]\n",tp->Threadld_,g_tickets);
            g_tickets--;
        }
        else
        {
            pthread_mutex_unlock(&g_mutex);
            delete tp;
            tp=NULL;
            break;
        }
        pthread_mutex_unlock(&g_mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid[THREADCOUNT];
    int i = 0;
    for(;i < THREADCOUNT;i++)
    {
        TP* tp = new TP;
        tp->Threadld_=i;
        pthread_create(&tid[i],NULL,ThreadStart,(void*)tp);
    }
    for(i = 0;i < THREADCOUNT;i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&g_mutex);
    return 0;
}
