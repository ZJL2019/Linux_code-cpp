//#include <unistd.h>
//#include <stdio.h>
//#include <pthread.h>
//#include <semaphore.h>
//使用队列来表示生产者消费者模型
//同步互斥不一定非得用互斥锁和条件变量来实现
//使用信号量来完成
//信号量就是一个计数器，表示可用资源的个数
//P 申请资源，计数器 -1
//V 释放资源，计数器 +1
//当计数器值为0的时候，再去P操作就会发生阻塞

//初始化

//sem_t sem;

//阻塞队列:一种常见的数据结构，线程安全版本的队列

//class Blocking_Queue
//{
//    
//};

//int main()
//{
    //第二个参数填为0表示这个信号量只能在当前进程内使用
    //第三个参数表示信号量这个计数器的初始值
    //sem_init(&sem,0,2);
    
    //P
    //sem_wait(&sem);
    //printf("P操作一次\n");
    //sem_wait(&sem);
    //printf("P操作一次\n");
    
    //V
    //sem_post(&sem);

    //sem_destroy(&sem);
    //return 0;
//}


#include "blocking_queue.hpp"

Blocking_Queue<int> queue(100);

void* Product(void *arg)
{
    (void) arg;
    int count=0;
    while(1)
    {
        queue.Push(++count);
        usleep(789789);
    }
    return NULL;
}

void* Consume(void *arg)
{
    (void) arg;
    while(1)
    {
        int count=0;
        queue.Pop(&count);
        printf("count = %d\n",count);
        usleep(123123);
    }
    return NULL;
}

int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,Product,NULL);
    pthread_create(&tid2,NULL,Consume,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}








