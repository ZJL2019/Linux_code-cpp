#pragma once
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

//一般 Blocking_Queue都要求长度是有上限的
//如果队列为空，去执行Pop就会阻塞
//如果队列满了，去执行Push也会阻塞
//信号量表示互斥比较简单，但是表示同步较为复杂

// 信号量表示可用资源的个数
// 一个信号量表示当前队列中元素的个数
// 另一个信号量表示当前队列中空格的个数
// 插入元素就是在消耗一个空格资源，释放了一个元素资源
// 删除元素就是在消耗一个元素资源，释放了一个空格资源

//如果用信号量表示互斥，P操作和V操作在同一个函数中
//如果用信号量表示同步，P操作和V操作在不同的函数中

//信号量这个计数器的 +1 -1 是原子的

template <class T>
class Blocking_Queue
{
public:
    Blocking_Queue(int max_size) 
         :_max_size(max_size)
         ,_head(0)
         ,_tail(0)
         ,_size(0)
         ,_queue(max_size) 
    {
       sem_init(&_lock,0,1);
       sem_init(&_elem,0,0);
       sem_init(&_blank,0,max_size);
    }

    ~Blocking_Queue()
    {
        sem_destroy(&_lock);
        sem_destroy(&_elem);
        sem_destroy(&_blank);
    }

    void Push(const T& data)
    {
        //每次插入元素，就得先申请一个空格资源
        //如果没有空格资源(信号量为0)，说明队列满了
        //满了就不能继续插入，并且在Push中阻塞
        sem_wait(&_blank);

        sem_wait(&_lock);
        _queue[_tail]=data;
        ++_tail;
        ++_size;
        sem_post(&_lock);

        sem_post(&_elem);
    }

    //data表示出队列的这个元素
    void Pop(T* data)
    {
        //每次出队列的时候，就先申请一个元素资源
        //如果没有元素资源，队列为空
        //就不能直接出队列，而需要在Pop的位置阻塞
        sem_wait(&_elem);

        sem_wait(&_lock);
        *data=_queue[_head];
        ++_head;
        --_size;
        sem_post(&_lock);

        sem_post(&_blank);
    }

private:
    std::vector<T> _queue;
    int _head;
    int _tail;
    int _size;
    int _max_size;
    sem_t _lock;// 可以用一个二元信号量(非0即1)表示互斥锁
    sem_t _elem;// 可用元素的个数
    sem_t _blank;//可用空格的个数
};
