/*************************************************************************
  > File Name: GeoBase.cpp
  > Author: implus
  > Mail: 674592809@qq.com
  > Created Time: 五 12/20 19:30:04 2013
 ************************************************************************/
//同类型的交互写在全局函数
//不同类型写在高等级的类型内部

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
#include<limits>
#include<cassert>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lson l,m,ls
#define rson m+1,r,rs

const double PI = acos(-1.0);
const double eps = 1e-8;
inline int dcmp(double x){
  return (x > eps) - (x < -eps);
}

struct Point{
  double x,y;
  Point(double x=0, double y=0):x(x),y(y){}

  Point operator+(const Point& p)const{ return Point(x + p.x,y + p.y);}
  Point operator-(const Point& p)const{ return Point(x - p.x,y - p.y);}
  Point operator*(const double& p)const{ return Point(x*p,y*p);}
  Point operator/(const double& p)const{ return Point(x/p,y/p);}

  double operator*(const Point& p)const{ return x*p.x + y*p.y;}//dot, v=a*b*cos(c)
  double operator^(const Point& p)const{ return x*p.y - y*p.x;}//x, abs=a*b*sin(c) 
  // a,b quadrangle_area = |a^b|
  // 3D: a,b,c parallelepiped_volume = a^b*c
  Point Rotate(double rad){
    return Point(x*cos(rad) - y*sin(rad),x*sin(rad) + y*cos(rad));
  }
  Point Normal(){ double l = Len(); return Point(-y/l,x/l); }
  Point One(){ double l = Len(); return Point(x/l,y/l); }
  double Len(){ return sqrt((*this)*(*this));}
  double Area2(Point A,Point B,Point C){ return fabs((B-A)^(C-A));}
  bool operator < (const Point& p)const{
    return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && dcmp(y - p.y) < 0);
  }
  bool operator == (const Point& p)const{
    return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0;
  }
  void read(){ scanf("%lf%lf",&x,&y); }
  void out(){ printf("%lf %lf ",x,y); }
};

typedef Point Vector;

struct Line;
double angle(Vector v){ return atan2(v.y, v.x); }
double Angle(Vector A, Vector B){ return acos((A*B)/A.Len()/B.Len()); }
//count two lines intersections
int CountTwoLines(Point P, Vector v, Point Q, Vector w){
  if(dcmp(v^w))return 1;// has 1 intersection
  if(dcmp(v^(P - Q)))return 0;// has 0 intersection, pingxing
  return numeric_limits<int>::max();// has inf intersections, chonghe
}
//make sure P+vt has 1 intersection with Q+wt; when dcmp(v^w)!=0
Point IntersectionLineLine(Point P, Vector v, Point Q, Vector w){
  double t = -((P - Q)^w)/(v^w);// dcmp(v^w)!=0
  return P + v*t;
}

// point on segment, <= 0 in ends, < 0 not ends;
bool OnSegment(Point p, Point a1, Point a2, int ContainEnds = 1){
  return dcmp((a1 - p)^(a2 - p)) == 0 && (
      (ContainEnds && dcmp((a1 - p)*(a2 - p)) <= 0) ||
      (!ContainEnds && dcmp((a1 - p)*(a2 - p)) < 0) );
}

// only one point, ContainEnds == 0, not in ends; ContainEnds == 1, in ends;
bool IntersectionSegmentSegment(Point a1, Point a2, Point b1, Point b2, int ContainEnds= 1){
  double c1 = (a2 - a1)^(b1 - a1), c2 = (a2 - a1)^(b2 - a1),
         c3 = (b2 - b1)^(a1 - b1), c4 = (b2 - b1)^(a2 - b1);
  return (dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0) ||
    (ContainEnds == 1 && (OnSegment(a1,b1,b2) || OnSegment(a2,b1,b2) || 
                          OnSegment(b1,a1,a2) || OnSegment(b2,a1,a2)));
}


double Area(vector<Point> p, int Direction = 0){// anticlockwise
  double ans = 0; int n = p.size();
  for(int i = 1; i < n-1; i++)
    ans += (p[i] - p[0])^(p[i + 1] - p[0]);
  return Direction ? ans/2 : fabs(ans/2);
}

