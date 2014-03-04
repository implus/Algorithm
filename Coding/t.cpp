/*************************************************************************
    > File Name: t.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 二  3/ 4 20:53:33 2014
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

vector<int> gao(vector<int> a){
  vector<int> dp(a.size(), 1);
  dp[1] = 1;
  for(int i = 2; i < a.size(); i++){
    if(a[i] > a[i - 1]) dp[i] = dp[i - 1] + 1; 
    else dp[i] = 1;
  }
  for(int i = 1; i < a.size(); i++) cerr<<dp[i]<<" ";cerr<<endl;
  return dp;
}
int n;
int main(){
  while(scanf("%d", &n) == 1){
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    vector<int> b = gao(a);
    reverse(a.begin() + 1, a.end());
    vector<int> c = gao(a);
    reverse(c.begin() + 1, c.end());
    ll ans = 0;
    for(int i = 1; i <= n; i++) ans += max(b[i], c[i]);
    printf("%lld\n", ans);
  }
  return 0;
}
