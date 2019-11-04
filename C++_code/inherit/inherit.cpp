#include <iostream>
using namespace std;

#if 0
//基类
  public:
    void SetBase(int pri,int pro,int pub)
    {
      _pri=pri;
      _pro=pro;
      _pub=pub;
    }

    void PrintBase()
    {
      cout<<_pri<<endl;
      cout<<_pro<<endl;
      cout<<_pub<<endl;
    }

  private:
    int _pri;
  protected:
    int _pro;
  public:
    int _pub;

};
//派生类
class Derived:public Base
{};

int main()
{
  //可以验证：派生类将基类中的成员变量继承到子类中
  cout<<sizeof(Derived)<<endl;

  //验证：基类中的成员函数被子类继承
  Derived d;
  d.SetBase(10,20,30);
  d.PrintBase();
  return 0;
}
#endif


#if 0
//基类
class Base
{
  public:
    void SetBase(int pri,int pro,int pub)
    {
      _pri=pri;
      _pro=pro;
      _pub=pub;
    }

    void PrintBase()
    {
      cout<<_pri<<endl;
      cout<<_pro<<endl;
      cout<<_pub<<endl;
    }

  private:
    int _pri;
  protected:
    int _pro;
  public:
    int _pub;

};

//继承权限：----public
//基类中public/protected的成员在子类中权限不变
//基类中private的成员在子类中不可见(不能使用--该成员变量确实被继承至子类中)
class Derived:public Base
{
  public:
    void SetDerived(int priD,int proD,int pubD)
    {
      _priD=priD;
      _proD=proD;
      _pubD=pubD;

      _pro=10;
      //_pri=20;
      //'_pri' is a private member of 'Base'
      //编译报错：在派生类中不能访问基类中的私有成员
      //访问权限：限定该成员变量是否可以直接在类外进行访问
    }
  public:
    int _pubD;
  protected:
    int _proD;
  private:
    int _priD;

};

class D : public Derived
{
  public:
      void Test()
      {
        _pro = 10;       
      }
};

int main()
{
  Derived d;
  cout<<sizeof(d)<<endl;
  d._pub=10;
 // d._pro=10;
 // '_pro' is a protected  member of 'Base'
 // 受保护权限的变量在public继承权限下，无法在类外访问，只能在类内访问
  return 0;
}
#endif

#if 0
//基类
class Base
{
  public:
    void SetBase(int pri,int pro,int pub)
    {
      _pri=pri;
      _pro=pro;
      _pub=pub;
    }

    void PrintBase()
    {
      cout<<_pri<<endl;
      cout<<_pro<<endl;
      cout<<_pub<<endl;
    }

  private:
    int _pri;
  protected:
    int _pro;
  public:
    int _pub;

};

//继承方式---protected
//基类中public的成员在子类中访问权限已经变成protected
//基类中protected的成员在子类中访问权限不变
//基类中private的成员在子类中不可见(不能使用--该成员变量确实被继承至子类中)
class Derived:protected Base
{
  public:
    void SetDerived(int priD,int proD,int pubD)
    {
      _priD=priD;
      _proD=proD;
      _pubD=pubD;

      _pro=10;
      
      //_pri=20;
      //'_pri' is a private member of 'Base'
      //编译报错：在派生类中能访问基类的私有成员
      //访问权限：访问权限：限定该成员变量是否可以直接在类外进行调用
    }
  public:
    int _pubD;
  protected:
    int _proD;
  private:
    int _priD;
};

class D : public Derived
{
  public:
    void Test()
    {
      _pub=10;
      _pro=20;
    }
};

int main()
{
  Derived d;
 //d._pub=10;
 //'Derived' to its protected base class 'Base'
 //'_pub' is a protected member of 'Base'
  return 0;
}
#endif

#if 0
//基类
class Base
{
  public:
    void SetBase(int pri,int pro,int pub)
    {
      _pri=pri;
      _pro=pro;
      _pub=pub;
    }

    void PrintBase()
    {
      cout<<_pri<<endl;
      cout<<_pro<<endl;
      cout<<_pub<<endl;
    }