struct Line{
  Point P; Vector v;
  double ang;
  Line(){}
  Line(Point P,Vector v):P(P),v(v){ ang = atan2(v.y, v.x); }
  bool operator<(const Line& L)const{
    return ang < L.ang;
  }
  bool OnSegment(Point Q, int ContainEnds = 1){
    return dcmp((P - Q)^(P + v - Q)) == 0 && (
        (ContainEnds && dcmp((P - Q)*(P + v - Q)) <= 0) ||
        (!ContainEnds && dcmp((P - Q)*(P + v - Q)) < 0) );
  }
  int Where(Point Q){
    return dcmp(v^(Q - P));
  }
  double Distance(Point Q){
    return fabs(v^(Q - P))/v.Len();
  }
  double SgnDistance(Point Q){
    return v^(Q - P)/v.Len();
  }
  double SegmentDistance(Point Q){
    if(dcmp(v.Len()) == 0) return (P - Q).Len();
    Vector v2 = Q - P, v3 = Q - P - v;
    if(dcmp(v*v2) < 0)return v2.Len();
    if(dcmp(v*v3) > 0)return v3.Len();
    return fabs(v^v2)/v.Len();
  }
  Point Projection(Point Q){// (P + v*t - Q)*v == 0
    double t = -((P - Q)*v / (v*v));
    return P + v*t;
  }
  void out(){ P.out(), (P + v).out(); }
};

bool IntersectionSegmentSegment(Line A, Line B, int type = 0){
  return IntersectionSegmentSegment(A.P, A.P + A.v, B.P, B.P + B.v, type);
}

Point IntersectionLineLine(Line A, Line B){
  return IntersectionLineLine(A.P, A.v, B.P, B.v);
}
int HalfplaneIntersection(vector<Line>& L, vector<Point>& P){
  //sort(L.begin(), L.end());
  int l = 0, r = 0, n = L.size();
  vector<Point> p(n);
  vector<Line> q(n);
  q[r++] = L[0];

  for(int i = 1; i < n; i++){
    while(r - l > 1 && L[i].Where(p[r - 2]) <= 0) r--;
    while(r - l > 1 && L[i].Where(p[l]) <=  0) l++;
    q[r++] = L[i];
    if(dcmp(q[r - 1].v^q[r - 2].v) == 0){
      r--;
      if(q[r - 1].Where(L[i].P) > 0) q[r - 1] = L[i];
    }
    if(r - l > 1) p[r - 2] = IntersectionLineLine(q[r - 1], q[r - 2]);
  }
  while(r - l > 1 && q[l].Where(p[r - 2]) <= 0) r--;

  if(r - l <= 2) return 0;

  p[r - 1] = IntersectionLineLine(q[l], q[r - 1]);
  for(int i = l; i < r; i++) P.push_back(p[i]);
  return r - l;
}



#define C_out_me 0
#define C_in_me 1
#define me_in_C -1
#define me_equal_C -2
#define has_2_intersections 2
struct Circle{
  Point c;double r;
  Circle(){}
  Circle(Point c,double r):c(c),r(r){}
  Point point(double a){
    return Point(c.x + cos(a)*r, c.y + sin(a)*r);
  }
  vector<Point> Intersection(Line L){
    vector<Point> ans;
    double d = L.Distance(c);  
    if(dcmp(d - r) > 0) return ans;
    Point p = L.Projection(c);
    if(dcmp(d - r) == 0) return ans.push_back(p),ans;
    double t = sqrt(r*r - d*d);
    Vector v = L.v.One();
    return ans.push_back(p + v*t), ans.push_back(p - v*t), ans;
  }
  vector<Vector> Tangent(Point p){
    vector<Vector> ans;
    Vector v = c - p;
    double d = v.Len();
    if(dcmp(d - r) < 0) return ans;
    if(dcmp(d - r) == 0) return ans.push_back(v.Normal()),ans;
    double a = asin(r/d);
    return ans.push_back(v.Rotate(a)), ans.push_back(v.Rotate(-a)), ans;
  }
  bool operator==(const Circle& C)const{
    return c == C.c && dcmp(r - C.r) == 0;
  }
  bool operator<(const Circle& C)const{
    return c < C.c || (c == C.c && r < C.r);
  }
  int Relation(Circle& C){
    double d = (C.c - c).Len();
    if(dcmp(d) == 0 && dcmp(C.r - r) == 0) return me_equal_C;
    if(dcmp(d - C.r - r) >= 0) return C_out_me;// C out me(contain)
    if(dcmp(d + C.r - r) <= 0) return C_in_me;// C in me(contain)
    if(dcmp(d + r - C.r) <= 0) return me_in_C;// me in C(contain)
    return has_2_intersections; // has 2 intersection points
  }
  void read(){
    c.read(), scanf("%lf",&r);
  }
};

