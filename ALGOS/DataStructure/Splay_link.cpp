/*************************************************************************
    > File Name: t.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 五  3/ 7 14:57:10 2014
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
const int inf = 1<<30;
const int maxn = 111111;
int n, m, x, y, D;
int a[maxn];
char cmd[22];
#define KV (root->ch[1]->ch[0])
//http://poj.org/problem?id=3580
struct Splay_link{
  struct Node{
    Node* ch[2];
    int val, sz, mi, rev, add;
    Node(){}
    Node(Node* l, Node* r, int val, int sz, int mi, int rev, int add):val(val), sz(sz), mi(mi), rev(rev), add(add){
      ch[0] = l; ch[1] = r; 
    }
    void up(){
      sz = 1; mi = val;
      if(ch[0]) sz += ch[0]->sz, mi = ::min(mi, ch[0]->mi);
      if(ch[1]) sz += ch[1]->sz, mi = ::min(mi, ch[1]->mi);
    }
    void down(){
      if(rev){
        swap(ch[0], ch[1]);
        if(ch[0]) ch[0]->rev ^= 1;
        if(ch[1]) ch[1]->rev ^= 1;
        rev = 0;
      }
      if(add){
        if(ch[0]) ch[0]->val += add, ch[0]->mi += add, ch[0]->add += add;
        if(ch[1]) ch[1]->val += add, ch[1]->mi += add, ch[1]->add += add;
        add = 0;
      }
    }
  };
  Node* root;
  void build(Node*& x, int l, int r){
    if(l > r) return;
    int m = (l + r) >> 1;
    x = new Node(NULL, NULL, a[m], 1, a[m], 0, 0);
    build(x->ch[0], l, m - 1);
    build(x->ch[1], m + 1, r);
    x->up();
  }
  void init(int n){
    Node *p = new Node(NULL, NULL, inf, 1, inf, 0, 0); 
    root = new Node(NULL, p, inf, 2, inf, 0, 0);
    build(KV, 1, n);
    root->ch[1]->up();
    root->up();
  }
  void rotate(Node*& o, int d){
    Node* x = o->ch[d ^ 1];
    o->down(); x->down();
    o->ch[d ^ 1] = x->ch[d];
    x->ch[d] = o;
    o->up(); x->up();
    o = x;
  }
  void splay(Node*& o, int k){// kth to o
    o->down();
    int ol = size(o->ch[0]);
    if(ol == k) return;
    int x = (ol < k); k -= x * (ol + 1);
    splay(o->ch[x], k);
    rotate(o, x ^ 1);
  }
  /*
  void splay(Node*& o, int k){
    o->down();
    int ol = size(o->ch[0]);
    if(ol == k) return;
    int x = (ol < k); k -= x * (ol + 1);

    o->ch[x]->down();
    int xl = size(o->ch[x]->ch[0]);
    if(xl != k) {
      int y = (xl < k); k -= y * (xl + 1);
      splay(o->ch[x]->ch[y], k);
      if(y == x) rotate(o, x ^ 1); else rotate(o->ch[x], y ^ 1);
    }
    rotate(o, x ^ 1);
  }
  */
  int size(Node* p){
    return (p == NULL) ? 0: p->sz;
  }
  void getS(int l, int r){
    splay(root, l - 1);
    splay(root->ch[1], r - size(root->ch[0]));// KV is ok
  }
  void add(int l, int r, int D){
    getS(l, r);
    KV->val += D;
    KV->mi += D;
    KV->add += D;
  }
  void reverse(int l, int r){
    getS(l, r);
    KV->rev ^= 1;
  }
  void cut(int l, int r, int k){
    getS(l, r);
    Node* p = KV;
    KV = NULL;
    root->ch[1]->up();
    root->up();

    getS(k + 1, k);
    KV = p;
    root->ch[1]->up();
    root->up();
  }
  void revolve(int l, int r, int T){
    T = T % (r - l + 1);
    if(T == 0) return;
    // move [l, r - T] to T + l - 1's after
    cut(l, r - T, T + l - 1);
  }
  void insert(int x, int P){
    getS(x + 1, x);
    Node* p = new Node(NULL, NULL, P, 1, P, 0, 0);
    KV = p;
    root->ch[1]->up();
    root->up();
  }
  void erase(int x){
    getS(x, x);
    queue<Node*> q;
    q.push(KV);
    while(q.size()){
      Node* p = q.front(); q.pop();
      if(p->ch[0]) q.push(p->ch[0]);
      if(p->ch[1]) q.push(p->ch[1]);
      delete p;
    }
    KV = NULL;
    root->ch[1]->up();
    root->up();
  }
  int min(int l, int r){
    getS(l, r);
    return KV->mi;
  }
}lx;

int main(){
  while(scanf("%d", &n) == 1){
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    lx.init(n);
    while(m--){
      scanf("%s", cmd);
      string cm = cmd;
      if(cm == "ADD"){
        scanf("%d%d%d", &x, &y, &D);
        lx.add(x, y, D);
      }else if(cm == "REVERSE"){
        scanf("%d%d", &x, &y);
        lx.reverse(x, y);
      }else if(cm == "REVOLVE"){
        scanf("%d%d%d", &x, &y, &D);
        lx.revolve(x, y, D);
      }else if(cm == "INSERT"){
        scanf("%d%d", &x, &D);
        lx.insert(x, D);
      }else if(cm == "DELETE"){
        scanf("%d", &x);
        lx.erase(x);
      }else if(cm == "MIN"){
        scanf("%d%d", &x, &y);
        printf("%d\n", lx.min(x, y));
      }
    }
  }
  return 0;
}

