/*************************************************************************
    > File Name: HuiWen.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 三  3/ 5 00:08:21 2014
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<string>
#include<set>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lson l,m,ls
#define rson m+1,r,rs

const int maxn = 222222;
struct HW{
  string predo(string s){
    string ans = "#";
    for(int i = 0; i < s.size(); i++){ ans += s[i]; ans += "#"; }
    return ans;
  }
  int p[maxn];
  int gao(string& s){
    int i, mx = 0, id, np;
    s = predo(s);
    for(i = 1; i < s.size(); i++){
      if(mx >= i) p[i] = min(p[2*id - i], mx - i);
      else p[i] = 0;
      while(np = p[i] + 1, i + np < s.size() && i - np >= 0 && s[i + np] == s[i - np]) p[i] = np;
      if(i + p[i] > mx){ mx = i + p[i]; id = i; }
    }
    return *max_element(p + 1, p + s.size());
  }
}lx;
char ch[111111];
int main(){
  while(scanf("%s", ch) == 1){
    string s = ch;
    printf("%d\n", lx.gao(s));
  }
  return 0;
}

