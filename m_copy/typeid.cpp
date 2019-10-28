#include <iostream>
using namespace std;
#include <typeinfo>
int main()
{
  cout<<typeid(char).name()<<endl;;
  cout<<typeid(char*).name()<<endl;
  cout<<typeid(short).name()<<endl;
  cout<<typeid(short*).name()<<endl;
  cout<<typeid(int).name()<<endl;
  cout<<typeid(int*).name()<<endl;
  cout<<typeid(long).name()<<endl;
  cout<<typeid(long*).name()<<endl;
  cout<<typeid(long long).name()<<endl;;
  cout<<typeid(long long*).name()<<endl;;
  cout<<typeid(float).name()<<endl;;
  cout<<typeid(float*).name()<<endl;;
  cout<<typeid(double).name()<<endl;
  cout<<typeid(double*).name()<<endl;
  return 0;
}
