/*************************************************************************
    > File Name: kdtree.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 五  5/ 9 23:52:06 2014
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

template<class T = double>
struct Point{
  vector<T> x;
  Point(){} Point(vector<T> x):x(x){}
  double Len(){
    double ans = 0;
    for(int i = 0; i < x.size(); i++) ans += x[i] * x[i];
    return sqrt(ans);
  }
  T operator[](const int& p)const{ return x[p]; }
  Point operator-(const Point& p)const { 
    vector<T> v = x;
    for(int i = 0; i < x.size(); i++){
      v[i] -= p[i];
    }
    return Point(v);
  }
  void out(){
    for(int i = 0; i < x.size(); i++) cerr<<x[i]<<" "; cerr<<endl;
  }
};


template<class T = double>
struct Node{
  Point<T> p;// 分割点
  int k; T v; // 法向量第几维度 和 数值
  int l, r; // 左儿子 右儿子
  Node(){}
  Node(Point<T> p, int k, T v, int l, int r):p(p), k(k), v(v), l(l), r(r){}
};

const int maxn = 1111;
Point<double> lx[maxn];

Node<double> Ne[maxn];
int E = 0, K = 2;

int cmpk = 0;
bool cmp(Point<> a, Point<> b){
  return a[cmpk] < b[cmpk];
}



// E = 0, first
void build(int& rt, int l, int r, int k){//当前根节点，左区间l，右区间r，选取k维度分割
  if(l > r) return;
  cmpk = k;
  sort(lx + l, lx + r + 1, cmp);
  int m = (l + r) >> 1;
  rt = E++;
  Ne[rt] = Node<double>(lx[m], k, lx[m][k], -1, -1);
  build(Ne[rt].l, l, m - 1, (k + 1) % K);
  build(Ne[rt].r, m + 1, r, (k + 1) % K);

  Ne[rt].p.out();
  cerr<<"left son = ";Ne[Ne[rt].l].p.out();
  cerr<<"right son = ";Ne[Ne[rt].r].p.out();
  cerr<<"---------------------------------"<<endl;
}

double minv;
// minv = inf, first
void dfs(int rt, Point<double> p){
  if(rt == -1) return;
  int k = Ne[rt].k;

  if(Ne[rt].p[k] > p[k]){ // fit left
    dfs(Ne[rt].l, p);
    if(fabs(Ne[rt].v - p[k]) < minv - eps){// 满足超越半平面，往另外一个孩子递归
      dfs(Ne[rt].r, p);
    }
  }else {// fit right
    dfs(Ne[rt].r, p);
    if(fabs(Ne[rt].v - p[k]) < minv - eps){// 满足超越半平面，往另外一个孩子递归
      dfs(Ne[rt].l, p);
    }
  }
  minv = min(minv, (p - Ne[rt].p).Len());
//输出检查dfs路径
  Ne[rt].p.out();
  cerr<<" minv = "<<minv<<endl;
}



double d[6][2] = {2, 3, 5, 4, 9, 6, 4, 7, 8, 1, 7, 2};
int main(){
  K = 2;
  for(int i = 0; i < 6; i++){
    vector<double> v; v.push_back(d[i][0]), v.push_back(d[i][1]);
    lx[i] = Point<double>(v);
  }
  
  int root; E = 0;
  build(root, 0, 5, 0); 
  
  double vx, vy;
  printf("Please input x y:\n");
  while(scanf("%lf%lf", &vx, &vy) == 2){
    minv = 1e99;
    vector<double> v; v.push_back(vx), v.push_back(vy);
    dfs(root, Point<double>(v));
    printf("\nminimal distance = %.4lf\n", minv);
  }
  return 0;
}
