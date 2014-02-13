/*************************************************************************
  > File Name: KSets.cpp
  > Author: implus
  > Mail: 674592809@qq.com
  > Created Time: 四  2/13 17:34:55 2014
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

const int maxn = 111111;
ll a[maxn];
map<ll,int> mp;
int main(){
  int n,k;
  while(scanf("%d%d", &n, &k) == 2){
    mp.clear();
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]), mp[a[i]]++;
    sort(a,a+n);

    if(k == 1){
      printf("%d\n", (int)mp.size()); continue;
    }
    set<ll> s;
    int ans = 0;
    for(int i = 0; i < n; i++)if(s.find(a[i]) == s.end()){
      vector<int> v;
      ll p = a[i];
      while(s.insert(p), v.push_back(mp[p]), 
          mp.find(p*k) != mp.end()) p = p * k; 
      if(v.size() == 1){
        ans += v[0]; continue;
      }
      vector<int> dp(v.size());
      dp[0] = v[0];
      dp[1] = max(v[1], v[0]);
      for(int i = 2; i < dp.size(); i++){
        dp[i] = max(dp[i - 1], v[i] + dp[i - 2]); 
      }
      ans += *max_element(dp.begin(), dp.end());
    }
    printf("%d\n", ans);
  }
  return 0;
}
