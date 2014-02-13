/*************************************************************************
    > File Name: c.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 三 12/25 06:49:45 2013
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
    while(cin>>n>>k){
        for(int i = 0; i < n; i++)cin>>a[i];
        sort(a,a+n);

        mp.clear();
        for(int i = 0; i < n; i++){
            int j = i;
            while(j < n && a[j] == a[i])j++;
            mp[a[i]] = j - i;
            i = j - 1;
        }
        if(k == 1){
            cout<<mp.size()<<endl;continue;
        }
        set<ll> s;
        int ans = 0;
        for(int i = 0; i < n; i++)if(s.find(a[i]) == s.end()){
            ll p = a[i];
            s.insert(p);
            int cnt[2] = {0}; cnt[0] = mp[p];
            int turn = 0;
            while(mp.find(p*k)!=mp.end()){
                p *= k;
                turn ^= 1;
                cnt[turn] += mp[p];
                s.insert(p);
            }
            ans += max(cnt[0],cnt[1]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
