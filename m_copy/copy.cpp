#include<iostream>
using namespace std;
#include <string.h>
class String
{
  public:
    String (const char* str="")
    {
      if(nullptr==str)
      {
        str="";
      }
      _str=new char[strlen(str)+1];
      strcpy(_str,str);
    }
    
    String(const String& s)
        :_str(new char [strlen(s._str)+1])
    {
      strcpy(_str,s._str);
    }

    String& operator=(const String& s)
    {
      if(this!=&s)
      {
        char* str=new char[strlen(s._str)+1];
        strcpy(str,s._str);
        delete [] _str;
        _str=str;
      }
      return *this;
    }

    ~String()
    {
      delete [] _str;
    }

  private:
    char* _str;
};


//写一个通用的拷贝函数，要求：效率尽可能高
//对于内置类型----->O(1)
//缺陷：浅拷贝

template<class T>
void Copy1(T* dst,T* src,size_t size)
{
  memcpy(dst,src,sizeof(T)*size);
}

//优点：一定不会出错
//缺陷：O(N)

template<class>
void Copy2(T* dst,T* src,size_t size)
{
  for(size_t i=0;i<size;i++)
  {
    dst[i]=src[i];
  }
}



