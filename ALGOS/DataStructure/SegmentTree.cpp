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


// poj 1157 rectangles area
const int MAX_N = 11111;
const double eps = 1e-6;
int dcmp(double x){
	return (x > eps) - (x < -eps);
}
struct Point{
	double x, y;
	Point(){} Point(double x, double y):x(x), y(y){ }
	void read(){
		cin>>x>>y;
	}
};

struct Rec{
	Point a, b;
	void read(){
		a.read(); b.read();
	}
};

Rec rec[MAX_N];
const double INF = 1e99;
vector<double> hash;
int getHash(double x){
	return lower_bound(hash.begin(), hash.end(), x - eps) - hash.begin();
}

struct Event{
	double x; int l, r, flag;
	Event(){} Event(double x, int l, int r, int flag):x(x), l(l), r(r), flag(flag){}
	bool operator<(const Event& p)const{
		return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && flag > p.flag);
	}
};
vector<Event>  eve;

struct Tree{
	Tree * ls, * rs;
	int l, r; 
	double sum; // up
	int add;    // flag (same == (add == -1))

	~Tree(){
		if(ls) delete ls;
		if(rs) delete rs;
	}
	Tree(){}
	Tree(int l, int r):l(l), r(r){
		ls = rs = NULL;
		sum = 0; add = 0;
		if(r - l == 1) return;
		int m = l + r >> 1;
		ls = new Tree(l, m);
		rs = new Tree(m, r);
		up();
	}

	void up(){
		sum = ls->sum + rs->sum;
	}
	void down(){
		if(add != -1){
			ls->add += add; if(ls->add > 0) ls->sum = hash[ls->r] - hash[ls->l];
			rs->add += add; if(rs->add > 0) rs->sum = hash[rs->r] - hash[rs->l];
			add = -1;
		}
	}

	void addSeg(int L, int R, int flag){
		if(L <= l && r <= R){
			if(add != -1){
				add += flag;
				if(add > 0) sum = hash[r] - hash[l];
				else sum = 0;
				return;
			}
		}
		down();
		int m = l + r >> 1;
		if(L < m) ls->addSeg(L, R, flag);
		if(R > m) rs->addSeg(L, R, flag);
		up();
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int n, icase = 1;
	while(cin>>n){
		if(n == 0) break;
		hash.clear();
		hash.push_back(-INF);
		for(int i  = 0; i < n; i++){
			rec[i].read();
			hash.push_back(rec[i].a.y);
			hash.push_back(rec[i].b.y);
		}
//hash init
		sort(hash.begin(), hash.end());
		hash.erase(unique(hash.begin(), hash.end()), hash.end());
		//for(int i = 0; i < hash.size(); i++) cerr<<"hash["<<i<<"] = "<<hash[i]<<" ";cerr<<endl;

		eve.clear();
		for(int i = 0; i < n; i++){
			int l = getHash(rec[i].a.y), r = getHash(rec[i].b.y);
			eve.push_back(Event(rec[i].a.x, l, r, 1));
			eve.push_back(Event(rec[i].b.x, l, r,  -1));
		}
		sort(eve.begin(), eve.end());

		Tree * rt = new Tree(1, hash.size());
		double ans = 0, lastp = eve[0].x;
		rt->addSeg(eve[0].l, eve[0].r, eve[0].flag);
		for(int i = 1; i < eve.size(); i++){
			//cerr<<rt->sum<<" mul "<<eve[i].x - lastp<<endl;
			ans += rt->sum * (eve[i].x - lastp);
			rt->addSeg(eve[i].l, eve[i].r, eve[i].flag);
			//cerr<<"add "<<eve[i].l<<" to "<<eve[i].r<<endl;
			lastp = eve[i].x;
		}
		delete rt;
		cout<<fixed<<setprecision(0);
		cout<<"Test case #"<<icase++<<endl;
		cout<<"Total explored area: "<<ans<<endl<<endl;
	}
	return 0;
}


//hdu 1828 rectangles zhouchang
const int MAX_N = 21111;
const double eps = 1e-8;
int dcmp(double x){
    return (x > eps) - (x < -eps);
}
struct Point{
    double x, y;
    Point(){} Point(double x, double y):x(x), y(y){ }
    void read(){
        cin>>x>>y;
    }
};

struct Rec{
    Point a, b;
    void read(){
        a.read(); b.read();
    }
};

Rec rec[MAX_N];
const double INF = 1e99;
vector<double> hash;
int getHash(double x){
    return upper_bound(hash.begin(), hash.end(), x - eps) - hash.begin();
}

struct Event{
    double x; int l, r, flag;
    Event(){} Event(double x, int l, int r, int flag):x(x), l(l), r(r), flag(flag){}
    bool operator<(const Event& p)const{
        return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && flag > p.flag);
    }
};
vector<Event>  eve;

