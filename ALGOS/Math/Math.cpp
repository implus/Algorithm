/*************************************************************************
    > File Name: Math.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 四  2/27 19:47:04 2014
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

#define product_mod(a, b, m) ((a * b) % m)
ll power_mod(ll a, ll m, ll n) {
	ll tmp = 1;
	a %= n;
	while (m != 0) {
		if (m & 1) tmp = product_mod(tmp, a, n);
		a = product_mod(a, a, n);
		m >>= 1;
	}
	return tmp;
}
ll base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
bool miller_rabin(ll n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (!(n & 1)) return false;
	ll k = 0, i, j, m, a;
	m = n - 1;
	while (!(m & 1)) m >>= 1, k++;
	for (i = 0; i < 10; i++) {
		if (base[i] >= n) return true;
		a = power_mod(base[i], m, n);
		if (a == 1) continue;
		for (j = 0; j < k; j++) {
			if (a == n - 1) break;
			a = product_mod(a, a, n);
		}
		if (j == k) return false;
	}
	return true;
}

