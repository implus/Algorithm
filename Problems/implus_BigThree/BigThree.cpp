/*************************************************************************
    > File Name: BigThree.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 日  2/16 16:21:34 2014
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

const int maxn = 100005;
ll dp[maxn];
int n, ask;
int v[maxn], c[maxn];
ll a, b;
bool cmpv(int a, int b){
  return dp[a] > dp[b];
}
int main(){
  while(scanf("%d%d",&n, &ask)== 2){
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
    for(int i = 0; i < n; i++) scanf("%d", &c[i]), c[i]++;
    while(ask--){
      fill(dp, dp + n + 2, -(1LL<<60));
      dp[0] = 0;
      int sa[4] = {0};
      scanf("%lld%lld", &a, &b);
      for(int i = 0; i < n; i++){
        ll nv = dp[c[i]] + a*v[i];
        for(int j = -1; j <= 1; j++)
          nv = max(nv, dp[c[i] + j] + a*v[i]);
        for(int j = 0; j < 4; j++){
          if(sa[j] > c[i] + 1 || sa[j] < c[i] - 1) nv = max(nv, dp[sa[j]] + b*v[i]);
        }
        dp[c[i]] = max(dp[c[i]], nv);
        int t = c[i];
        if(t == sa[0] || t == sa[1] || t == sa[2] || t == sa[3]){
          sort(sa, sa + 4, cmpv);
          //for(int j = 0; j < 4; j++) cerr<<sa[j]<<" dp = "<<dp[sa[j]]<<endl;
        }else {
          for(int j = 0; j < 4; j++){
            if(dp[t] > dp[sa[j]]) t^=sa[j]^=t^=sa[j];
          }
        }
      }
      printf("%lld\n", dp[sa[0]]);
    }
  }
  return 0;
}
