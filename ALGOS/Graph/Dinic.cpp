/*************************************************************************
  > File Name: Dinic.cpp
  > Author: implus
  > Mail: 674592809@qq.com
  > Created Fime: 五  4/ 4 10:43:56 2014
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

const int FINF = 1<<30;
const int CINF = 1<<30;
template<class F = int, class C = int>// F is flow, C is cost
struct Flow{
    struct Edge{
        int from, to, cap; F flow; C cost; int next;
        Edge(){} Edge(int from, int to, int cap, F flow, F cost, int next):
            from(from), to(to), cap(cap), flow(flow), cost(cost), next(next){}
    };

    vector<Edge> E;
    vector<int> head;
    int n, m;

    void init(int n){
        this->n = n; head.assign(n + 1, -1);
        m = 0; E.clear();
    }
    void add(int s, int t, int f, int c){
        E.push_back(Edge(s, t, f, 0, c, head[s])); head[s] = m++;
        E.push_back(Edge(t, s, 0, 0, -c, head[t])); head[t] = m++;
    }

    vector<int> dp;// steps
    bool bfs(int s, int t){
        dp.assign(n + 1, -1); 
        queue<int> q; q.push(s), dp[s] = 0;
        while(q.size()){
            int u = q.front(); q.pop();
            for(int e = head[u]; ~e; e = E[e].next) if( E[e].cap > E[e].flow ){
                int v = E[e].to;
                if(dp[v] != -1) continue;
                dp[v] = dp[u] + 1;
                q.push(v);
            }
        }
        return dp[t] != -1;
    }
    F dfs(int s, int t, F a){
        if(s == t || a == 0) return a;
        F ans = 0, f;
        for(int e = head[s]; ~e; e = E[e].next) if( E[e].cap > E[e].flow ){
            if(dp[E[e].to] == dp[s] + 1 && (f = dfs(E[e].to, t, min(a, E[e].cap - E[e].flow))) > 0){
                ans += f; E[e].flow += f; E[e ^ 1].flow -= f; a -= f; if(a == 0) break;
            }
        }
        return ans;
    }
    F maxFlow(int s, int t){
        F flow = 0;
        while(bfs(s, t)){
            //cerr<<flow<<endl;
            flow += dfs(s, t, FINF);
        }
        E.clear(); head.clear(); dp.clear();
        return flow;
    }

    // mcmf
    vector<C> d; vector<F> a; vector<int> last;
    bool spfa(int s, int t, F& flow, C& cost){
        d.assign(n + 1, CINF); last.assign(n + 1, -1); a.assign(n + 1, FINF);
        queue<int> q; q.push(s), d[s] = 0;
        while(q.size()){
            int w = q.front(); q.pop();
            for(int e = head[w]; ~e; e = E[e].next) if( E[e].cap > E[e].flow ) {
                if(d[E[e].to] > d[w] + E[e].cost){
                    d[E[e].to] = d[w] + E[e].cost;
                    last[E[e].to] = e;
                    a[E[e].to] = min(a[w], E[e].cap - E[e].flow);
                    q.push(E[e].to);
                }
            }
        }
        if(d[t] == CINF) return false;
        flow += a[t];
        cost += a[t] * d[t];
        int e = last[t];
        while(~e){
            E[e].flow += a[t]; 
            E[e ^ 1].flow -= a[t];
            e = last[E[e].from];
        }
        return true;
    }
    C MCMF(int s, int t, F& flow, C& cost){
        cost = 0; flow = 0;
        while(spfa(s, t, flow, cost));
        E.clear(); head.clear();d.clear(); last.clear(); a.clear(); // not overstack
        return cost;
    }
};

Flow<int,int> g;
int main(){
    return 0;
}