// return the number of the intersections of two circles
int IntersectionCircleCircle(Circle C1, Circle C2, vector<Point>& ans){
  double d = (C1.c - C2.c).Len();
  if(dcmp(d) == 0){
    if(dcmp(C1.r - C2.r) == 0)return numeric_limits<int>::max();
    return 0;
  }
  if(dcmp(C1.r + C2.r - d) < 0)return 0;
  if(dcmp(fabs(C1.r - C2.r) - d) > 0)return 0;

  double a = angle(C2.c - C1.c);
  double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
  Point p1 = C1.point(a + da), p2 = C1.point(a - da);

  ans.push_back(p1);
  if(p1 == p2) return 1;
  ans.push_back(p2);
  return 2;
}

struct Event{
  double a; int t;
  Event(){}
  Event(double a,int t):a(a),t(t){}
  bool operator<(const Event& e)const{
    return dcmp(a - e.a) < 0 || (dcmp(a - e.a) == 0 && t < e.t);
  }
};
void Moderate(double & a){ if(a < 0) a += 2*PI; else if(a > 2*PI) a -= 2*PI; }
double UnionCircles(vector<Circle> v){
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  double s = 0;

  vector<Circle> nv;
  for(int i = 0; i < v.size(); i++){
    bool ok = 1;
    for(int j = 0; j < v.size(); j++)if(i ^ j)
      if(v[i].Relation(v[j]) == me_in_C){
        ok = 0; break;
      }
    if(ok) nv.push_back(v[i]);
  }
  v.swap(nv);
  for(int i = 0; i < v.size(); i++){
    int cnt = 0;
    vector<Event> ve;
    ve.push_back(Event(0, 1));
    ve.push_back(Event(2*PI, -1));
    for(int j = 0; j < v.size(); j++)if(i ^ j){
      if(v[i].Relation(v[j])== has_2_intersections){
        Circle C1 = v[i], C2 = v[j];
        Vector L = C2.c - C1.c;
        double d = L.Len(), a = atan2(L.y, L.x); Moderate(a);
        double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
        double a1 = a - da; Moderate(a1);
        double a2 = a + da; Moderate(a2);
        if(dcmp(a1 - a2) > 0) cnt++;
        ve.push_back(Event(a1, 1)), ve.push_back(Event(a2, -1));
      }
    }

    sort(ve.begin(), ve.end());
    double l = 0, r, R = v[i].r;  
    for(int j = 0; j < ve.size(); j++){
      r = ve[j].a;
      if(cnt == 1) {
        double ang = r - l;
        Point p1 = v[i].point(l), p2 = v[i].point(r);
        s += R * R * (ang - sin(ang));
        s += p1 ^ p2;
      }
      l = r;
      cnt += ve[j].t;
    }
  }
  return s * 0.5;
}

// return the number of tangents, 0,1,2,3,4,inf possible, Points is tangents of Circles
int TangentCircleCircle(Circle A, Circle B, Point* a, Point* b){
  int cnt = 0;
  if(A.r < B.r) swap(A,B), swap(a,b);
  double d = (A.c - B.c).Len();
  double rdiff = A.r - B.r, rsum = A.r + B.r;
  if(dcmp(d - rdiff) < 0)return 0;// nei han 0

  double base = angle(B.c - A.c);
  if(dcmp(d) == 0 && dcmp(A.r - B.r) == 0)return numeric_limits<int>::max();// inf 
  if(dcmp(d - rdiff) == 0){// nei qie 1
    a[cnt] = A.point(base), b[cnt] = B.point(base);cnt++;
    return 1;
  }
  //wai gong qie xian
  double ang = acos((A.r - B.r) / d);
  a[cnt] = A.point(base + ang), b[cnt] = B.point(base + ang); cnt++;
  a[cnt] = A.point(base - ang), b[cnt] = B.point(base - ang); cnt++;

  if(dcmp(d - rsum) == 0){// 1 nei gong qie xian
    a[cnt] = A.point(base), b[cnt] = B.point(PI + base); cnt++;
  }else if(dcmp(d - rsum) > 0){// 2 nei gong qie xian
    double ang = acos((A.r + B.r) / d);
    a[cnt] = A.point(base + ang), b[cnt] = B.point(base + ang + PI); cnt++;
    a[cnt] = A.point(base - ang), b[cnt] = B.point(base - ang + PI); cnt++;
  }
  return cnt;
}

