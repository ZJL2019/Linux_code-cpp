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

int main()
{
 
TestStack();
  return 0;
}