  private:
    int _pri;
  protected:
    int _pro;
  public:
    int _pub;

};
//继承方式---private
//基类中public的成员在子类中访问权限已经变成private
//基类中protected的成员在子类中访问权限已经变成private
//基类中private的成员在子类中不可见(不能使用--该成员变量确实被继承至子类中)

class Derived:private Base
{
  public:
    void SetDerived(int priD,int proD,int pubD)
    {
      _priD=priD;
      _proD=proD;
      _pubD=pubD;

      _pro=10;
      
      //_pri=20;
      //'_pri' is a private member of 'Base'
      //编译报错：在派生类中能访问基类的私有成员
      //访问权限：访问权限：限定该成员变量是否可以直接在类外进行调用
    }
  public:
    int _pubD;
  protected:
    int _proD;
  private:
    int _priD;
};

class D : public Derived
{
  public:
    void Test()
    {
      //'D' to its private base class 'Base'
      //_pub=10;
      //'_pub' is a private member of 'Base'
      //_pro=20;
      //'_pro' is a private member of 'Base'
    }
};

int main()
{
  Derived d;
  //'Derived' to its private base class 'Base'
  //d._pub=10;
  //'_pub' is a private member of 'Base'
  return 0; 
}
#endif


#if 0
//基类
class Base
{
  public:
    void SetBase(int pri,int pro,int pub)
    {
      _pri=pri;
      _pro=pro;
      _pub=pub;
    }

    void PrintBase()
    {
      cout<<_pri<<endl;
      cout<<_pro<<endl;
      cout<<_pub<<endl;
    }

  private:
    int _pri;
  protected:
    int _pro;
  public:
    int _pub;

};

//class 和 struct的默认继承权限
//class 默认继承权限---private
//struct 默认继承权限---public
struct Derived: Base
{
  public:
    void SetDerived(int priD,int proD,int pubD)
    {
      _priD=priD;
      _proD=proD;
      _pubD=pubD;

      _pro=10;
      //_pri=20;
      //'_pri' is a private member of 'Base'
      
    }
  public:
    int _pubD;
  protected:
    int _proD;
  private:
    int _priD;
};


class D:public Derived
{
  public:
    void Test()
    {
      _pub=10;
    }
};


int main()
{
  D d;
  d._pub=10;
  return 0;
}
#endif


#if 0
class B
{
public:
  void SetB(int b)
  {
    _b=b;
  }
protected:
  int _b;
};

class D:public B
{
public:
  void SetD(int b,int d)
  {
    _b=b;
    _d=d;
  }
//protected:
  int _d;
};

//赋值兼容规则：前提----->public
//如果是public继承方式：派生类与基类对象之间是--is-a的关系
//is-a:是一个，可以将一个子类对象看成是一个基类对象//所有用到基类对象的位置都可以使用子类对象进行代替


int main()
{
  B b;
  b.SetB(10);

  D d;
  //d.SetB(10);
  d.SetD(20,30);

  //可以用子类对象来给基类对象赋值
  b=d; 
  //基类对象不能给子类对象赋值
  //d=b;
  
  //一个基类指针可以指向子类对象
  B* pb=&d;

  //一个子类的指针不能直接指向一个基类的对象
  //D* pd=&b;
  
  //子类指针指向基类对象，需要对对象使用强转
  D* pd=(D*)&b;

  pd->_d=10;
  
  B& rb=d;
  //D& rd=b;
  
  return 0;
}
#endif

#if 0
class B
{
  public:
    void SetB(int b)
    {
      _b=b;
    }

    void Test(int a=10)
    {}
  //protected:
    char _b;
};

//同名隐藏：基类和派生类中具有相同名称的成员(成员变量||成员函数)
//如果通过派生类对象直接访问同名成员，优先访问到的是派生类自己的，基类的同名成员不能直接访问到(派生类将基类中的同名成员隐藏)

//成员变量：与变量类型是否相同无关
//成员函数：与成员函数原型是否相同无关

