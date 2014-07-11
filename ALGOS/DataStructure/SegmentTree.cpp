/*************************************************************************
    > File Name: SegmentTree.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 三  7/ 2 08:49:29 2014
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

struct Tree{
    Tree *pl, *pr;
    int l, r;
    int mx; ll sum;
    Tree(){}
    ~Tree(){
        if(pl) pl->~Tree();
        if(pr) pr->~Tree();
        delete this;
    }
    
    void update(){
        sum = pl->sum + pr->sum;
        mx = max(pl->mx, pr->mx);
    }

    Tree(int l, int r):l(l), r(r){
        if(l == r) {
            sum = mx = a[l];
            return;
        }
        int m = (l + r) >> 1;
        pl = new Tree(l, m);
        pr = new Tree(m + 1, r);
        update();
    }

    ll query(int L, int R){
        if(L <= l && r <= R) return sum;
        int m = (l + r) >> 1;
        ll ans = 0;
        if(L <= m) ans += pl->query(L, R);
        if(R >  m) ans += pr->query(L, R);
        return ans;
    }

    void modulo(int L, int R, int x){
        if(mx < x) return;
        if(l == r){
            sum %= x;
            mx %= x;
            return;
        }
        int m = (l + r) >> 1;
        if(L <= m) pl->modulo(L, R, x);
        if(R  > m) pr->modulo(L, R, x);
        update();
    }

    void set(int k, int x){
        if(l == r){
            sum = x;
            mx = x; return;
        }
        int m = (l + r) >> 1;
        if(k <= m) pl->set(k, x);
        else pr->set(k, x);
        update();
    }
};


struct Tree{
    Tree* ls, *rs;
    int l, r;
    ll sum; bool same; int x; ll add;
    Tree(){
    }
    ~Tree(){
        if(ls) delete ls;
        if(rs) delete rs;
    }
    void up(){
        if(ls->same && rs->same && ls->x == rs->x){
            same = 1; x = ls->x; add = 0;
        }else same = 0, add = 0;
        sum = rs->sum + ls->sum;
    }
    void down(){
        if(add){
            ls->add += add; ls->sum += add * (ls->r - ls->l); ls->x = x;
            rs->add += add; rs->sum += add * (rs->r - rs->l); rs->x = x;
            add = 0;
        }
    }
    Tree(int l, int r):l(l), r(r){
        ls = rs = NULL;
        sum = 0; same = 0; 
        x = l; add = 0;
        if(r - l <= 1){ same = 1; return; }
        int m = (l + r) >> 1;
        ls = new Tree(l, m);
        rs = new Tree(m, r);
        up();
    }

    void gao(int L, int R, int X){
        if(L <= l && r <= R){
            if(same){
                //cerr<<"l = "<<l<<" r = "<<r<<" x = "<<x<<endl;
                ll v = 1LL * abs(X - x);
                x = X;
                add += v;
                sum += v * (r - l); 
                return;
            }
        }
        down();
        int m = (l + r) >> 1;
        if(L < m) ls->gao(L, R, X);
        if(R > m) rs->gao(L, R, X);
        up();
    }

    ll ask(int L, int R){
        if(L <= l && r <= R) return sum;
        int m = (l + r) >> 1;
        ll ans = 0; down();
        if(L < m) ans += ls->ask(L, R);
        if(R > m) ans += rs->ask(L, R);
        up();
        return ans;
    }
};
