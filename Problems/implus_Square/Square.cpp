/*************************************************************************
    > File Name: Square.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 四  2/20 15:36:07 2014
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

int n, m, k;
int a[1111][1111];
int s[2222][2222];
bool gao(int len){
  //cerr<<"len = "<<len<<endl;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      if(j - len <= 0 || j + len > m || i - 2*len <= 0) continue;
      int ni = i - j + m, nj = i + j - 1;
      int nni = ni - 2*len - 1, nnj = nj - 2*len - 1;
      //cerr<<"ni = "<<ni<<" nj = "<<nj<<endl;
      if(nni >= 0 && nnj >= 0){
        int ans = s[ni][nj] - s[nni][nj] - s[ni][nnj] + s[nni][nnj];
        //cerr<<"[x,y] = ["<<i<<","<<j<<"]"<<endl;
        //cerr<<"ans = "<<ans<<endl;
        if(ans <= k) return 1;
      }
    }
  }
  return 0;
}
int main(){
  while(scanf("%d%d%d",&n, &m, &k) == 3){
    memset(s, 0, sizeof(s));
    for(int i = 1; i <= n; i++)
      for(int j = 1; j <= m; j++){
        scanf("%d", &a[i][j]), s[i - j + m][i + j - 1] = a[i][j];
      }
    for(int i = 1; i < n + m; i++)
      for(int j = 1; j < n + m; j++)
        s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    int le = 0, ri = min(n, m), mi;
    while(ri - le > 1){
      mi = (le + ri) >> 1;
      if(gao(mi)) le = mi;
      else ri = mi;
    }
    printf("%d\n", le + 1);
  }
  return 0;
}