// Point && Polygon
struct Polygon{
  vector<Point> v;
  Polygon(){}
  Polygon(vector<Point> v):v(v){}
  Polygon(int n){v.resize(n);}
  Point& operator[](int x){ return v[x];}
  int size()const{ return v.size();}
  void push_back(Point p){ v.push_back(p); }

  int Contain(const Point& p){
    int wn = 0;
    int n = v.size();
    for(int i = 0; i < n; i++){
      int ni = (i + 1)%n;
      if(OnSegment(p,v[i],v[ni]))return -1;// on board
      int k = dcmp((v[ni] - v[i])^(p - v[i]));
      int d1 = dcmp(v[i].y - p.y);
      int d2 = dcmp(v[ni].y - p.y);
      if(k > 0 && d1 <= 0 && d2 > 0) wn++;
      if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if(wn) return 1;// inside
    return 0;// outside
  }

  //no repeated points, if edge has points, change <= to <
  vector<Point> ConvexHull(){
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int i, t, n = v.size(), k;

    vector<Point> p;
    for(i = 0; i < n; i++){
      while((t = p.size()) > 1 && dcmp((p[t - 1] - p[t - 2])^(v[i] - p[t - 2])) <= 0)
        p.pop_back();
      p.push_back(v[i]);
    }
    k = p.size();
    for(i = n - 2; i >= 0; i--){
      while((t = p.size()) > k && dcmp((p[t - 1] - p[t - 2])^(v[i] - p[t - 2])) <= 0)
        p.pop_back();
      p.push_back(v[i]);
    }

    if(n > 1) p.pop_back();
    return p;
  }
  /*
  // leftmost x, rightmost y, (x) + QuickHull(x,y,S1) + (y) + QuickHull(y,x,S2)
  // S1 upper xy points, S2 lower xy points
  vector<int> QuickHull(int a,int b,vector<int> S){
  vector<int> ans;
  if(S.size() == 0) return ans;
  int c = S[0], nc;
  Line l(v[a], v[b] - v[a]);
  for(int i = 1; i < S.size(); i++){
  nc = S[i];
  if(dcmp(l.Distance(v[nc]) - l.Distance(v[c])) > 0) c = nc;
  }
  vector<int> A,B; 
  Line ac(v[a], v[c] - v[a]), cb(v[c], v[b] - v[c]);
  for(int i = 0; i < S.size(); i++){
  nc = S[i];
  if(dcmp(ac.v^(v[nc] - v[a])) > 0) A.push_back(nc);
  if(dcmp(cb.v^(v[nc] - v[c])) > 0) B.push_back(nc);
  }
  vector<int> t = QuickHull(a,c,A);
  ans.insert(ans.end(),t.begin(),t.end());
  ans.push_back(c);
  t = QuickHull(c,b,B);
  ans.insert(ans.end(),t.begin(),t.end());
  return ans;
  }
   */
  // erase the redundant points, (anticlockwised)
  void Simplify(){
    //v.erase(unique(v.begin(), v.end()), v.end());
    vector<Point> ans;
    int n = v.size();
    for(int i = 0; i < n; i++){
      Point a = v[i];
      Point b = v[(i + 1)%n];
      Point c = v[(i + 2)%n];
      if(dcmp((a - b)^(c - b))) ans.push_back(b);
    }
    v = ans;
  }
};

bool _IntersectionConvexHullConvexHull(Polygon& P, Polygon& Q){
  int i, j, n = P.size(), m = Q.size();
  if(m > 1)for(i = 0; i < n; i++){
    if(Q.Contain(P[i])) return true;
  }
  if(n > 1 && m > 1) for(i = 0; i < n; i++) for(j = 0; j < m; j++)
    if(IntersectionSegmentSegment(P[i], P[(i + 1)%n], Q[j], Q[(j + 1)%m], 1))
      return true;
  return false;
}
bool IntersectionConvexHullConvexHull(Polygon& P, Polygon& Q){
  return _IntersectionConvexHullConvexHull(P, Q) ||
    _IntersectionConvexHullConvexHull(Q, P);
}

/*
   Line f;
   bool cmp(Point a, Point b){
   return dcmp(f.SgnDistance(a) - f.SgnDistance(b)) < 0;
   }
   double _RotateCaliper(Polygon& P, Polygon& Q){
   f = Line(P[0], P[1] - P[0]);
   int p = max_element(Q.v.begin(),Q.v.end(),cmp) - Q.v.begin(), 
   n = P.size(), m = Q.size();

   double ans = 1e99;
   for(int i = 0; i < n; i++){
   int ni = (i + 1)%n, np;
   f = Line(P[i], P[ni] - P[i]);
   while(np = (p + 1)%m, cmp(Q[p], Q[np])) p = np;

   ans = min(ans, f.SegmentDistance(Q[p]));
   ans = min(ans, f.SegmentDistance(Q[np]));
   Line nf(Q[p], Q[np] - Q[p]);
   ans = min(ans, nf.SegmentDistance(P[i]));
   ans = min(ans, nf.SegmentDistance(P[ni]));
   }
   return ans;
   }
   double RotateCaliperConvexHull(Polygon& P, Polygon& Q){
   double ans = 1e99;
   ans = min(ans, _RotateCaliper(P, Q));
   ans = min(ans, _RotateCaliper(Q, P));
   return ans;
   }
 */
double RotateCaliperConvexHull(Polygon& P, Polygon& Q){
  int n = P.size(), m = Q.size(), j = 0, nj, i = 0, ni, k;
  for(k = 0; k < m; k++)if(dcmp(Q[k].x - Q[j].x) >= 0) j = k;
  double ans = 1e99;
  for(i = 0; i < n; i++){
    ni = (i + 1)%n;
    while(nj = (j + 1)%m, dcmp((P[ni] - P[i])^(Q[nj] - Q[j])) > 0) j = nj;

    Line lp(P[i], P[ni] - P[i]), lq(Q[j], Q[nj] - Q[j]);
    ans = min(ans, lp.SegmentDistance(Q[j]));
    ans = min(ans, lp.SegmentDistance(Q[nj]));
    ans = min(ans, lq.SegmentDistance(P[i]));
    ans = min(ans, lq.SegmentDistance(P[ni]));
  }
  return ans;
}

bool _ApartConvexHullConvexHull(Polygon& P, Polygon& Q){
  int n = P.size(), m = Q.size(), j = 0, nj, i = 0, ni, k;
  for(k = 0; k < m; k++)if(dcmp(Q[k].x - Q[j].x) >= 0) j = k;
  if(n == 1){
    if(m <= 1) return true;
    for(j = 0; j < m; j++){  
      nj = (j + 1)%m;
      if(dcmp((Q[nj] - Q[j]) ^ (P[0] - Q[j])) < 0) return true;
    }
  }
  for(i = 0; i < n; i++){
    ni = (i + 1)%n;
    while(nj = (j + 1)%m, dcmp((P[ni] - P[i]) ^ (Q[nj] - Q[j])) > 0) j = nj;
    if(dcmp((P[ni] - P[i]) ^ (Q[j] - P[i])) < 0) return true;
  }
  return false;
}
bool ApartConvexHullConvexHull(Polygon& P, Polygon& Q){
  return _ApartConvexHullConvexHull(P, Q) || _ApartConvexHullConvexHull(Q, P);
}

//uva 11178 test, Angle, Rotate, IntersectionLineLine
//uva 11796 test, SegmentDistance,
//zoj 1081 test, OnSegment*, Polygon.Contain
//uva 10652,11168 test, ConvexHull, 
//uva 10256 test, IntersectionConvexHullConvexHull, ConvexHull*, IntersectionSegmentSegment[type=1], Polygon.Contain
//poj 3608 test, ConvexHull*, RotateCaliperConvexHull[Polygon,Polygon]*,
//poj 2048 test, Line.OnSegment, IntersectionSegmentSegment
//hdu 3761 poj 3968 test, HalfplaneIntersection,
//poj 2164 test, PSLG, build_graph
//hdu 2823 test, ApartConvexHullConvexHull, RotateCaliperConvexHull, ConvexHull
//凸包求平面最大面积三角形，所有n的算法都挂了，只有n^2的

struct Edge{
  int from, to;// 
  double ang;
  Edge(){}
  Edge(int from, int to, double ang):from(from), to(to), ang(ang){}
};

template<int maxn = 11111>
struct PSLG{
  int n, m, face_cnt;
  double x[maxn], y[maxn];
  vector<Edge> edges;
  vector<int> G[maxn];
  int vis[maxn<<1]; // edge visited
  int left[maxn<<1];// left face id
  int prev[maxn<<1];// edge id before

