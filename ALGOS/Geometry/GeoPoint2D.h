/*************************************************************************
    > File Name: GeoPoint2D.h
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 日  1/ 5 14:56:00 2014
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

const double PI = acos(-1.0);
const double eps = 1e-8;

inline int dcmp(double x){
  if(fabs(x) < eps) return 0; return x < 0 ? -1: 1;
}

struct Point{
  double x,y;
  Point(double x=0, double y=0):x(x),y(y){}
  Point operator+(const Point& p)const{ return Point(x + p.x,y + p.y);}
  Point operator-(const Point& p)const{ return Point(x - p.x,y - p.y);}
  Point operator*(const double& p)const{ return Point(x*p,y*p);}
  double operator*(const Point& p)const{ return x*p.x + y*p.y;}//dot, v=a*b*cos(c)
  double operator^(const Point& p)const{ return x*p.y - y*p.x;}//x, abs=a*b*sin(c) 
  // a,b quadrangle_area = |a^b|
  // 3D: a,b,c parallelepiped_volume = a^b*c
  Point operator/(const double& p)const{ return Point(x/p,y/p);}
  Point Rotate(double rad){
    return Point(x*cos(rad) - y*sin(rad),x*sin(rad) + y*cos(rad));
  }
  Point Normal(){ double l = Len(); return Point(-y/l,x/l); }
  Point One(){ double l = Len(); return Point(x/l,y/l); }
  double Len(){ return sqrt((*this)*(*this));}
  double Area2(Point A,Point B,Point C){ return fabs((B-A)^(C-A));}
  bool operator < (const Point& p)const{
    return x < p.x || (dcmp(x - p.x) == 0 && y < p.y);
  }
  bool operator == (const Point& p){
    return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0;
  }
  void read(){ cin>>x>>y;}
  void out(){ cerr<<x<<","<<y<<endl;}
};
typedef Point Vector;

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
bool OnSegment(Point p, Point a1, Point a2){
  return dcmp((a1 - p)^(a2 - p)) == 0 && dcmp((a1 - p)*(a2 - p)) <= 0;// <=0 if in ends, <0 if not ends
}

// only one point, type == 0, not in ends; type == 1, in ends;
bool IntersectionSegmentSegment(Point a1, Point a2, Point b1, Point b2, int type = 0){
  double c1 = (a2 - a1)^(b1 - a1), c2 = (a2 - a1)^(b2 - a1),
         c3 = (b2 - b1)^(a1 - b1), c4 = (b2 - b1)^(a2 - b1);
  return (dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0) ||
  (type == 1 && (OnSegment(a1,b1,b2) || OnSegment(a2,b1,b2) || 
                 OnSegment(b1,a1,a2) || OnSegment(b2,a1,a2)));
}

double Area(vector<Point> p){// clockwise or anticlockwise
  double ans = 0; int n = p.size();
  for(int i = 1; i < n-1; i++)
    ans += (p[i] - p[0])^(p[i + 1] - p[0]);
  return fabs(ans/2);
}


struct Line{
  Point P; Vector v;
  Line(){}
  Line(Point P,Vector v):P(P),v(v){}
  int Where(Point Q){
    return dcmp(v^(Q - P));
  }
  double Distance(Point Q){
    return fabs(v^(Q - P))/v.Len();
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
};


