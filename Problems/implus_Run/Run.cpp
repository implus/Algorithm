/*************************************************************************
    > File Name: Run.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 五  2/14 14:42:51 2014
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

int vx, vy, x, y;
int n, m;
double gao(double w){
  double l = sqrt(1.0*vx*vx + 1.0*vy*vy);
  return fabs(1.0*vx*w - 1.0*vy) / l;
}
int main(){
  while(scanf("%d%d", &n, &m) == 2){
    double mi = 1e99, ma = -1e99, t;
    for(int i = 0; i < n; i++) scanf("%d%d", &x, &y), t = 1.0*y/x, mi = min(mi, t), ma = max(ma, t);
    while(m--){
      scanf("%d%d", &vx, &vy);
      double ans;
      if(vx == 0 && vy == 0) ans = 0;
      else ans = max(gao(mi), gao(ma));
      printf("%.6lf\n", ans);
    }
  }
  return 0;
}