  vector<Polygon> faces;
  double area[maxn]; // directioned area for each polygon

  void init(int n){
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
    faces.clear();
  }

  // directioned segment from->to's angle 
  double getAngle(int from, int to){ return atan2(y[to] - y[from], x[to] - x[from]); }
  void AddEdge(int from, int to){
    edges.push_back(Edge(from, to, getAngle(from, to)));
    edges.push_back(Edge(to, from, getAngle(to, from)));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  //static bool angcmp(int a, int b){ return edges[a].ang < edges[b].ang; }
  // find faces and cal area
  void Build(){
    for(int u = 0; u < n; u++){
      //sort(G[u].begin(), G[u].end(), angcmp);
      int d = G[u].size();
      for(int i = 0; i < d; i++)
        for(int j = i + 1; j < d; j++)
          if(edges[G[u][i]].ang > edges[G[u][j]].ang) swap(G[u][i], G[u][j]);

      for(int i = 0; i < d; i++)
        prev[G[u][(i + 1)%d]] = G[u][i];
    }
    memset(vis, 0, sizeof(vis));
    face_cnt = 0;
    for(int u = 0; u < n; u++)
      for(int i = 0; i < G[u].size(); i++){
        int e = G[u][i];
        if(!vis[e]){ // anticlockwise find
          face_cnt++;
          Polygon poly;
          while(1){
            vis[e] = 1; left[e] = face_cnt;
            int from = edges[e].from;
            poly.push_back(Point(x[from], y[from]));
            e = prev[e^1];
            if(e == G[u][i])break;
            assert(vis[e] == 0);
          }
          faces.push_back(poly);
        }
      }
    for(int i = 0; i < faces.size(); i++){
      area[i] = Area(faces[i].v,1);
    }
  }
};

PSLG<> g;
const int maxp = 105;
int n, c;
Point P[maxp];
Point V[maxp*maxp];

int ID(Point p){ return lower_bound(V, V + c, p) - V; }

void build_graph(Point* P,int n){
  c = n;
  for(int i = 0; i < n; i++)V[i] = P[i];
  vector<double> dist[maxp];// dist[i][j] i's segment dist to j from P[i];
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)if(i != j)
      if(IntersectionSegmentSegment(P[i], P[(i + 1)%n], P[j], P[(j + 1)%n], 0)){
        Point p = IntersectionLineLine(P[i], P[(i + 1)%n] - P[i], P[j], P[(j + 1)%n] - P[j]);
        V[c++] = p;
        dist[i].push_back((p - P[i]).Len());
      }

