/*************************************************************************
    > File Name: Gauss.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 日  4/20 16:50:16 2014
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cah>
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

// n^3
int a[333][333], mt[333][333];
int x[333];
bool isFree[333];

void out(int n, int m){
  for(int i = 0; i < m; i++)
    for(int j = 0; j <= n; j++)
      printf("%d%s", a[i][j], (j == n) ? "\n": " ");
  puts("");
}

//0 or 1 int
int Gauss(int n, int m){// n values,  m equations
  int r = 0, c = 0;  // deal (r, c)
  //out(n, m);
  vector<int> free;
  fill(isFree, isFree + n, 0);
  while(r < m && c < n){
    int mr = r;
    for(int i = r + 1; i < m; i++) if(a[i][c] > a[mr][c]) mr = i;
    for(int j = c; j <= n; j++) swap(a[r][j], a[mr][j]);
    int v = a[r][c];
    if(v == 0) { free.push_back(c), isFree[c] = 1; c++; continue; }
    
    for(int i = r + 1; i < m; i++) if(a[i][c]){
      for(int j = c; j <= n; j++) {
        a[i][j] ^= a[r][j];
      }
    }
    r++, c++;
  }
  for(int i = r; i < m; i++) if(a[i][n]) return -1;
  //out(n, m);  

//高斯消元法 枚举01 自由基
  //cerr<<"free size = "<<n - r<<endl;
  int MS = 1<<(n - r);
  int ans = n;
  for(int s = 0; s < MS; s++){
    for(int i = 0; i < m; i++)
      for(int j = 0; j <= n; j++) mt[i][j] = a[i][j];

    fill(x, x + n, 0);
    for(int i = 0; i < free.size(); i++){
      if(s & (1<<i)) x[free[i]] = 1;
      else x[free[i]] = 0;
    }

    int cnt = 0, nr = r;
    for(int j = n - 1; j >= 0; j--){
      while(j > nr - 1){  // free one j
        for(int i = 0; i < m; i++) mt[i][n] ^= (mt[i][j] & x[j]);
        if(x[j]) cnt++;
        j--;
      }
      x[j] = mt[nr - 1][n];
      if(x[j]) cnt++;
      for(int i = 0; i < m; i++) mt[i][n] ^= (mt[i][j] & x[j]);
      nr--;
    }

    ans = min(ans, cnt);
  }
  //out(n, m);
  return ans;
}

//double
int Gauss(int n, int m){// n values,  m equations

  int r = 0, c = 0;
  //out(n, m);
  while(r < m && c < n){
    int mr = r;
    for(int i = r + 1; i < m; i++) if(fabs(a[i][c]) > fabs(a[mr][c]))mr = i;
    for(int j = c; j <= n; j++) swap(a[r][j], a[mr][j]);
    double v = a[r][c];
    if(fabs(v) < eps){ c++; continue; }
    for(int j = c; j <= n; j++) a[r][j] /= v;
    for(int i = r + 1; i < m; i++) if(fabs(a[i][c]) > eps){
      v = a[i][c] / a[r][c];
      for(int j = c; j <= n; j++){
        a[i][j] -= v * a[r][j];
      }
    }
    r++, c++;
  }
  
// 高斯消元求取确定量：（初始均为不确定量）
  fill(unsure, unsure + n, true);
  if(n > r){
    for(int i = r - 1; i >= 0; i--){
      int free_num = 0, free_index = 0;
      for(int j = 0; j < n; j++) 
        if(unsure[j] && fabs(a[i][j]) > eps) { free_num++; free_index = j; }
      if(free_num > 1) continue;
      //free_index
      x[free_index] = a[i][n] / a[i][free_index], unsure[free_index] = 0;
      for(int ii = 0; ii < m; ii++)
        a[ii][n] -= a[ii][free_index] * x[free_index];
    }
    return n - r;
  }
  else 
  for(int j = n - 1; j >= 0; j--){
    while(j > r - 1) j--;
    x[j] = a[r - 1][n];
    for(int i = 0; i < m; i++) 
      a[i][n] -= x[j] * a[i][j];
    r--;
  }
  return 0;
}

