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
typedef pair<int,int> PIi;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lson l,m,ls
#define rson m+1,r,rs
const double eps = 1e-8;
const double PI = acos(-1.0);
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
  void read(){ scanf("%lf%lf%lf",&x, &y, &z); }
};
typedef Point3 Vector3;

// *** Spherical cosine rules:
// http://en.wikipedia.org/wiki/Spherical_trigonometry
// cosc = cosa*cosb + sina*sinb*cosC
// E = A + B + C - PI = 4 * PI * AreaOfTriangle / AreaOfSphere
// tan(E/2) = (tan(a/2)*tan(b/2)*sinC) / (1 + tan(a/2)*tan(b/2)*cosC);
double Area(Point3 o, double R, Point3 p){
  return 2*PI*R*R*(1 - R/(p - o).Len());
}
double gao(Point3 o, double R, Point3 A, Point3 B){
  double a = acos(R / (A - o).Len());
  double c = acos(R / (B - o).Len());
  Point3 nA = o + (A - o)/(A - o).Len()*R,
         nB = o + (B - o)/(B - o).Len()*R;
  double l = (nA - nB).Len();
  double b = acos((2*R*R - l*l) / (2*R*R));
  
  double aR = a*R, bR = c*R, dist = b*R;
  double s1 = Area(o, R, A), s2 = Area(o, R, B);
  if(dcmp(dist - aR - bR) >= 0)  return 0; // out
  else if(dcmp(dist + aR - bR) <= 0 || dcmp(dist + bR - aR) <= 0){ // contain
    return min(s1, s2) / 2;
  }

  double C = (cos(c) - cos(a)*cos(b)) / (sin(a)*sin(b));
  C = acos(C);
  C = 2*C;
  double E = (tan(a/2)*tan(a/2)*sin(C)) / (1 + tan(a/2)*tan(a/2)*cos(C));
  E = atan(E);
  E = 2*E;
  double tri = E*R*R;
  double shan = Area(o, R, A) * C / (2*PI);
  return shan - tri;
}


//UVA 11275 test, TriTriIntersection, TriSegIntersection, PointInTri
//hdu 4714 test, LineDistance3D
int main(){
  Point3 A, B, C; Point3 o(0, 0, 0);double R;
  while(o.read(), scanf("%lf", &R) == 1){
    A.read(); B.read(); C.read();
    double s1 = Area(o, R, A), s2 = Area(o, R, B), s3 = Area(o, R, C);
    double ans = s1 + s2 + s3;

    ans -= gao(o, R, A, B) + gao(o, R, B, A)
         + gao(o, R, A, C) + gao(o, R, C, A)
         + gao(o, R, B, C) + gao(o, R, C, B);

    printf("%.6lf\n", 4*PI*R*R - ans );
  }
  return 0;
}
