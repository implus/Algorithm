/*************************************************************************
    > File Name: GeoBase3D.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 三  1/ 8 08:11:09 2014
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
#include<limits>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lson l,m,ls
#define rson m+1,r,rs
const double eps = 1e-8;
int dcmp(double x){
  return (x > eps) - (x < -eps);
}
// 3D
struct Point3{
  double x,y,z;
  Point3(){}
  Point3(double x,double y,double z):x(x),y(y),z(z){}
  Point3 operator+(const Point3& p)const{ return Point3(x + p.x,y + p.y,z + p.z); }
  Point3 operator-(const Point3& p)const{ return Point3(x - p.x,y - p.y,z - p.z); }
  double operator*(const Point3& p)const{ return x*p.x + y*p.y + z*p.z; }
  Point3 operator*(const double& p)const{ return Point3(x*p,y*p,z*p); }
  Point3 operator/(const double& p)const{ return Point3(x/p,y/p,z/p); }
  Point3 operator^(const Point3& p)const{ 
    return Point3(y*p.z - p.y*z, -x*p.z + p.x*z, x*p.y - p.x*y);
  }
  double Len(){ return sqrt(x*x + y*y + z*z);}
  bool operator==(const Point3& p){
    return dcmp(x - p.x)==0 && dcmp(y - p.y)==0 && dcmp(z - p.z)==0;
  }
  bool operator<(const Point3& p){
    return dcmp(x - p.x) < 0 || 
    (dcmp(x - p.x)==0 && dcmp(y - p.y) < 0) || 
    (dcmp(x - p.x)==0 && dcmp(y - p.y)==0 && dcmp(z - p.z) < 0);
  }
  void read(){
    scanf("%lf%lf%lf",&x, &y, &z);
  }
};
typedef Point3 Vector3;
struct Plane{
  Point3 p0; Vector3 n;
  bool has(Point3& p){// p in Plane ==> (p - p0)*n == 0
    return dcmp((p - p0)*n) == 0;
  }
  Point3 Projection(Point3& p){// q = p + nt, (q - p0)*n == 0
    double t = -((p - p0)*n/(n*n));
    return p + n*t;
  }
  double Distance(Point3& p, int Directioned = 0){
    return Directioned ? (p - p0)*n/n.Len() : fabs((p - p0)*n)/n.Len();
  }
  int Count(Point3& p1, Point3& p2){
    Vector3 v = p2 - p1;
    double k = v*n;
    if(dcmp(k) == 0){
      if(has(p1)) return numeric_limits<int>::max();
      return 0;
    }
    return 1;
  }
  Point3 Intersection(Point3& p1, Point3& p2){// (p1 + (p2 - p1)*t - p0)*n = 0
    double t = ((p1 - p0)*n) / ((p1 - p2)*n); // judge zero
    return p1 + (p2 - p1)*t;// if segment judge  t in 0 ~ 1
  }
};

double Angle(Vector3 A, Vector3 B){ return acos((A*B) / A.Len() / B.Len()); }
double Area2(Point3 A, Point3 B, Point3 C){
  return ((B - A) ^ (C - A)).Len();
}

bool PointInTri(Point3 P, Point3 P0, Point3 P1, Point3 P2){
  double area1 = Area2(P, P0, P1),
         area2 = Area2(P, P1, P2),
         area3 = Area2(P, P2, P0);
  return dcmp(area1 + area2 + area3 - Area2(P0, P1, P2)) == 0;
}

// P0P1P2 with AB
bool TriSegIntersection(Point3 P0, Point3 P1, Point3 P2, Point3 A, Point3 B, Point3& P){
  Vector3 n = (P1 - P0) ^ (P2 - P0);
  if(dcmp(n*(B - A)) == 0) return false;// AB and P0P1P2 parallel or one face
  else {
    double t = (n*(P0 - A)) / (n*(B - A));
    if(dcmp(t) < 0 || dcmp(t - 1) > 0)return false;
    P = A + (B - A)*t;
    return PointInTri(P, P0, P1, P2);
  }
}

//P to AB
double DistanceToLine(Point3 P, Point3 A, Point3 B){
  Vector3 v1 = B - A, v2 = P - A;
  return (v1 ^ v2).Len() / v1.Len();
}
double DistanceToSegment(Point3 P, Point3 A, Point3 B){
  if(A == B) return (P - A).Len();
  Vector3 v1 = B - A, v2 = P - A, v3 = P - B;
  if(dcmp(v1 * v2) < 0) return v2.Len();
  if(dcmp(v1 * v3) > 0) return v3.Len();
  return (v1 ^ v2).Len() / v1.Len();
}
double Volume6(Point3 A, Point3 B, Point3 C, Point3 D){
  return (D - A) * ((B - A) ^ (C - A));
}

template<int maxf = 10005, int maxp = 555>
struct ConvexHull3D{
  struct Face{
    int a, b, c;
    bool exist;
    Face(){}
    Face(int a,int b,int c,bool exist):a(a), b(b), c(c), exist(exist){}
    Vector3 normal(Point3 *P) const{
      return (P[b] - P[a]) ^ (P[c] - P[a]);
    }
    int cansee(Point3 *P, int i)const{
      return (P[i] - P[a]) * normal(P) > 0;
    }
  };
  int n, m;
  Face F[maxf];
  Point3 P[maxp];
  int LeftFace[maxp][maxp];

  //rao dong init
  double rand01(){ return rand() / (double) RAND_MAX; }
  double randeps() { return (rand01() - 0.5) * eps; }
  Point3 add_noise(Point3 p){ return Point3(p.x + randeps(), p.y + randeps(), p.z + randeps()); }
  Point3 BP[4];
  void AddFace(int a,int b,int c){
    Face f(a,b,c,1);
    LeftFace[a][b] = LeftFace[b][c] = LeftFace[c][a] = m;
    F[m++] = f;
  }
  void init(){
    m = 0;
    for(int i = 0; i < 4; i++) BP[i] = P[i], P[i] = add_noise(P[i]);
    Face f(0,1,2,true);
    if(!f.cansee(P,3)){
      F[m++] = f;
      F[m++] = Face(1,0,3,true); F[m++] = Face(2,1,3,true); F[m++] = Face(0,2,3,true);
    }else{
      F[m++] = f = Face(2,1,0,true);
      F[m++] = Face(0,1,3,true); F[m++] = Face(1,2,3,true); F[m++] = Face(2,0,3,true);
    }
  }
  void dfs2(int p, int a, int b){
    int f = LeftFace[a][b];
    if(F[f].exist){
      if(F[f].cansee(P, p)) dfs(p, f);
      else AddFace(p, b, a);
    }
  }
  void dfs(int p, int f){
    F[f].exist = false;
    dfs2(p, F[f].b, F[f].a);
    dfs2(p, F[f].a, F[f].c);
    dfs2(p, F[f].c, F[f].b);
  }
  void gao(){
    init();
    for(int p = 4; p < n; p++){
      for(int f = 0; f < m; f++)
        if(F[f].exist && F[f].cansee(P, p)){
          dfs(p, f); break;
        }
    }
  }

};
bool TriTriIntersection(Point3* T1, Point3* T2){
  Point3 P;
  for(int i = 0; i < 3; i++){
    if(TriSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i + 1)%3], P))return 1;
    if(TriSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i + 1)%3], P))return 1;
  }
  return 0;
}
bool LineDistance3D(Point3 p1, Vector3 u, Point3 p2, Vector3 v, double& s, double& t){
  double d = (u*u)*(v*v) - (u*v)*(u*v); d = -d;
  double a = (p2 - p1)*u*(v*v) - (p2 - p1)*v*(u*v); a = -a;
  double b = u*u*((p2 - p1)*v) - u*v*((p2 - p1)*u);
  //if(dcmp(d) == 0) return false;
  s = a / d;
  t = b / d;
  return true;
}

// 求异面直线p1+su和p2+tv的公垂线对应的s。如果平行/重合，返回false
bool Rat_LineDistance3D(const Point3& p1, const Vector3& u, const Point3& p2, const Vector3& v, double& s) {
  double b = (u*u)*(v*v) - (u*v)*(u*v);
  if(dcmp(b) == 0) return false;
  double a = (u*v)*(v*(p1 - p2)) - (v*v)*(u*(p1 - p2));
  s = a / b;
  return true;
}

//UVA 11275 test, TriTriIntersection, TriSegIntersection, PointInTri
//hdu 4714 test, LineDistance3D
int main(){
  int T;
  scanf("%d",&T);
  Point3 p[4];
  while(T--){
    for(int i = 0; i < 4; i++) p[i].read();
    double s, t;
    Rat_LineDistance3D(p[0], p[1] - p[0], p[2], p[3] - p[2], s);
    Point3 p1 = p[0] + (p[1] - p[0])*s;

    Rat_LineDistance3D(p[2], p[3] - p[2], p[0], p[1] - p[0], t);
    Point3 p2 = p[2] + (p[3] - p[2])*t;

    printf("%.6f\n",(p1 - p2).Len());
    printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
  }
  return 0;
}