class D :public B
{
  public:
    void SetD(int b,int d)
    {
      _b=b;
    }
    void Test()
    {}
  //protected:
    int _b;
};

int main()
{
  cout<<sizeof(D)<<endl;
  D d;
  d._b='1';
  cout<<sizeof(d._b)<<endl;
  d.B::_b='2';
  cout<<sizeof(d.B::_b)<<endl;

  d.Test();
  d.B::Test();

  d.SetD(1,2);
  return 0;
}
#endif

#if 0
//如果基类的构造函数是无参或者全缺省参数的构造函数
//在派生类构造函数初始化列表的位置调用或不调用都可以
//如果用户没有调用，则编译器会默认调用

class B
{
  public:
    B()
    {
      cout<<"B()"<<endl;
    }
  protected:
    int _b;
};

class D: public B
{
  public:
    D()
    {
      cout<<"D()"<<endl;
    }
  protected:
    int _d;
};

int main()
{
  D d;
  return 0;
}
#endif

#if 0
class B
{
  public:
    B(int b)
    {
      cout<<"B()"<<endl;
    }
  protected:
    int _b;
};

//如果基类的构造函数是带有参数的构造函数，用户必须在派生类构造函数初始化列表的位置显示调用，以完成基类部分成员的初始化工作

class D:public B
{
  public:
    D()
      :B(1)
       ,_d(2)
  {
   cout<<"D()"<<endl; 
  }
  protected:
    int _d;
};

int main()
{
  D d;
  return 0;
}
#endif

#if 0
class B
{
  public:
    B(int b)
      :_b(b)
    {
      cout<<"B()"<<endl;
    }

    B(const B& b)
      :_b(b._b)
    {}

    B& operator=(const B& b)
    {
      if(this!=&b)
      {
        _b=b._b;
      }
      return *this;
    }

  protected:
    int _b;
};

//如果基类的构造函数是带有参数的构造函数，用户必须在派生类构造函数的初始化列表的位置显示调用，以完成基类部分成员初始化的工作

class D: public B
{
  public:
    D(int b,int d)
      :B(b)
      ,_d(d)
    {
      cout<<"D()"<<endl;
    }

    D(const D& d)
    :B(d)
     ,_d(d._d)
    {}

    D& operator=(const D& d)
    {
      if(this!=&d)
      {
        B::operator=(d);
        _d=d._d;
      }
      return *this;
    }

  protected:
    int _d;
};

int main()
{
  D d1(1,2);
  D d2(d1);

  D d3(3,4);
  d2=d3;
  return 0;
}
#endif


#if 0
class Base
{
  public:
    Base(int b=10)
      :_b(b)
    {}

    void SetBase(int b)
    {
      _b=b;
    }

  protected:
    int _b;
};

class Derived: public Base
{
  public:
    void SetDerived(int b,int d)
    {
      _b=b;
      _d=d;
    }
  protected:
      int _d;
};

int main()
{
  Base b;
  Derived d;
  return 0;
}
#endif


#if 0
class Base
{
  public:
    Base(int b)
      :_b(b)
    {}

    void SetBase(int b)
    {
      _b=b;
    }
  protected:
    int _b;
};

class Derived : public Base
{
  public:
    //如果编译器生成默认的构造函数，则编译器生成的构造函数一定是无参的
    //Derived()
        //:Base()
        //{}
    //派生类默认构造函数在其初始化列表位置调用基类构造函数时，必须调用基类无参或者全缺省的构造函数
     Derived(int b,int d)
      :Base(b)
       ,_d(d)
  {}
    void SetDerived(int b,int d)
    {
      _b=b;
      _d=d;
    }
  protected:
    int _d;
};
int main()
{
  Base b(10);
  Derived d(10,20);
  return 0;
}
#endif

#if 0
class Base
{
  public:
    Base(int b)
      :_b(b)
    {}
    Base(const Base& b)
      :_b(b._b)
    {}
    void SetBase(int b)
    {
      _b=b;
    }
  protected:
    int _b;
};

