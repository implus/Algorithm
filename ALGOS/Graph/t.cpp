/*************************************************************************
  > File Name: t.cpp
  > Author: implus
  > Mail: 674592809@qq.com
  > Created Time: 一  5/ 5 21:10:44 2014
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

const int maxn = 11111;
const double pi = acos(-1.0);

struct Point{
  double x, y;
  Point(){} Point(double x, double y):x(x), y(y){}
  double Len(){ return (x*x + y*y); }
  Point operator-(const Point&p) const {
    return Point(x - p.x, y - p.y);
  }
  void read(){
    scanf("%lf%lf", &x, &y);
  }
}lx[maxn];
int n;

double cal(Point p){
  double ans = 0;
  for(int i = 0; i < n; i++){
    ans = max(ans, (lx[i] - p).Len());
  }
  return ans;
}

int main(){
  int X, Y; 
  while(scanf("%d%d%d", &X, &Y, &n) != EOF){
    double xmi = 10000, ymi = 10000, xma = 0, yma = 0;
    for(int i =0 ; i< n; i++) {
      lx[i].read();
      xmi = min(xmi, lx[i].x);
      xma = max(xma, lx[i].x);
      ymi = min(ymi, lx[i].y);
      yma = max(yma, lx[i].y);
    }

    Point ap((xmi + xma) / 2, (ymi + yma) / 2); 
    double ans = cal(ap);
    double step = sqrt((xma - xmi)*(xma - xmi) + (yma - ymi)*(yma - ymi)) / 2;


    while(1){
      double nans = ans; Point np = ap;
      for(double r = 0; r <= 2 * pi; r += 0.1){
        Point tp = Point(ap.x + step * cos(r), ap.y + step * sin(r));
        double tans = cal(tp);
        if(tans < nans) {
          nans = tans; np = tp;
        }
      }
      if(fabs(nans - ans) < 0.01 && step < 0.0001) break;
      if(nans < ans){
        ans = nans;
        ap = np;
      }else step *= 0.5;

    }

    printf("(%.1lf,%.1lf).\n", ap.x, ap.y);
    printf("%.1lf\n", sqrt(ans));
    //printf("(%.1lf,%.1lf).\n%.1lf\n", ap.x, ap.y, sqrt(ans));
  }
  return 0;
}
