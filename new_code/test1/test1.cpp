//牛牛有一个由小写字母组成的字符串s,在s中可能有一些字母重复出现。
//比如在"banana"中,字母'a'和字母'n'分别出现了三次和两次。但是牛牛不喜欢重复。
//对于同一个字母,他只想保留第一次出现并删除掉后面出现的字母。请帮助牛牛完成对s的操作。

#include <iostream>
using namespace std;
#include <string>

int main()
{
  string temp;
  cin>>temp;
  int Re[26]={0};
  for(int i=0;i<temp.length();i++)
  {
        if(Re[temp[i]-'a']==0)
        {
          cout<<temp[i];
        }
        Re[temp[i]-'a']++;
  }
  cout<<endl;
}