class Derived: public Base
{
  public:
    Derived(int b,int d)
      :Base(b)
       ,_d(d)
  {}
    Derived(const Derived& d)
      :Base(d)
       ,_d(d._d)
  {}
    void SetDerived(int b,int d)
    {
      _b=b;
      _d=d;
    }
  protected:
    int _d;
};


int main()
{
  Base b(10);
  Derived d1(10,20);
  Derived d2(d1);

  Derived d3(30,40);
  d2=d3;
  return 0;
}
#endif

#if 0
class Base
{
  public:
    Base(int b)
      :_b(b)
    {}
    
    Base(const Base& b)
      :_b(b._b)
    {}

    Base& operator=(const Base& b)
    {
      if(this!=&b)
      {
        _b=b._b;
      }
      return *this;
    }

    void SetBase(int b)
    {
      _b=b;
    }
  protected:
    int _b;
};

class Derived:public Base
{
  public:
    Derived(int b,int d)
      :Base(b)
       ,_d(d)
    {}

    Derived(const Derived& d)
      :Base(d)
       ,_d(d._d)
    {}

    Derived& operator=(const Derived& d)
    {
      if(this!=&d)
      {
        //给基类部分成员赋值
        Base::operator=(d);
        //给派生类新增加成员赋值
        _d=d._d;
      }
      return *this;
    }
    void SetDerived(int b ,int d)
    {
      _b=b;
      _d=d;
    }
  protected:
    int _d;
};

int main()
{
  Base b(10);
  Derived d1(10,20);
  Derived d2(d1);

  Derived d3(30,40);
  d2=d3;
  return 0;
}
#endif

#if 0
class Base
{
  public:
    Base(int b)
      :_b(b)
    {
      cout<<"Base::Base(int)"<<endl;
    }

    ~Base()
    {
      cout<<"Base::~Base()"<<endl;
    }

  protected:
    int _b;
};

class Derived : public Base
{
  public:
    Derived(int b,int d)
      :Base(b)
       ,_d(d)
    {
      cout<<"Derived::Derived(int,int)"<<endl;
    }

    ~Derived()
    {
      cout<<"Derived::~Derived()"<<endl;
      //call Base::~Base();
    }
  protected:
    int _d;
};
//1、运行结束打印结果
//Base::Base(int)
//Derived::Derived(int,int)
//Derived::~Derived()
//Base::~Base()
//2、构造和析构的调用次序
//函数体的执行次序：先执行基类构造--->派生类构造--->派生类析构--->基类析构
//构造次序:
//派生类构造函数()
//  : 基类构造函数()
//  {}
//  析构次序：
//  派生类析构函数()
//  {
//    释放派生类资源
//    编译器在派生类析构函数最后一条有效语句后插了一条汇编代码
//    call 基类析构函数
//  }
void TestDerived()
{
  Derived d(10,20);
}

int main()
{
  TestDerived();
  return 0;
}
#endif

#if 0
//C++ 98
//设计一个类不能被继承

class Base
{
  public:
    static Base GetObject(int b)
    {
      return Base(b);
    }
  private:
    Base(int b)
      :_b(b)
    {}
  protected:
    int _b;
};

#if 0
class Derived:public Base
{
  public:
    Derived()
      :Base()
    {}
    因为基类构造函数访问权限是private，其子子类中就不能直接被调用，因此派生类的构造函数无法生成
};
#endif
int main()
{
  //Derived d;
  //拷贝构造函数
  Base b(Base::GetObject(10));
  return 0;
}
#endif


#if 0
// C++ 11
// final 如果修饰一个类：表示该类不能被继承
class Base final
{
  public:
    Base(int b)
      :_b(b)
    {}
  protected:
    int _b;
};
//base 'Base' is marked 'final'
class Derived : public Base
{};

int main()
{
  return 0;
}
#endif


#if 0
//友元关系：不能被继承
class Base
{
  friend void Print();
  public:
    Base(int b)
      :_b(b)
    {}
    int GetB()
    {
      return _b;
    }
  protected:
    int _b;
};

