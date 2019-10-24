#include <iostream>
using namespace std;

#include <assert.h>
namespace My
{
  template<class T,size_t N>
  class array
  {
  public:
    void push_back(const T& data)
    {
      _array[_size++]=data;
    }

    T& operator[](size_t index)
    {
      assert(index<_size);
      return _array[index];
    }
    
    bool empty()const 
    {
      return 0 ==_size;
    }
      
    size_t size()const 
    {
      return _size;
    }

  private:
    T _array[N];
    size_t _size;
  };
}

int main()
{
  int a=10;
  int b=20;
  //非类型模板参数必须在编译时确认其结果
  My::array<int,10+20> arr;
  arr.push_back(1);
  arr.push_back(2);
  arr.push_back(3);
  arr.push_back(4);
  return 0;
}

