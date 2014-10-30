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
using namespace std;
typedef long long lint;


const int maxn = 250005;
const int sigma_size = 26;
const int maxs = maxn<<1;

struct SAM{
	int sz, lastp;
	struct State{
		int mx, pa, pos;
		int go[sigma_size];
		State(){}
		Staet(int mx, int pa, int pos):mx(mx), pa(pa), pos(pos){
			memset(go, 0, sizeof(go));
		}
	}v[maxs];
	int num[maxs], f[maxs];

	void init(){
		sz = 0;
		v[lastp = sz++] = State(0, -1);
	}

	int idx(char c){
		return c - 'a';
	}

	void add(int x, int pos){
		int p, nq;
		v[p = sz++] = State(v[lastp].mx + 1, 0, pos);

		int s = lastp;
		while(~s && v[s].go[x] == 0){
			v[s].go[x] = p, s = v[s].pa;
		}
		if(s != -1){
			int q = v[s].go[x];
			if(v[q].mx == v[s].mx + 1){
				v[p].pa = q;
			}else{
				v[nq = sz++] = State(v[s].mx + 1, v[q].pa, v[q].pos);
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
		for(int i = 0; i < n; i++){
			add(idx(ch[i]), i + 1);
		}
	}

	int d[maxn], so[maxs];
	lint cnt[maxs];
	void get(int maxlen){
		fill(d, d + maxlen + 1, 0);
		for(int i =0 ; i < sz; i++) d[v[i].mx]++;
		for(int i = 1; i <= maxlen; i++) d[i] += d[i - 1];
		for(int i = 0; i < sz; i++) so[--d[v[i].mx]] = i;
		for(int i = 0; i < sz; i++) cnt[i] = 1;
		cnt[0] = 0;
		for(int i = sz - 1; i >= 0; i--){
			int s = so[i];
			for(int j = 0; j < sigma_size; j++){
				int ns = v[s].go[j];
				if(ns)
					cnt[s] += cnt[ns];
			}
		}
	}

/*
	int son[sigma_size], sp;
	pii gao(int s, lint k){
		if(k == 0){
			return pii(v[s].pos - len + 1, v[s].pos);
		}
		lint sum = 0; bool ok = 0;
		sp = 0;
		for(int i = 0; i < sigma_size; i++){
			int ns = v[s].go[i];
			if(ns){
				son[sp++] = ns;
			}
		}
		for(int i = 0; i < sp; i++){
			if(sum < k && sum + cnt[son[i]] >= k){
				return gao(son[i], len + 1, k - 1 - sum);
			}else sum += cnt[son[i]];
		}
		return pii(-1, -1);
	}
	*/
}

int main() {
	while(scanf("%s", &ch) == 1){
		scanf("%d", &q);
		
		for(int i = 0; i < q; i++){
			scanf("%lld", &v);
			k = 
		}
	}
	return 0;
}
