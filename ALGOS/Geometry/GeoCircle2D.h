/*************************************************************************
    > File Name: GeoCircle2D.h
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 日  1/ 5 14:58:17 2014
 ************************************************************************/

#include "GeoPoint2D.h"
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
    if(dcmp(d - r) > 0)return ans;
    Point p = L.Projection(c);
    if(dcmp(d - r) == 0)return ans.push_back(p),ans;
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

