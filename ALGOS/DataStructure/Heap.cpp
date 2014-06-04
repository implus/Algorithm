/*************************************************************************
    > File Name: Heap.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 二  6/ 3 17:12:19 2014
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

template<class T = long long>
struct HEAP {
	vector <T> heap;

	void init() {
		heap.clear();
		make_heap(heap.begin(), heap.end());
		heap.push_back(-1);
		push_heap(heap.begin(), heap.end());
	}

	T getMax() {
		long long t = heap[0];
		if(t < 0) return T(0);
		pop_heap(heap.begin(), heap.end());
		heap.pop_back();
		return t;
	}

	void add(T x) {
		heap.push_back(x);
		push_heap(heap.begin(), heap.end());
	}

	/*  Note
		1. Assume all elements are positive
		2. return 0 if it is empty
	*/

	/*  Eaxmple
		init();
		add(2);
		add(3);
		cout << getMax() << endl;
		cout << getMax() << endl;
		cout << getMax() << endl;
	*/
};



/*
struct HEAP{
    vector<int> a; int n;
    void init(int n){
        a.resize(n + 1, 0);
        this->n = 0;
    }

    void up(int p){
        if(p == 1) return;
        int f = p / 2;
        if(a[f] > a[p]) {
            swap(a[f], a[p]);
            up(f);
        }
    }

    void down(int p){
        int l = p * 2, r = p * 2 + 1;
        if(l > n) return;
        if(r > n) {
            if(a[p] > a[l])
                swap(a[p], a[l]), down(l);
        }else {
            int w = (a[l] < a[r]) ? l: r;
            if(a[p] > a[w])
                swap(a[w], a[p]), down(w);
        }
    }

    void add(int x){
        n++; a[n] = x;
        up(n);
    }

    int pop(){// n >= 1;
        int ans = a[1];
        swap(a[1], a[n]); n--;
        down(1);
        return ans;
    }

    int size(){
        return n;
    }

    void out(){
        for(int i = 1; i <= n; i++) cerr<<a[i]<<" "; cerr<<endl;
    }
}lx;*/

//http://poj.org/problem?id=3253
