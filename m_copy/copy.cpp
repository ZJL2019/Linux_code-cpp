#include<iostream>
using namespace std;
#include <string.h>
#include <typeinfo>
#if 0
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

template<class T>
void Copy2(T* dst,T* src,size_t size)
{
  for(size_t i=0;i<size;i++)
  {
    dst[i]=src[i];
  }
}

bool IsPODType(const char* strType)
{
  //此处可以将所有的内置类型枚举出来
  const char* strTypes[]={"c","s","i","l","x","f","d"};
  for(auto e : strTypes)
 {
   if(strcmp(strType,e)==0)
   {
     return true;
   }
 }
 return false;
}

template<class T>
void Copy(T* dst,T* src,size_t size)
{
  //通过typeid可以将T的实际类型按照字符串的方式返回
  if(IsPODType(typeid(T).name()))
  {
    // T的类型：内置
    memcpy(dst,src,sizeof(T)*size);
  }
  else
  {
    for(size_t i=0;i<size;i++)
    {
      dst[i]=src[i];
    }
  }
}

void TestCopy()
{ 
  int array1[]={1,2,3,4,5,6,7,8,9,0};
  int array2[10];
  Copy(array2,array1,10);

  String s1[3]={"1111","2222","3333"};
  String s2[3];
  Copy(s2,s1,3);
}

int main()
{
  TestCopy();
  return 0;
}
#endif


class String
{
public:
  String(const char* str="")
  {
    if(nullptr==str)
    {
      str="";
    }
    _str=new char[strlen(str)+1];
    strcpy(_str,str);
  }

  String(const String& s)
    :_str(new char[strlen(s._str)+1])
  {
    strcpy(_str,s._str);
  }

  String& operator=(const String& s)
  {
    if(this!=&s)
    {
      char* str=new char [strlen(s._str)+1];
      strcpy(str,s._str);
      delete[] _str;
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


//确认T到底是否为内置类型？
//是
//不是

//对应内置类型
struct TrueType
{};

//对应自定义类型
struct FalseType
{};

template<class T>
struct TypeTraits
{
    typedef FalseType PODTYPE;
};

template<>
struct TypeTraits<char>
{
    typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<short>
{
  typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<int>
{
  typedef  TrueType PODTYPE;
};

template<class T>
void Copy(T* dst,T* src,size_t size,TrueType)
{
  memcpy(dst,src,sizeof(T)*size);
}

template<class T>
void Copy(T* dst,T* src,size_t size,FalseType)
{
  for(size_t i=0;i<size;i++)
  {
    dst[i]=src[i];
  }
}


template<class T>
void Copy(T* dst,T* src,size_t size)
{
  Copy(dst,src,size,typename TypeTraits<T>::PODTYPE());
}

void TestCopy()
{
  int array1[]={1,2,3,4,5,6,7,8,9,0};
  int array2[10];
  Copy(array2,array1,10);

  String s1[3]={"1111","2222","3333"};
  String s2[3];
  Copy(s2,s1,3);
}

int main()
{
  TestCopy();
  return 0;
}


