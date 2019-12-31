#include "threadpool.hpp"


//这个类由用户自定制
//需要依赖哪些数据都可以随意添加和修改
class MyTask : public Task
{
public:
    MyTask(int id)
        :_id(id)
    {}

    void Run()
    {
        //执行用户自定制的逻辑
        printf("id = %d\n",_id);
    }
private:
    int _id;
};

int main()
{
    ThreadPool pool(10);
    for(int i=0; i < 20;++i)
    {
        pool.AddTask(new MyTask(i));
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}
