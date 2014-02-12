/*************************************************************************
    > File Name: Count.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 三  2/12 15:09:11 2014
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

const int maxn = 1e8;
struct BIT{
  map<int, ll> b, c;
  void init(){
    b.clear(); c.clear();
  }
  // sum[r] = b[1] ~ b[r] + c[r]*r
  // b[p] += v*p
  // c[1] ~ c[p - 1] += v
  void add(int p, ll v){
    for(int x = p; x < maxn; x += x&-x) b[x] += v*p;
    for(int x = p - 1; x; x -= x&-x) c[x] += v;
  }
  void add(int l, int r, ll v){
    add(r, v); if(l > 1) add(l - 1, -v);
  }
  ll sum(int p){
    ll ans = 0, v = 0;
    for(int x = p; x; x -= x&-x) ans += b[x];
    for(int x = p; x < maxn; x += x&-x) v += c[x];
    return ans + v * p;
  }
  ll sum(int l, int r){
    return sum(r) - ((l > 1) ? sum(l - 1): 0);
  }
}lx;
int main(){
  int n, l, r, x;
  while(scanf("%d",&n) == 1){
    lx.init();
    for(int i = 0; i < n; i++){
      scanf("%d%d", &l, &r);
      ll s = lx.sum(l, r);   
      printf("%lld\n", s);
      scanf("%d%d%d",&l, &r, &x);
      lx.add(l + s % 2014, r + s % 2014, (x + s) % 2014);
    }
  }
  return 0;
}
