#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

const int maxn = 333;
const int maxc = 333;
int T,C,N, M;
const double eps = 1e-8;
inline int dcmp(double x){
  return (x > eps) - (x < -eps);
}
struct Point{
  double x,y;
  Point(){}
  Point(double x,double y):x(x),y(y){}
  Point operator+(const Point& p)const { return Point(x + p.x, y + p.y); }
  Point operator-(const Point& p)const { return Point(x - p.x, y - p.y); }
  Point operator*(const double& p)const { return Point(x*p, y*p); }
  double operator*(const Point& p)const { return x*p.x + y*p.y; }
  Point operator/(const double& p)const { return Point(x/p, y/p); }
  double operator^(const Point& p)const { return x*p.y - y*p.x; }
  void read(){ scanf("%lf%lf", &x, &y); }
  double Len(){ return sqrt(x*x + y*y); }
  Point Normal(){ double d = Len(); return Point(-y/d, x/d); }
  Point One(){ double d = Len(); return Point(x/d, y/d); }
  bool operator==(const Point& p)const{ return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0; }
}p[maxn];
typedef Point Vector;

struct PointN{
  Point p; double d;
  PointN(){}
  PointN(Point p, double d):p(p), d(d){}
  bool operator<(const PointN& q)const{ return d < q.d; }
  bool operator==(const PointN& q)const{ return dcmp(d - q.d) == 0; }
};
double Area(vector<Point>& v){
  double s = 0;
  for(int i = 0; i < v.size(); i++){
    s += v[i] ^ v[(i + 1)% v.size()];
  }
  return s * 0.5;
}
inline bool OnSegment(Point p, Point a1, Point a2){
  return dcmp((a1 - p)^(a2 - p)) == 0 && dcmp((a1 - p)*(a2 - p)) <= 0;
}
Point IntersectionLineLine(Point& P, Vector& v, Point& Q, Vector& w){
  double t = (P - Q)^w / (v^w); t = -t;
  return P + v*t;
}

struct Polygon{
  vector<Point> v;
  Polygon(){}
  Polygon(vector<Point> v):v(v){}
  void Moderate(){ if(dcmp(Area(v)) < 0) reverse(v.begin(), v.end()); }
  int Contain(Point p){
    int wn = 0;
    for(int i = 0; i < v.size(); i++){
      int ni = (i + 1) % v.size();
      if(OnSegment(p, v[i], v[ni]))return -1;
      int k = dcmp((v[ni] - v[i]) ^ (p - v[i]));
      int d1 = dcmp(v[i].y - p.y), d2 = dcmp(v[ni].y - p.y);
      if(k > 0 && d1 <= 0 && d2 > 0) wn++;
      if(k < 0 && d1 > 0 && d2 <= 0) wn--;
    }
    if(wn) return 1;
    return 0;
  }
}ct[maxc];

struct Line{
  Point P; Vector v;
  Line(){}
  Line(Point P, Vector v):P(P),v(v){}
  bool OnSegment(Point Q, int ContainEnds = 1){
    return dcmp((P - Q)^(P + v - Q)) == 0 && (
        (ContainEnds && dcmp((P - Q)*(P + v - Q)) <= 0) ||
        (!ContainEnds && dcmp((P - Q)*(P + v - Q)) < 0) );
  }
  double Distance(Point& Q){
    return fabs(v ^ (Q - P)) / v.Len();
  }
  Point Projection(Point& Q){
    double t = (P - Q)*v / (v*v); t = -t;
    return P + v*t;
  }
};
struct Circle{
  Point c; double r;
  Circle(){}
  Circle(Point c,double r):c(c), r(r){}
  void Intersection(Line& L, vector<PointN>& vL){
    vector<Point> ans;
    double d = L.Distance(c);
    if(dcmp(d - r) > 0) return;
    Point p = L.Projection(c);
    double t = sqrt(r*r - d*d);
    Vector v = L.v.One();
    if(L.OnSegment(p + v*t)) vL.push_back( PointN(p + v*t, (p + v*t - L.P).Len()) );
    if(L.OnSegment(p - v*t)) vL.push_back( PointN(p - v*t, (p - v*t - L.P).Len()) );
  }
};

