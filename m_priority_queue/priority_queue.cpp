#include <iostream>
using namespace std;
#include <vector>
template<class T,class Container=vector<T>,class Compare=less<T> >
class Priority_queue
{
  public:
    Priority_queue()
      :c()
    {}
  
    template<class Iterator>
    Priority_queue(Iterator first,Iterator last)
      :c(first,last)
    {
      //将c中的元素调整成堆的结构
      int count=c.size();
      int root=((count-2)>>1);
      for(;root>=0;root--)
      {
        AdjustDown(root);
      }
    }
    
    void push(const T& data)
    {
      c.push_back(data);
      AdjustUP(c.size()-1);
    }

    void pop()
    {
      if(empty())
      {
        return ;
      }
      swap(c.front(),c.back());
      c.pop_back();
      AdjustDown(0);
    }

    size_t size()const
    {
      return c.size();
    }

    bool empty()const
    {
      return c.empty();
    }

    const T& top()const
    {
      return c.front();
    }

  private:
    void AdjustDown(int parent)
    {
      int child=parent*2+1;
      while(child<c.size())
      {
        // 找以parent为根的较大的孩子
        
        if(child+1 < c.size() && com(c[child],c[child+1]))
        {
          child+=1;
        }
        
        // 检测双亲是否满足情况

        if(com(c[parent],c[child]))
        {
          swap(c[child],c[parent]);
          parent=child;
          child=parent*2+1;
        }
        else
        {
          return;
        }
      }
    }
    
    void AdjustUP(int child)
    {
      int parent=((child-1)>>1);
      while(child)
      {
        if(com(c[parent],c[child]))
        {
          swap(c[child],c[parent]);
          child=parent;
          parent=((child-1)>>1);
        }
        else
        {
          return ;
        }
      }
    }

  private:
    Container c;
    Compare com; //堆中元素比较规则

};

#include <functional>

int main()
{
  // 8 1 9 3 6 4 5 0 2 7
  int array[]={8,1,9,3,6,4,5,0,2,7};
  Priority_queue<int> q(array,array+sizeof(array)/sizeof(array[0]));
  cout<<q.top()<<endl;
  q.pop();
  cout<<q.top()<<endl;

  Priority_queue<int,vector<int>,less<int> > q2;
  q2.push(5);
  q2.push(0);
  q2.push(9);
  q2.push(3);
  q2.push(4);

  return 0;
}
