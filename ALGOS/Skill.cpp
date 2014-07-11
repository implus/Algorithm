//stringstream  的使用
// a = 12 output a = 0XC
// b = 12 output b = 二进制表示
// 分割字符串

#include<iostream>
#include<string>
using namespace std;

#include<sstream>

int main(){
  int a = 12; stringstream ss;
  ss.flags( ios::hex | ios::showbase | ios::uppercase);
  ss << a;
  string n;
  ss >> n;
  cout<< n << endl;

  ss.clear();
  bitset<16> b(12); //b reverse
  ss << b; ss >> n;
  cout<< n << endl;

  //split
  ss.clear();
  ss << "123.67   456,";
  string s1;
  int cnt = 0;
  while(getline(ss, s1, ' ')){//parse
    cerr<< cnt++ <<endl;
    cout<< s1 << endl;
  }
  return 0;
}


#pragma comment(linker,"/STACK:102400000,102400000")//手动扩栈