bool in(Point p, double d){
  for(int i = 0; i < C; i++){
    if(ct[i].Contain(p)) return 1;
    vector<Point>& vp = ct[i].v;
    for(int j = 0; j < vp.size(); j++){
      if(dcmp((vp[j] - p).Len() - d) <= 0) return 1;

      int nj = (j + 1) % vp.size();
      Vector v = vp[nj] - vp[j];
      v = v.Normal();
      Polygon po;
      po.v.push_back(vp[j] - v*d);
      po.v.push_back(vp[nj] - v*d);
      po.v.push_back(vp[nj]);
      po.v.push_back(vp[j]);
      po.Moderate();
      if(po.Contain(p)) return 1;
    }
  }
  return 0;
} 
bool IntersectionSegmentSegment(Point a1, Point a2, Point b1, Point b2){
  double c1 = (a2 - a1) ^ (b1 - a1), c2 = (a2 - a1) ^ (b2 - a1),
         c3 = (b2 - b1) ^ (a1 - b1), c4 = (b2 - b1) ^ (a2 - b1);
  return (dcmp(c1) * dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0) ;
  return (dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0) || (
  OnSegment(a1, b1, b2) || OnSegment(a2, b1, b2) || OnSegment(b1, a1, a2) || OnSegment(b2, a1, a2) );
}
bool gao(double d){
  for(int i = 0; i < N - 1; i++){
    Line L(p[i], p[i + 1] - p[i]);// gao intersection
    // add line
    vector<PointN> vL;
    vL.push_back(PointN(p[i], 0)), 
    vL.push_back(PointN(p[i + 1],L.v.Len()));
    if(!in(vL[0].p, d) || !in(vL[1].p, d)) return false;

    for(int j = 0; j < C; j++){
      vector<Point>& vp = ct[j].v;
      int n = vp.size();
      for(int k = 0; k < n; k++){
        int nk = (k + 1) % n;
        Vector v = vp[nk] - vp[k];
        Vector vv= v.Normal();
        //vector<Line> nvl;
        //nvl.push_back(Line(vp[k] - vv*d, v));
        //nvl.push_back(Line(vp[nk] - vv*d, vv*d));
        //nvl.push_back(Line(vp[nk], v*(-1)));
        //nvl.push_back(Line(vp[k], vv*(-d)));
        
        //for(int kk = 0; kk < nvl.size(); kk++){
          Line nL = //nvl[kk];
                    Line(vp[k] - vv*d, v);
          //if(IntersectionSegmentSegment(L.P, L.P + L.v, nL.P, nL.P + nL.v)){
            Point p = IntersectionLineLine(L.P, L.v, nL.P, nL.v);
            if(OnSegment(p, L.P, L.P + L.v)) 
              vL.push_back(PointN(p, (p - L.P).Len()));
          //}
        //}
      }
      for(int k = 0; k < n; k++){
        Circle cir(vp[k], d);
        cir.Intersection(L, vL);
      }
    }
    
    sort(vL.begin(), vL.end());
    vL.erase(unique(vL.begin(), vL.end()), vL.end());

    for(int j = 0; j < vL.size() - 1; j++){
      if(!in((vL[j].p + vL[j + 1].p)/2, d))
        return false;
    }
  }
  return true;
}
int main(){
  T = 1;
 // scanf("%d",&T);
  while(T -- ){
    scanf("%d%d",&C,&N);
    for(int i = 0; i < N; i++) p[i].read();
    for(int c = 0; c < C; c++){
      scanf("%d",&M); ct[c].v.clear(); ct[c].v.resize(M);
      for(int i = 0; i < M; i++) ct[c].v[i].read();
      ct[c].Moderate();
    }
    double l = 0, r = 40000, m;
    while(r - l > 1e-4){
      m = (l + r) / 2;
      if(gao(m)) r = m;
      else l = m;
    }
    printf("%.2lf\n", l);
  }
  return 0;
}

