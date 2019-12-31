#pragma once
#include <stdio.h>
#include "blocking_queue.hpp"
class Task
{
public:
    virtual ~Task()
    {}
    virtual void Run()
    {
        printf("base Run\n");    
    }

};

//线程池对象启动的时候会创建一组线程
//每个线程都需要完成一定的任务(执行一定的代码逻辑，这个逻辑是由
//调用者来决定的)
//任务是一段代码，可以用函数来表示

class ThreadPool
{
public:
//n表示创建线程的数量
    ThreadPool(int n)
        :_queue(100)
         ,_worker_count(n)
    {
        //创建出若干个线程
       for(int i=0; i < _worker_count; ++i)
       {
           pthread_t tid;
           pthread_create(&tid,NULL,ThreadEntry,this);
           _workers.push_back(tid);
       }
    }

     ~ThreadPool()
    {
        //让线程退出，然后再回收
        for(size_t i = 0;i < _workers.size(); ++i)
        {
            pthread_cancel(_workers[i]);
        }
        for(size_t i = 0; i < _workers.size(); ++i)
        {
            pthread_join(_workers[i],NULL);
        }
    }

    //使用线程池的时候，就需要由调用者加入一些任务，让线程池执行
    
    void AddTask(Task* task)
    {
        _queue.Push(task);
    }

private:
    Blocking_Queue<Task*> _queue;
    int _worker_count;
    std::vector<pthread_t> _workers;
    static void* ThreadEntry(void *arg)
    {
        ThreadPool* pool=(ThreadPool*)arg;
        while(true)
        {
            //循环中尝试从阻塞队列中获取任务
            //获取到一个任务就只想一个任务
            Task *task = NULL;
            pool->_queue.Pop(&task);
            //task 表面上看是一个 Task* 类型，实际上指向的是 MyTask*
            //执行的是 子类 ，用户自定制的逻辑
            task->Run();
            delete task;
        }
    }
};



