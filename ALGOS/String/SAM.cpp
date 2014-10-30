#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
using namespace std;
typedef long long lint;
typedef pair<int, int> pii;

const int maxn = 250005;// string length
const int sigma_size = 26;
const int maxs = maxn << 1;
struct SAM{
	int sz, lastp;
	struct State{
		int mx, pa;
		int go[sigma_size];
		State(){}
		State(int mx, int pa):mx(mx), pa(pa){ 
			memset(go, 0, sizeof(go));
		}
	}v[maxs];
	int num[maxs], f[maxs];

	void init(){
		sz = 0;
		v[lastp = sz++] = State(0, -1);
		fill(num, num + maxs, 0);
	}
	
	int idx(char c){
		return c - 'a';
	}
	void add(int x){
		int p, nq;
		v[p = sz++] = State(v[lastp].mx + 1, 0);
		num[p] = 1;

		int s = lastp;
		while(~s && v[s].go[x] == 0){
			v[s].go[x] = p, s = v[s].pa;
		}

		if(s != -1){
			int q = v[s].go[x];
			if(v[q].mx == v[s].mx + 1){ // fit
				v[p].pa = q;
			}else{
				v[nq = sz++] = State(v[s].mx + 1, v[q].pa);
				memcpy(v[nq].go, v[q].go, sizeof v[q].go);
				v[q].pa = v[p].pa = nq;
				while(~s && v[s].go[x] == q){
					v[s].go[x] = nq, s = v[s].pa;
				}
			}
		}
		lastp = p;
	}

	void gen(char * ch, int n){
		init();
		for(int i = 0; i < n; i++)
			add(idx(ch[i]));
	}

// get one string appear times, before some s, num[s] = 1
	void gaoNum(){
		queue<int> q;
		vector<int> deg(sz + 1, 0);
		for(int i = 1; i < sz; i++) deg[v[i].pa]++;
		for(int i = 1; i < sz; i++) if(deg[i] == 0) q.push(i);
		while(q.size()){
			int s = q.front(); q.pop();
			if(s == 0) continue; // pa == -1 not legal
			num[v[s].pa] += num[s];
			if(--deg[v[s].pa] == 0) q.push(v[s].pa);
		}
	}

// B match A's SAM status, return maxLength common substring
	int gao(char * B, int n){
		int ans = 0, s = 0, len = 0;
		for(int i = 0; i < n; i++){
			int x = idx(B[i]);
			if(v[s].go[x]){
				s = v[s].go[x];
				len++;
			}else{
				while(~s && v[s].go[x] == 0) s = v[s].pa;
				if(~s && v[s].go[x]) len = v[s].mx + 1, s = v[s].go[x];
				else s = 0, len = 0;
			}
			ans = max(len, ans);
		}
		return ans;
	}

// different type of substring way 1:
	int d[maxn], so[maxs], cnt[maxs];
	int get(int maxlen){
		fill(d, d + maxlen + 1, 0);
		for(int i = 0; i < sz; i++) d[v[i].mx]++;
		for(int i = 1; i <= maxlen; i++) d[i] += d[i - 1];
		for(int i = 0; i < sz; i++) so[--d[v[i].mx]] = i;
		for(int i = 0; i < sz; i++) cnt[i] = 1;

		for(int i = sz - 1; i >= 0; i--){
			int s = so[i];
			for(int j = 0; j < sigma_size; j++){
				int ns = v[s].go[j];
				if(ns) {
					cnt[s] += cnt[ns];
				}
			}
		}
		return cnt[0];
	}

// different type of substring way 2:
	int get2(){
		int sum = 0;
		for(int i = 1; i < sz; i++){
			sum += v[i].mx - v[v[i].pa].mx;
		}
		return sum;
	}


	void gao(int n){
		gaoNum();
		fill(f, f + maxs, 0);
		for(int s = 0; s < sz; s++)
			f[v[s].mx] = max(f[v[s].mx], num[s]);

		for(int i = n - 1; i > 0; i--){
			f[i] = max(f[i], f[i + 1]);
		}
		for(int i = 1; i <= n; i++){
			printf("%d\n", f[i]);
		}
	}

// 10 strings common substring (len 100000)
// in init():
// fill(dp[0], dp[maxs], 0), fill(cnt[0], cnt[maxs], 0);
// use int d[maxn], so[maxs];
    int dp[maxs][10], cnt[maxs][10];
	void chGoInSAMwithID(char * ch, int n, int id){//id from 1 ~ 9
        int s = 0, mx = 0;
        for(int i = 0; i < n; i++){
            int x = idx(ch[i]);
            if(v[s].go[x]){
                mx++;
                s = v[s].go[x];
            }else {
                while(~s && v[s].go[x] == 0) s = v[s].pa;
                if(s != -1){
                    mx = v[s].mx + 1;
                    s = v[s].go[x];
                }else s = mx = 0;
            }
            if(s){
                dp[s][id] = max(dp[s][id], mx); // id string has mx match length in state s
            	cnt[s][id] = 1;					
            }
        }
    }
	int ncommonSubstring(int n){ 
		int ans = 0;
		fill(d, d + maxn, 0);
		for(int i = 0; i < sz; i++) d[v[i].mx]++;
		for(int i = 1; i < maxn; i++) d[i] += d[i - 1];
		for(int i = 0; i < sz; i++) so[--d[v[i].mx]] = i;

		//for(int i = 0; i < sz; i++) cerr<<"dp["<<i<<"] = "<<dp[i]<<" ";cerr<<endl;

		for(int i = sz - 1; i > 0; i--){
			int s = so[i];
			//cerr<<"s = "<<s<<" v[s].mx = "<<v[s].mx<<endl;
			int ps = v[s].pa;
			int c = 0, mi = v[s].mx;
			for(int j = 1; j < n; j++){
				c += (cnt[s][j] > 0);
				mi = min(mi, dp[s][j]);
				if(dp[s][j] > v[ps].mx){
					dp[ps][j] = dp[s][j];
					cnt[ps][j]++;
				}
			}
			if(c == n - 1) ans = max(ans, mi);
		}
		return ans;
	}
	

// topo dp: sigma_size == 11, make 101 -> 101, 1, 10,... get sum 112 == ans
	int dp[maxs], cnt[maxs];
	//int d[maxn], so[maxs];
	int gao(){
		fill(dp, dp + sz, 0);
		fill(cnt, cnt + sz, 0);
		fill(d, d + maxn, 0);
		for(int i = 0; i < sz; i++) d[v[i].mx]++;
		for(int i = 1; i < maxn; i++) d[i] += d[i - 1];
		for(int i = 0; i < sz; i++) so[--d[v[i].mx]] = i;
		
		int ans = 0; cnt[0] = 1;
		for(int i = 0; i < sz; i++){// topo according to mx small to big
			int s = so[i];
			if(cnt[s] == 0)continue;// topo, no use State
			ans += dp[s];
			ans %= MOD;
			int st = (s ? 0: 1);
			for(int j = st; j < sigma_size - 1; j++){
				int ns = v[s].go[j];
				if(ns){
					cnt[ns] += cnt[s];
					dp[ns] += dp[s] * 10 + cnt[s] % MOD * j;
					dp[ns] %= MOD;
				}
			}
		}
		return ans;
	}

}g;

char ch[maxn];
int main() {
	//ios_base::sync_with_stdio(false);
	while(scanf("%s", ch) == 1){
		int n = strlen(ch);
		g.gen(ch, n);
		g.gao(n);
	}
	return 0;
}