  sort(V, V + c);
  c = unique(V, V + c) - V;
  g.init(c);
  for(int i = 0; i < c; i++){
    g.x[i] = V[i].x;
    g.y[i] = V[i].y;
  }

  for(int i = 0; i < n; i++){
    Vector v = P[(i + 1)%n] - P[i];
    double len = v.Len();
    dist[i].push_back(0);
    dist[i].push_back(len);
    sort(dist[i].begin(), dist[i].end());
    int sz = dist[i].size();
    for(int j = 1; j < sz; j++){
      Point a = P[i] + v * (dist[i][j-1] / len);
      Point b = P[i] + v * (dist[i][j] / len);
      if(a == b) continue;
      g.AddEdge(ID(a), ID(b));
    }
  }

  g.Build();

  Polygon poly;
  for(int i = 0; i < g.faces.size(); i++)
    if(g.area[i] < 0){
      poly = g.faces[i];
      reverse(poly.v.begin(), poly.v.end());
      poly.Simplify();
      break;
    }
  int m = poly.size();
  printf("%d\n", m);

  int start = 0;
  for(int i = 0; i < m; i++)
    if(poly[i] < poly[start]) start = i;
  for(int i = start; i < m; i++)
    printf("%.4lf %.4lf\n", poly[i].x, poly[i].y);
  for(int i = 0; i < start; i++)
    printf("%.4lf %.4lf\n", poly[i].x, poly[i].y);

}



int main() {
  int n;
  ios_base::sync_with_stdio(false);
  int T;
  cin>>T;
  while(T--){
    cin>>C>>N;
    for(int i = 0; i < N; i++) p[i].read();
    for(int c = 0; c < C; c++){
      cin>>M; ct[c].v.resize(M);
      for(int i = 0; i < M; i++) ct[c][i].read();
    }

  }
  return 0;
}


