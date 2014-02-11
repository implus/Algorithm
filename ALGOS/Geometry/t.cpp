//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;

const double eps = 1e-8;
inline int dcmp(double x){
  return (x > eps) - (x < -eps);
}
const int maxp = 333;
const int maxc = 333;
int T,C,N,M;

struct Point{
  double x,y;
  Point(){}
  Point(double x,double y):x(x),y(y){}
  void read(){ scanf("%lf%lf",&x,&y); }
  Point operator+(const Point& p)const{ return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p)const{ return Point(x - p.x, y - p.y); }
  Point operator*(const double& p)const{ return Point(x*p, y*p); }
  double operator*(const Point& p)const{ return x*p.x + y*p.y; }
  double operator^(const Point& p)const{ return x*p.y - y*p.x; }
  double Len(){ return sqrt((*this) * (*this)); }
}p[maxp], GLOBAL;
typedef Point Vector;
struct Line{
  Point P; Vector v;
  Line(){}
  Line(Point P, Vector v):P(P),v(v){}
  double SegmentDistance(Point Q, Point& T = GLOBAL){
    if(dcmp(v.Len()) == 0) { T = P; return (Q - P).Len(); }
    Vector v2 = Q - P, v3 = Q - P - v;
    if(dcmp(v*v2) < 0) { T = P; return v2.Len(); }
    if(dcmp(v*v3) > 0) { T = P + v; return v3.Len(); }
    double t = -((P - Q)*v / (v*v)); T = P + v*t;
    return fabs(v^v2)/v.Len();
  }
};
double Area(vector<Point>& v){
  double s = 0;
  for(int i = 0; i < v.size(); i++)
    s += v[i] ^ v[(i + 1)%v.size()];
  return s * 0.5;
}
inline bool OnSegment(Point& p, Point& a1, Point& a2){
  return dcmp((a1 - p) ^ (a2 - p)) == 0 && dcmp((a1 - p)*(a2 - p)) <= 0;
}
struct Polygon{
  vector<Point> v;
  void Moderate(){ if(dcmp(Area(v)) < 0){ reverse(v.begin(), v.end()); } }
  bool Contain(Point p){
    int wn = 0;
    for(int i = 0; i < v.size(); i++){
      int ni = (i + 1) % v.size();
      if(OnSegment(p, v[i], v[ni])) return -1;
      int k = dcmp((v[ni] - v[i])^(p - v[i]));
      int d1 = dcmp(v[i].y - p.y);
      int d2 = dcmp(v[ni].y - p.y);
      if(k > 0 && d1 <= 0 && d2 > 0) wn++;
      if(k < 0 && d1 > 0 && d2 <= 0) wn--;
    }
    if(wn) return 1;
    return 0;
  }
}ct[maxc];

bool check(Point &p){
  for(int i = 0; i < C; i++)
    if(ct[i].Contain(p)) return 1;
  return 0;
}
double gao(Point p, Point& w){
  if(check(p)) { w = p; return 0;}
  double ans = 1e99; Point ansp, tp;
  for(int i = 0; i < C; i++){
    vector<Point>& vp = ct[i].v;
    int n = vp.size();
    for(int j = 0; j < n; j++){
      Line L(vp[j], vp[(j + 1)%n] - vp[j]);
      double d = L.SegmentDistance(p, tp);
      if(d < ans) { ans = d, w = tp; }
    }
  }
  return ans;
}
int main(){
  scanf("%d",&T);
  while(T--){
    scanf("%d%d",&C,&N);
    for(int i =0; i < N; i++) p[i].read();
    for(int c= 0; c < C; c++){
      scanf("%d",&M);  ct[c].v.resize(M);
      for(int i = 0; i < M; i++) ct[c].v[i].read();
      ct[c].Moderate();
    }
    double ans = 0;
    queue<Line> q;
    for(int i = 0; i < N - 1; i++)
      q.push(Line(p[i], p[i + 1] - p[i]));

    while(q.size()){
      Line L = q.front(); q.pop();
      Point p1, p2;
      double l1 = gao(L.P, p1), l2 = gao(L.P + L.v, p2);
      ans = max(ans, l1);
      ans = max(ans, l2);
      
      double l = 0, r = 1, m;
      while(r - l > eps){
        m = (l + r) / 2;
        Point tp = L.P + L.v*m;
        if(dcmp( (tp - p1).Len() - (tp - p2).Len() ) >= 0) r = m;
        else l = m;
      }
      //double l = 1.0 * (rand()%100 / 100);
      Point tp = L.P + L.v*l;
      if((tp - p1).Len() > ans + 0.001) q.push(Line(L.P, tp - L.P));
      if((tp - p2).Len() > ans + 0.001) q.push(Line(tp, L.P + L.v - tp));

    }
    printf("%.6lf\n",ans);
  }
  return 0;
}
