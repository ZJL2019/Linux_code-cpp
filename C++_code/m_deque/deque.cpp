#include <iostream>
using namespace std;
#include <deque>
  template<class T,class Container=deque<T> >
  class Stack
  {
    public:
      Stack()
      {

      }
      void push(const T& data)
      {
        _con.push_back(data);
      }

      void pop()
      {
        _con.pop_back();
      }

      size_t size()const
      {
        return _con.size();
      }

      bool empty()const
      {
        return _con.empty();
      }

      T& top()
      {
        return _con.back();
      }

      const T& top()const
      {
        return _con.back();
      }

  private:
      Container _con;
  };


template<class T,class Container=deque<T> >
class Queue
{
  public:
    Queue()
    {}

    void push(const T& data)
    {
      _con.push_back(data);
    }

    void pop()
    {
      _con.pop_front();
    }

    T& front()
    {
      return _con.front();
    }

    const T& front()const
    {
      return _con.front();
    }

    T& back()
    {
      return _con.back();
    }

    const T& back()const 
    {
      return _con.back();
    }

    size_t size()const 
    {
      return _con.size();
    }

    bool empty()const 
    {
      return _con.empty();
    }

  private:
    Container _con;

};




#include <vector>
void TestStack()
{
  Stack<int> s1;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.push(4);
  cout<<s1.size()<<endl;
  cout<<s1.top()<<endl;
  
  Stack<int,vector<int> > s2;
  s2.push(1);
  s2.push(2);
  s2.push(3);
  s2.push(4);
  cout<<s2.size()<<endl;
  cout<<s2.top()<<endl;
}

#include <list>

void Testqueue()
{
  Queue<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);
  q1.push(4);
  cout<<q1.size()<<endl;
  cout<<q1.front()<<endl;
  cout<<q1.back()<<endl;

  q1.pop();
  q1.pop();
  cout<<q1.size()<<endl;
  cout<<q1.front()<<endl;
  cout<<q1.back()<<endl;

  Queue<int,list<int> > q2;
  q2.push(1);
  q2.push(2);
  q2.push(3);
  q2.push(4);
  cout<<q2.size()<<endl;
  cout<<q2.front()<<endl;
  cout<<q2.back()<<endl;

  q2.pop();
  q2.pop();
  cout<<q2.size()<<endl;
  cout<<q2.front()<<endl;
  cout<<q2.back()<<endl;

}

int main()
{
 
  //TestStack();
  Testqueue();
  return 0;
}


