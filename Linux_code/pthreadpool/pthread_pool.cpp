#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

#define THREADCOUNT 4

typedef void (*Handler_t)(int);

class ThreadTask
{
    public:
        ThreadTask()
        {
            Data_ = -1;
            Handler_ = NULL;
        }

        ThreadTask(int Data,Handler_t Handler)
        {
            Data_ = Data;
            Handler_ = Handler;
        }

        void Run()
        {
            Handler_(Data_);
        }

    private:
        int Data_;
        Handler_t Handler_;
};

class ThreadPool
{
    public:
        ThreadPool()
        {
            ThreadCapacity_=THREADCOUNT;
            ThreadCurNum_=THREADCOUNT;
            pthread_mutex_init(&Mutex_,NULL);
            pthread_cond_init(&Cond_,NULL);
            IsQuit_=false;

            bool IsCreate=ThreadCreate();
            if(!IsCreate)
            {
                printf("ThreadPool Create thread failed\n");
                exit(1);
            }
        }

        ~ThreadPool()
        {
            pthread_mutex_destroy(&Mutex_);
            pthread_cond_destroy(&Cond_);
        }

        bool Push(ThreadTask* Tt)
        {
            pthread_mutex_lock(&Mutex_);
            if(IsQuit_)
            {
                pthread_mutex_unlock(&Mutex_);
                return false;
            }
            Que_.push(Tt);
            pthread_mutex_unlock(&Mutex_);
            pthread_cond_signal(&Cond_);
            return true;
        }

        bool Pop(ThreadTask** Tt)
        {
            *Tt=Que_.front();
            Que_.pop();
            return true;
        }

        bool PoolClear()
        {
            pthread_mutex_lock(&Mutex_);
            IsQuit_=true;
            pthread_mutex_unlock(&Mutex_);
            if(ThreadCurNum_ > 0)
            {
                pthread_cond_broadcast(&Cond_);
            }
            return true;
        }

    private:
        static void* ThreadStart(void* arg)
        {
            ThreadPool* tp = (ThreadPool*)arg;
            while(1)
            {
                pthread_mutex_lock(&tp->Mutex_);
                while(tp->Que_.empty())
                {
                    if(tp->IsQuit_)
                    {
                        tp->ThreadQuit();
                    }
                    pthread_cond_wait(&tp->Cond_,&tp->Mutex_);
                }
                ThreadTask* tt;
                tp->Pop(&tt);
                pthread_mutex_unlock(&tp->Mutex_);
                tt->Run();
                delete tt;
            }
            return NULL;
        }

        void ThreadQuit()
        {
            ThreadCurNum_--;
            pthread_mutex_unlock(&Mutex_);
            pthread_exit(NULL);
        }

    private:
        bool ThreadCreate()
        {
            int ret=-1;
            pthread_t tid;
            for(int i=0;i < THREADCOUNT;i++)
            {
                ret=pthread_create(&tid,NULL,ThreadStart,(void*)this);
                if(ret!=0)
                {
                    printf("Create thread failed\n");
                    return false;
                }
            }
            return true;
        }

    private:
        size_t ThreadCapacity_;
        size_t ThreadCurNum_;
        std::queue<ThreadTask*> Que_;
        pthread_mutex_t Mutex_;
        pthread_cond_t Cond_;
        bool IsQuit_;
};

void Printf(int Data)
{
    printf("I Am Handler Func, I Print [%d]\n",Data);
}


int main()
{
    ThreadPool* tp=new ThreadPool();
    for(int i=0;i < 10;i++)
    {
        ThreadTask* tt = new ThreadTask(i,Printf);
        tp->Push(tt);
    }
    sleep(10);
    tp->PoolClear();
    delete tp;
    return 0;
}