class Derived : public Base
{
  public:
    Derived(int b,int d)
      :Base(b)
       ,_d(d)
  {}
  protected:
    int _d;
};
void Print()
{
  Base b(10);
  cout<<b.GetB()<<endl;
  cout<<b._b<<endl;

  Derived d(10,20);
  //cout<<d.Print()<<endl;
  //no member named 'Print' in 'Derived'
}

int main()
{
  Print();
  return 0;
}
#endif


#if 0
//统计一个类创建了多少个对象
#include <string>
class Person
{
  public:
    Person (const string& name,const string& gender,int age)
      :_name(name)
       ,_gender(gender)
       ,_age(age)
  {
    _count++;
  }

    Person(const Person& p)
      :_name(p._name)
       ,_gender(p._gender)
       ,_age(p._age)
  {
    ++_count;
  }

    ~Person()
    {
      --_count;
    }

  protected:
    string _name;
    string _gender;
    int _age;
  public:
    static size_t _count;
};
size_t Person::_count =0;

class Student:public Person
{
  public:
    Student (const string& name,const string& gendr,int age,int stuId)
     :Person(name,gendr,age)
     ,_stuId(stuId)
       {}

    Student(const Student& s)
     :Person(s)
     ,_stuId(s._stuId)
       {}

  protected:
     int _stuId;
};

class Teacher : public Person
{
  public:
    Teacher(const string& name,const string& gendr,int age,int stuId)
      :Person(name,gendr,age)
       ,_stuId(stuId)
    {}

    Teacher(const Teacher& s)
      :Person(s)
       ,_stuId(s._stuId)
    {}

  protected:
    int _stuId;
};

void TestPerson()
{
  Person p("111","男",18);
  Student s("222","女",18,19784);

  cout<<Person::_count<<endl;
  cout<<Student::_count<<endl;
  cout<<s._count<<endl;

  cout<<&Person::_count<<endl;
  cout<<&Student::_count<<endl;
  cout<<&Teacher::_count<<endl;
  //结论：
  //1、基类中静态成员变量可以被子类继承
  //2、在整个继承体系中，静态成员变量只有一份
}

int main()
{
  TestPerson();
  return 0;
}
#endif

#if 0
//多继承
class B1
{
  public:
    int _b1;
};

class B2
{
  public:
    int _b2;
};

//注意：每个基类前必须给出继承权限，否则就是默认的继承权限
//先继承谁，在栈上，谁的地址就大
class D : public B2,public B1
{
  public:
    int _d;
};

int main()
{
  cout<<sizeof(D)<<endl;

  D d;
  d._b1=1;
  d._b2=2;
  d._d=3;
  return 0;
}
#endif


#if 0
class B
{
  public:
    int _b;
};

class C1:public B
{
  public:
    int _c1;
};

class C2: public B
{
  public:
    int _c2;
};

class D: public C1,public C2
{
  public:
    int _d;
};

int main()
{
  cout<<sizeof(D)<<endl;

  D d;
  //d._b=1;
  //菱形继承缺陷：会存在二义性问题
  d.C1::_b=1;
  d._c1=2;
  
  d.C2::_b=3;
  d._c2=4;

  d._d=5;
  return 0;
}
#endif

#if 0
class B
{
  public:
    int _b;
};

class C1:virtual public B
{
  public:
    int _c1;
};

class C2:virtual public B
{
  public:
    int _c2;
};

class D: public C1,public C2
{
  public:
    int _d;
};

int main()
{
  cout<<sizeof(D)<<endl;

  D d;
  d._b=1;
  
  d.C1::_b=1;
  d._c1=2;

  d.C2::_b=3;
  d._c2=4;

  d._d=5;
  return 0;
}
#endif

class B
{
  public:
    int _b;
};
class C1:virtual public B
{
  public:
    int _c1;
};
class C2:virtual public B
{
  public:
    int _c2;
};
class D: public C1,public C2
{
  public:
    int _d;
};

int main()
{
  D d;
  d._b=1;
  d._c1=2;
  d._c2=3;
  d._d=4;
  return 0;
}







