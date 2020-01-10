#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
class Mythread
{
    public:
        Mythread()
        {
            a=78;
            sprintf(arr,"%s","nihao");
        }
        void print()
        {
            printf("%d-%s\n",a,arr);
        }

        static void* thread_start(void* arg)
        {
            Mythread* mythread=(Mythread*)arg;
            while(1)
            {
                sleep(1);
                mythread->print();
                printf("i am thread_start\n");
            }
            return NULL;
        }
        void CreatThread()
        {
            pthread_t tid;
            pthread_create(&tid,NULL,thread_start,this);
        }
    private:
        int a;
        char arr[1024];
};

void* thread_start2(void* arg)
{
    Mythread* mythread=(Mythread*)arg;
    while(1)
    {
        sleep(1);
        mythread->print();
        pthread_attr_t attr;
        size_t stacksize;
        pthread_attr_getstacksize(&attr,&stacksize);
    printf("%d\n",stacksize);
    }
    return NULL;
}

int main()
{

    Mythread* mt=new Mythread();
    mt->CreatThread();
    pthread_t tid;
    pthread_create(&tid,NULL,thread_start2,mt);
    printf("%p\n",tid);

    while(1)
    {
        sleep(1);
        printf("i am main thread\n");
    }

    delete mt;
    return 0;
}
