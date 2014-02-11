/*************************************************************************
    > File Name: GeoPolygon2D.h
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 日  1/ 5 15:02:14 2014
 ************************************************************************/

#include "GeoPoint2D.h"
using namespace std;

// Point && Polygon
struct Polygon{
  vector<Point> v;
  Polygon(){}
  Polygon(vector<Point> v):v(v){}
  Polygon(int n){v.resize(n);}
  Point& operator[](int x){ return v[x];}
  int size()const{ return v.size();}
  Point Center(){
    double sx = 0, sy = 0;int n = v.size();
    for(int i = 0; i < n; i++)
      sx += v[i].x, sy += v[i].y;
    return Point(sx / n, sy / n);
  }
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
    int i, t, n = v.size();
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    v.resize(n<<1);
    reverse_copy(v.begin(), v.begin() + n, v.begin() + n);
    vector<Point> p;
    for(i = 0; i < (n<<1); i++){
      while((t = p.size()) >= 2 && dcmp((p[t - 1] - p[t - 2])^(v[i] - p[t - 2])) <= 0)
        p.pop_back();
      p.push_back(v[i]);//cerr<<"add ";v[i].out();
    }
    t = unique(p.begin(), p.end()) - p.begin();
    p.resize(t - (t > 1));
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
};

bool IntersectionConvexHullConvexHull(Polygon& P, Polygon& Q){
  int i, j, n = P.size(), m = Q.size();
  if(m > 1)for(i = 0; i < n; i++){
    if(Q.Contain(P[i])) return true;
  }
  if(n > 1 && m > 1) for(i = 0; i < n; i++) for(j = 0; j < m; j++)
    if(IntersectionSegmentSegment(P[i], P[(i + 1)%n], Q[j], Q[(j + 1)%m], 1))
      return true;
  return false;
}

void RotateCaliperConvexHull(Polygon& P){

}

int sgn; Line f;
bool cmp(Point a, Point b){
  return sgn * f.Distance(a) < sgn * f.Distance(b);
}
double _RotateCaliper(Polygon& P, Polygon& Q){
  Po = P.Center(); Qo = Q.Center();
  f = Line(P[0], P[1] - P[0]);
  sgn = f.Where(Po) * f.Where(Qo);
  int p = max_element(Q.v.begin(),Q.v.end(),cmp) - Q.v.begin(), n = P.size(), m = Q.size();
  double ans = 1e99;
  for(int i = 0; i < n; i++){
    int ni = (i + 1)%n;
    f = Line(P[i], P[ni]);
    sgn = f.Where(Po) * f.Where(Qo);
    while(np = (p + 1)%m, cmp(Q[p], Q[np])) p = np;
    //gao 
    ans = min(ans, f.SegmentDistance(Q[p]));
    ans = min(ans, f.SegmentDistance(Q[np]));
  }
  return ans;
}
void RotateCaliperConvexHull(Polygon& P, Polygon& Q){
  double ans = 1e99;
  ans = min(ans, _RotateCaliper(P, Q));
  ans = min(ans, _RotateCaliper(Q, P));
  return ans;
}
