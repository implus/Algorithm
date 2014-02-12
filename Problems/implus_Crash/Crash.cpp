/*************************************************************************
    > File Name: Crash.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 一  1/27 11:01:16 2014
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

const double eps = 1e-8;
inline int dcmp(double x){
  return (x > eps) - (x < -eps);
}
struct Point {
  double x, y;
  Point(){}
  Point(double x, double y):x(x), y(y){}
  Point operator-(const Point& p)const{ return Point(x - p.x, y - p.y); }
  double operator^(const Point& p)const{ return x*p.y - y*p.x; }
  void read(){ scanf("%lf%lf", &x, &y); }
  void out() { cerr<<x<<" "<<y<<endl; }
};
double Area(vector<Point> & v){
  double s = 0;
  for(int i = 0; i < v.size(); i++){
    int ni = (i + 1) % v.size();
    s += v[i] ^ v[ni];
  }
  return s * 0.5;
}
struct Polygon{
  vector<Point> v;
  Point& operator[](int x) { return v[x]; }
  void read(int n){
    v.resize(n);
    for(int i = 0; i < n; i++) v[i].read();
  }
  void Moderate(){ if(dcmp( Area(v) ) < 0) reverse(v.begin(), v.end()); }
};

bool _ApartConvexHullConvexHull(Polygon& P, Polygon& Q){
  int n = P.v.size(), m = Q.v.size(), j = 0, nj, i = 0, ni, k, st, en;
  for(k = 0; k < m; k++) 
    if(dcmp(Q[k].x - Q[j].x) > 0 || (dcmp(Q[k].x - Q[j].x) == 0 && dcmp(Q[k].y - Q[j].y) > 0) ) j = k;
  for(k = 0; k < n; k++)
    if(dcmp(P[k].x - P[i].x) < 0 || (dcmp(P[k].x - P[i].x) == 0 && dcmp(P[k].y - P[i].y) < 0) ) i = k;
  if(n == 1){
    if(m <= 1) return true;
    for(j = 0; j < m; j++){
      nj = (j + 1) % m;
      if(dcmp((Q[nj] - Q[j]) ^ (P[0] - Q[j])) < 0) return true;
    }
  }
  st = i, en = i + n;
  for(k = st; k < en; k++){
    i = k % n;
    ni = (i + 1) % n;
    while(nj = (j + 1)%m, dcmp((P[ni] - P[i]) ^ (Q[nj] - Q[j])) > 0) j = nj;
    if(dcmp((P[ni] - P[i]) ^ (Q[j] - P[i])) < 0){ return true; }
  }
  return false;
}
bool ApartConvexHullConvexHull(Polygon& P, Polygon& Q){
  return _ApartConvexHullConvexHull(P, Q) || _ApartConvexHullConvexHull(Q, P);
}

int main(){
  int n, m;
  while(scanf("%d",&n) == 1){
    Polygon P, Q;
    P.read(n); P.Moderate();
    scanf("%d", &m);
    Q.read(m); Q.Moderate();
    if(ApartConvexHullConvexHull(P, Q)) puts("WanWanMeiXiangDao");
    else puts("Crash");
  }
  return  0;
}
