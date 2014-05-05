#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<string>
using namespace std;
const int maxn = 55555;
int T, N, M;
char str[maxn]; string s;
#define ls (son[x][0])
#define rs (son[x][1])
#define KV (son[son[root][1]][0])

struct Splay {
  int son[maxn][2], sz[maxn], sum[maxn], mil[maxn], mir[maxn], mal[maxn], mar[maxn], v[maxn];
  int rep[maxn], rev[maxn], inv[maxn];
  int root, tot;
  void newNode(int& x, int val) { 
    x = ++tot;
    son[x][0] = son[x][1] = 0; sz[x] = 1; sum[x] = v[x] = val;
    mil[x] = mir[x] = min(0, val);
    mal[x] = mar[x] = max(0, val);
    rep[x] = rev[x] = inv[x] = 0;
  }
  void build(int& x, int l, int r) {
    if(l > r) return;
    int m = (l + r) >> 1;
    newNode(x, s[m] == '(' ? 1: -1);
    build(ls, l, m - 1);
    build(rs, m + 1, r);
    up(x);
  }
  void init(int n) {
    root = tot = 0;
    newNode(root, 0);
    newNode(son[root][1], 0);
    build(KV, 1, n);
    up(son[root][1]);
    up(root);
  }
  void up(int x) {
    sz[x] = 1 + sz[ls] + sz[rs];
    sum[x] = sum[ls] + v[x] + sum[rs];
    mil[x] = min(mil[ls], sum[ls] + v[x] + mil[rs]);
    mir[x] = min(mir[rs], sum[rs] + v[x] + mir[ls]);
    mal[x] = max(mal[ls], sum[ls] + v[x] + mal[rs]);
    mar[x] = max(mar[rs], sum[rs] + v[x] + mar[ls]);
  }
  // 在该区间打上标记，并把该区间所维护的值更新为代表 mark and fit
  // 问题转化为对于一个区间的值(其他标记也是要维护的值)，标记的影响对其的维护,以及多标记之间的影响是否为O（1）若是则可用区间方法
  void repx(int x, int c) {
    rep[x] = c;
    sum[x] = c * sz[x]; v[x] = c;
    mil[x] = mir[x] = min(0, sum[x]);
    mal[x] = mar[x] = max(0, sum[x]);

    rev[x] = inv[x] = 0;
  }
  void revx(int x) {
    rev[x] ^= 1;
    swap(mil[x], mir[x]);
    swap(mal[x], mar[x]);
  }
  void invx(int x) {
    inv[x] ^= 1;
    swap(mil[x], mal[x]); mil[x]=-mil[x]; mal[x]=-mal[x];
    swap(mir[x], mar[x]); mir[x]=-mir[x]; mar[x]=-mar[x];
    sum[x] = -sum[x]; v[x] = -v[x];
  }
  void down(int x) { 
    if(rep[x]) {
      int c = rep[x];
      repx(ls, c); repx(rs, c);
      rep[x] = 0;
      //return;
    }
    if(rev[x]) {
      revx(ls); revx(rs);
      swap(ls, rs);
      rev[x] = 0;
    }
    if(inv[x]) {
      invx(ls); invx(rs);
      inv[x] = 0;
    }
  }
  void rotate(int& x, int d) {// d==1 roright
    int y = son[x][d ^ 1];
    down(x), down(y);
    son[x][d ^ 1] = son[y][d];
    son[y][d] = x;
    up(x), up(y);
    x = y;
  }
  /*
  void splay(int& x, int k){
    down(x);
    if(sz[ls] == k) return;
    int d = (sz[ls] < k); k -= d * (sz[ls] + 1);
    
    down(son[x][d]);
    int xl = sz[son[son[x][d]][0]];
    if(xl != k){
      int y = (xl < k); k -= y * (xl + 1);
      splay(son[son[x][d]][y], k);
      if(y == d) rotate(x, d ^ 1); else rotate(son[x][d], y ^ 1);
    }
    rotate(x, d ^ 1);
  }*/
  void splay(int& x, int k) {
    down(x);
    if(sz[ls] == k) return;
    int d = (sz[ls] < k); 
    splay(son[x][d], k - d * (sz[ls] + 1));
    rotate(x, d ^ 1);
  }
  void getS(int l, int r) {
    splay(root, l - 1);
    splay(son[root][1], r - sz[son[root][0]]);
  }
  void replace(int l, int r, int c) {
    getS(l, r);
    repx(KV, c);
  }
  void reverse(int l, int r) {
    getS(l, r);
    revx(KV);
  }
  void invert(int l, int r) {
    getS(l, r);
    invx(KV);
  }
  int query(int l, int r) {
    getS(l, r);
    int y = sum[KV], x = mil[KV];
    return (abs(x) + 1) / 2 + (y - x + 1) / 2;
  }
}lx;

int main(){
  scanf("%d", &T); int icase = 1;
  while(T--) {
    printf("Case %d:\n", icase++);
    scanf("%d%d%s", &N, &M, str);
    s = str; s = "0" + s;
    lx.init(N);
    char cmd[22];int l, r; char c;
    while(M--){
      scanf("%s%d%d", cmd, &l, &r);
      if(cmd[0] == 'R') {
        scanf(" %c", &c);
        lx.replace(l, r, c == '(' ? 1: -1);
      }else if(cmd[0] == 'S') {
        lx.reverse(l, r);
      }else if(cmd[0] == 'I') {
        lx.invert(l, r);
      }else {
        printf("%d\n", lx.query(l, r));
      }
    }
  }
  return 0;
}

