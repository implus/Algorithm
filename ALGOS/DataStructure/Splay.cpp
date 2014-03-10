/*************************************************************************
    > File Name: Splay.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 四  3/ 6 20:55:57 2014
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
#include<cassert>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

#define KV (son[ son[root][1] ][0])
#define ls (son[x][0])
#define rs (son[x][1])
const int inf = 1<<30;
const int maxn = 3e5 + 5;
int num[maxn];

bool ok = 1;
struct SplayTree{
  int root, tot;
  int sz[maxn], son[maxn][2], pre[maxn];
  int ss[maxn], que[maxn], top2;// memory limits add
  int val[maxn], mi[maxn], add[maxn], rev[maxn];
  inline void rotate(int x, int d){// d==1 for toRight
    int nx = son[x][d ^ 1], fx = pre[x];
    down(x), down(nx);
    son[x][d ^ 1] = son[nx][d]; pre[son[nx][d]] = x;
    son[nx][d] = x; pre[x] = nx;
    son[fx][x == son[fx][1]] = nx; pre[nx] = fx;
    up(x); //up(nx);
  }
  inline void splay(int x, int goal){//move x to goal's son
    down(x); int y, z, dy, dz;
    while(y = pre[x], dy = (x == son[y][0]), y != goal){
      if(pre[y] == goal){ rotate(y, dy); break; }
      z = pre[y]; dz = (y == son[z][0]);
      if(dz == dy) rotate(z, dz), rotate(y, dy);
      else rotate(y, dy), rotate(z, dz);
    }
    up(x); if(goal == 0) root = x;
  }
  inline void getK(int k, int goal){// move kth to goal's son
    int x = root; down(x);
    while(sz[ls] != k){// inf is the added one
      if(k < sz[ls]) x = ls;  
      else k -= (sz[ls] + 1), x = rs;
      down(x);
    }
    splay(x, goal);
  }
  inline int getS(int l, int r){// get [l, r]'s segment
    getK(l - 1, 0);
    getK(r + 1, root);
    return KV;
  }
  inline void erase(int x){
    int fx = pre[x], l = 0, r = 0, bx = x;
    for(que[r++] = x; l < r; l++){
      x = ss[top2++] = que[l];     
      if(ls) que[r++] = ls;
      if(rs) que[r++] = rs;
    }
    son[fx][son[fx][1] == bx] = 0;
    up(fx);
  }
  void debug(){ printf("%d\n", root); debug(root); }
  void debug(int x){
    if(x == 0) return;
    debug(ls);
    printf("Node %2d ls: %2d rs: %2d fa: %2d size = %2d, val = %2d, mi = %2d\n", x, ls, rs, pre[x], sz[x], val[x], mi[x]);
    debug(rs);
  }

  inline void newNode(int &x, int c, int fa){
    x = ++tot;
    ls = rs = 0;  pre[x] = fa;
    rev[x] = 0; val[x] = c; 
  }
  inline void init(int n){
    root = tot = 0;
    //son[root][0] = son[root][1] = pre[root] = rev[root] = sz[root] = 0;
    newNode(root, inf, 0);
    newNode(son[root][1], inf, root);
    //for(int i = 1; i <= n; i++) scanf("%d", &num[i]);
    build(KV, 1, n, son[root][1]);
    up(son[root][1]);
    up(root);
  }
  inline void build(int &x, int l, int r, int fa){
    if(l > r) return;
    int m = (l + r) >> 1;
    newNode(x, m, fa);
    build(ls, l, m - 1, x);
    build(rs, m + 1, r, x);
    up(x);
  }
  inline void down(int x){
    if(rev[x]){
      rev[ls] ^= 1;
      rev[rs] ^= 1;
      swap(ls, rs);
      rev[x] = 0;
    }
  }
  inline void up(int x){
     sz[x] = 1 + sz[ls] + sz[rs];
  }
  int cut(int l, int r){// cut [l, r] from root
    int x = getS(l, r);
    pre[x] = 0;
    KV = 0;
    up(son[root][1]); 
    up(root);
    return x;
  }
  void merge(int p, int o){// merge o to p'th after 
    int x = getS(p + 1, p);
    pre[o] = son[root][1];
    KV = o;
    up(son[root][1]);
    up(root);
  }
  void CUT(int l, int r, int p){
    int x = cut(l, r);
    merge(p, x);
  }
  void reverse(int l, int r){
    int x = getS(l, r);
    rev[x] ^= 1;   
  }
  int first;
  void out(int x){
    if(x == 0) return;
    down(x);
    if(ls) out(ls);

    if(val[x] != inf){
      if(first) first = 0;
      else printf(" ");
      printf("%d", val[x]);
    }

    if(rs) out(rs);
  }
  void print(int n){
    first = 1;
    out(root);puts("");
  }
}lx;

int n, m, a, b, c;
char cmd[22];
int main(){
  while(scanf("%d%d", &n, &m) == 2){
    if(n == -1 && m == -1) break;
    lx.init(n);
    for(int i = 0; i < m; i++){
      scanf("%s", cmd);
      if(cmd[0] == 'C'){
        scanf("%d%d%d", &a, &b, &c);
        lx.CUT(a, b, c);
        //lx.print(n);
      }else{
        scanf("%d%d", &a, &b);
        lx.reverse(a, b);
        //lx.print(n);
      }
    }
    lx.print(n);
  }
  return 0;
}


