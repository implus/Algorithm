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

const int MAX_X = 101010;
const int MAX_N = 101010;
const int MAX_NODE = MAX_X << 9;

struct Tree{
	Tree * ls, * rs;
	int l, r;
	lint add, sum;
	Tree(){}
	Tree(int l, int r):l(l), r(r){
		ls = rs = NULL;
		add = sum = 0;
	}
	//void * operator new(size_t sz);
};

Tree node[MAX_NODE]; int nodeid = 0;
/*
void * Tree::operator new(size_t sz){
	return (void *) &node[nodeid++];
}*/

//init trashid = 0
Tree * build(int l, int r){
	node[nodeid] = Tree(l, r);
	Tree * ret = &node[nodeid++];
	if(r == l) return ret;
	int m = l + r >> 1;
	if(l <= m) ret->ls = build(l, m);
	if(r  > m) ret->rs = build(m + 1, r);
	return ret;
}

void down(Tree * rt, Tree* old){
	if(rt->add){
		node[nodeid] = *(old->ls);
		rt->ls = &node[nodeid++];

		node[nodeid] = *(old->rs);
		rt->rs = &node[nodeid++];

		rt->ls->add += rt->add, rt->ls->sum += rt->add * (rt->ls->r - rt->ls->l + 1);
		rt->rs->add += rt->add, rt->rs->sum += rt->add * (rt->rs->r - rt->rs->l + 1);
		rt->add = 0;
	}
}

void up(Tree * rt){
	rt->sum = rt->ls->sum + rt->rs->sum;
}

Tree * build(int L, int R, lint a, Tree * old){
	node[nodeid] = *old;
	Tree * ret = &node[nodeid++];
	int l = ret->l, r = ret->r;
	if(L <= l && r <= R){
		ret->add += a;
		ret->sum += a * (r - l + 1); 
		return ret;
	}
	down(ret, old);
	int m = l + r >> 1;
	if(L <= m) ret->ls = build(L, R, a, ret->ls);
	if(R  > m) ret->rs = build(L, R, a, ret->rs);
	up(ret);
}

lint query(int L, int R, Tree * rt){
	int l = rt->l, r = rt->r;
	if(L <= l && r <= R){
		return rt->sum;
	}
	down(rt, rt);
	int m = l + r >> 1;
	lint ans = 0;
	if(L <= m) ans += query(L, R, rt->ls);
	if(R >  m) ans += query(L, R, rt->rs);
	up(rt);
	return ans;
}

Tree * rt[MAX_N];

int main() {
	int T, N, id = 0, x, y, a, w, ty, M;
	nodeid = 0;
	scanf("%d%d", &N, &M);

	rt[id] = build(1, N);
	for(int i = 0; i < M; i++){
		scanf("%d", &ty);
		if(ty == 1){
			scanf("%d%d%d", &x, &y, &a);
			rt[id + 1] = build(x, y, a, rt[id]);
			id++;
		}else {
			scanf("%d%d%d", &w, &x, &y);
			printf("%lld\n", query(x, y, rt[w]));
		}
	}
	return 0;
}
