/*************************************************************************
    > File Name: RunRun.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 六  2/15 16:05:37 2014
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

const int maxn = 111111;
const double inf = 1e99;
struct Point{
  double x, y;
  Point(){}
  Point(double x, double y):x(x),y(y){}
  void read(){
    scanf("%lf%lf", &x, &y);
  }
  double operator^(const Point& p) const{ return x*p.y - y*p.x; }
  double Len(){ return sqrt(x*x + y*y); }
}p[maxn];
double sum[maxn], vp[maxn];
double vx, vy;
int n, m;
int main(){
  while(scanf("%lf%lf", &vx, &vy) == 2){
    Point v(vx, vy), o;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) p[i].read(), vp[i] = v^p[i];
    vp[0] = -inf; vp[n + 1] = inf;
    sort(vp + 1, vp + n + 1);

    sum[0] = 0;
    for(int i = 1; i <= n; i++)
      sum[i] = sum[i - 1] + vp[i];
    
    scanf("%d", &m);
    while(m--){
      o.read();
      double vo = v^o, ans;
      int w = upper_bound(vp, vp + n + 2, vo) - vp;
      // w -> n: v^p - v^o
      // 1 -> w - 1: v^o - v^p
      if(w == 0 || w == n + 1) {
        ans = fabs(sum[n] - vo*n) / v.Len();
      }else{
        ans = sum[n] - sum[w - 1] - vo*(n - w + 1) + vo*(w - 1) - sum[w - 1];
        ans = ans / v.Len();
      }
      printf("%.6lf\n", ans);
    }
  }
  return 0;
}