struct Tree{
    Tree * ls, * rs;
    int l, r; 
    double sum; // up
    int num, lf, rf;// up segNum, left flag, right flag
    int add;    // flag (same == (add == -1))

    ~Tree(){
        if(ls) delete ls;
        if(rs) delete rs;
    }
    Tree(){}
    Tree(int l, int r):l(l), r(r){
        ls = rs = NULL;
        sum = add = num = lf = rf = 0;
        if(r - l == 1) return;
        int m = l + r >> 1;
        ls = new Tree(l, m);
        rs = new Tree(m, r);
        up();
    }

    void up(){
        sum = ls->sum + rs->sum;
        num = ls->num + rs->num;
        if(ls->rf && rs->lf) num--;
        lf  = ls->lf;
        rf  = rs->rf;
    }

    void down(){
        if(add != -1){
            ls->add += add; 
            ls->downX();
            rs->add += add; 
            rs->downX();
            add = -1;
        }
    }
    void downX(){
        if(add > 0){
            sum = hash[r] - hash[l];
            num = lf = rf = 1;
        }else if(add == 0){
            sum = 0;
            num = lf = rf = 0;
        }
    }

    void addSeg(int L, int R, int flag){
        if(L <= l && r <= R){
            if(add != -1){
                add += flag;
                downX();
                return;
            }
        }
        down();
        int m = l + r >> 1;
        if(L < m) ls->addSeg(L, R, flag);
        if(R > m) rs->addSeg(L, R, flag);
        up();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int n, icase = 1;
    while(cin>>n){
        //if(n == 0) break;
        hash.clear();
        hash.push_back(-INF);
        for(int i  = 0; i < n; i++){
            rec[i].read();
            hash.push_back(rec[i].a.y);
            hash.push_back(rec[i].b.y);
        }
//hash init
        sort(hash.begin(), hash.end());
        hash.erase(unique(hash.begin(), hash.end()), hash.end());
        //for(int i = 0; i < hash.size(); i++) cerr<<"hash["<<i<<"] = "<<hash[i]<<endl;

        eve.clear();
        for(int i = 0; i < n; i++){
            int l = getHash(rec[i].a.y), r = getHash(rec[i].b.y);
            eve.push_back(Event(rec[i].a.x, l, r, 1));
            eve.push_back(Event(rec[i].b.x, l, r,  -1));
        }
        sort(eve.begin(), eve.end());

        Tree * rt = new Tree(1, hash.size());
        double ans = 0, lastp = eve[0].x, lastsum = 0;
        
        int i, j;
        for(i = 0; i < eve.size(); i = j){
            j = i;
            ans += 2 * rt->num * (eve[i].x - lastp), lastp = eve[i].x;
            while(j < eve.size()){
                if(j == i || dcmp(eve[j].x - eve[j - 1].x) == 0){
                    rt->addSeg(eve[j].l, eve[j].r, eve[j].flag); j++;
                    ans += fabs(rt->sum - lastsum), lastsum = rt->sum;
                }
                else break;
            }
        }
        delete rt;
        cout<<fixed<<setprecision(0);
        cout<<ans<<endl;
    }
    return 0;
}
