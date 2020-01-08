#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>
//C++ 中自带的std::thread
//C++ 11 把线程直接纳入到标准库中
//std::thread 类
// 互斥锁 ，条件变量
// 信号量(目前还没有)
// 读写锁(目前也没有)

// 原子操作
// 曾经 ++ 普通变量，步骤分成3个部分
// 现在的 原子操作， 把这三个步骤和并成一个
// 原子操作本质上也是锁，只不过是 CPU指令级别的锁
// 这样的锁本质上是 自旋锁
std::mutex lock;
std::atomic_int count(0);
void Handler() 
{
    for(int i = 0;i < 50000; i++ )
    {
        ++count;
    }
}

int main()
{
    // std::thread 构造函数用到的语法 变长参数模板
    std::thread t1(Handler);
    std::thread t2(Handler);
    t1.join();
    t2.join();
    printf("count = %d\n",(int)count);
    return 0;
}
