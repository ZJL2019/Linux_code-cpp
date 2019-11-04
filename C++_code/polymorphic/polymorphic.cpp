#include <iostream>
using namespace std;

#include <string>


#if 0
//行为：买票
//对象：普通人

class Person
{
public:
  Person(const string& name,const string& gender,int age)
    :_name(name)
     ,_gender(gender)
     ,_age(age)
  {}

  //虚函数
  virtual void BuyTicket()
  {
    cout<<"全价票"<<endl;
  }

protected:
  string _name;
  string _gender;
  int _age;
};

class Student:public Person
{
  public:
    Student(const string& name,const string& gender,int age,int stuId)
      :Person(name,gender,age)
       ,_stuId(stuId)
    {}

    virtual void BuyTicket()
    {
      cout<<"半价票"<<endl;
    }

  protected:
    int _stuId;
};

class Soldier : public Person
{
  public:
    Soldier(const string& name,const string& gender,int age,const string& rank)
      :Person(name,gender,age)
       ,_rank(rank)
    {}
    void BuyTicket()
    {
      cout<<"免费"<<endl;
    }
  protected:
    string _rank;
};
//多态的实现
//虚函数必须通过基类的指针或者引用来调用
//基类虚函数必须使用virtual修饰，子类是否使用virtual修饰都可以。建议：子类中虚函数也使用virtual修饰，增加代码可读性
//多态的体现：代码编译时，不能确定到底调用哪个类的虚函数
//在代码运行时，根据p所指向的实际对象选择调用对应类的虚函数
//如果多态的实现条件没有完全满足：1、重写失败(基类函数不是虚函数，函数原型不一致)
//                                2、，没有通过基类的指针或者引用调用虚函数
void TestBuyTicket(Person& p)
{
  p.BuyTicket();
}


//void TestBuyTicket(Person& p)
//{
//    p.BuyTicket();
//
//}
//
//void TestBuyTicket(Student& p)
//{
//    p.BuyTicket();
//}
//
//void TestBuyTicket(Soldier& p)
//{
//    p.BuyTicket();
//}



int main()
{
  Person p("Jack","男",19);
  Student st("Tom","男",20,1000);
  Soldier so("Kate","女",26,"班长");

  TestBuyTicket(p);
  TestBuyTicket(st);
  TestBuyTicket(so);
  return 0;

}
#endif

#if 0
struct A{};
struct B:public A{};

class Base
{
  public:
    virtual void TestFun1()
    {
      cout<<"Base::TestFun1()"<<endl;
    }

    virtual void TestFun2(int)
    {
      cout<<"Base::TestFun2()"<<endl;
    }

    void TestFun3()
    {
      cout<<"Base::TestFun3()"<<endl;
    }

    virtual void TestFun4()
    {
      cout<<"Base::TestFun4()"<<endl;
    }

    virtual Base* TestFun5()
    {
      cout<<"Base:TestFun5()"<<endl;
      return this;
    }

    virtual A& TestFun6(A& a)
    {
      cout<<"Base::TestFun6()"<<endl;
      return a;
    }
};

class Derived:public Base
{
  public:
    virtual void TestFun1()
    {
      cout<<"Derived::TestFun1()"<<endl;
    }

    virtual void TestFun2()
    {
      cout<<"Derived::TestFun2()"<<endl;
    }

    virtual void TestFun3()
    {
      cout<<"Derived::TestFun3()"<<endl;
    }

    void TestFun4()
    {
      cout<<"Derived::TestFun4()"<<endl;
    }

    virtual Derived* TestFun5()
    {
      cout<<"Derived::TestFun5()"<<endl;
      return this;
    }
    
    virtual B& TestFun6(A& a)
    {
      cout<<"Derived::TestFun6()"<<endl;
      return *(new B);
    }

};

void TestVirtualFunc(Base* pb)
{
  pb->TestFun1();
  //子类和基类中的虚函数必须完全相同
  pb->TestFun2(10);
  //基类中的虚函数必须用virtual修饰
  pb->TestFun3();
  //子类中虚函数可以不被virtual修饰
  pb->TestFun4();
  //协变情况下，基类与子类的返回值可以不同
  //被返回的基类类型与子类类型必须是继承关系
  pb->TestFun5();
  
  A a;
  pb->TestFun6(a);
}

int main()
{
  Base b;
  Derived d;

  TestVirtualFunc(&b);
  TestVirtualFunc(&d);
  return 0;
}
#endif

class Base
{
  public:
    Base(int b)
      :_b(b)
    {
      cout<<"Base::Base()"<<endl;
    }
    virtual ~Base()
    {
      cout<<"Base::~Base()"<<endl;
    }
  int _b;
};

class Derived : public Base
{
  public:
    Derived(int b)
      :Base(b)
       ,_p(new int [10])
  {
    cout<<"Derived::Derived(int)"<<endl;
  }

    ~Derived()
    {
      delete [] _p;
      cout<<"Derived::~Derived()"<<endl;
    }

protected:
  int* _p;
};

void TestDestory()
{
  //基类和子类中析构函数名可以不同。
  Base* bp=new Derived(10);
  delete bp;
}

int main()
{
  TestDestory();
  return 0;
}

