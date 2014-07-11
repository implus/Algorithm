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

const int FINF = 1<<30; const int CINF = 1<<30;
typedef int F; typedef int C; // F is flow, C is cost
struct NetWork{
    struct Edge{
        int from, to; F cap, flow; C cost; int next;
        Edge(){} Edge(int from, int to, F cap, F flow, F cost, int next):
            from(from), to(to), cap(cap), flow(flow), cost(cost), next(next){}
    };

    vector<Edge> E;
    vector<int> head, cur;
    int n, m;// real point id, edge number
    int source, sink;// from, to

    NetWork(){} NetWork(int pointAmount){ 
        m = n = 0; 
        head.assign(pointAmount, -1); cur = head;
        E.clear(); 
    }
    int addVertex(){ return n++; }

    void addEdge(int s, int t, F f, C c = 0){
        E.push_back(Edge(s, t, f, 0, c, head[s])); head[s] = m++;
        E.push_back(Edge(t, s, 0, 0, -c, head[t])); head[t] = m++;
    }

    vector<int> dp;// steps
    bool bfs(int s, int t){
        dp.assign(n, -1); 
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
        for(int& e = cur[s]; ~e; e = E[e].next) if( E[e].cap > E[e].flow ){
            int ns = E[e].to;
            if(dp[ns] == dp[s] + 1 && (f = dfs(ns, t, min(a, E[e].cap - E[e].flow))) > 0){
                ans += f; E[e].flow += f; E[e ^ 1].flow -= f; a -= f; if(a == 0) break;
            }
        }
        return ans;
    }
    F maxFlow(int s, int t){
        F flow = 0;
        while(bfs(s, t)){
            copy(head.begin(), head.end(), cur.begin());
            flow += dfs(s, t, FINF);
        }
        //E.clear(); head.clear(); cur.clear(); dp.clear();
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
                int nw = E[e].to;
                if(d[nw] > d[w] + E[e].cost){
                    d[nw] = d[w] + E[e].cost;
                    last[nw] = e;
                    a[nw] = min(a[w], E[e].cap - E[e].flow);
                    q.push(nw);
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
        //E.clear(); head.clear(); cur.clear(); d.clear(); last.clear(); a.clear(); // not overstack
        return cost;
    }
};

template<int MAXN, typename T = int, typename S = T>
struct MinCostMaxFlow {
  struct NegativeCostCircuitExistsException {
  };

  struct Edge {
    int v;
    T c;
    S w;
    int b;
    Edge(int v, T c, S w, int b) : v(v), c(c), w(w), b(b) { }
  };

  int n, source, sink;
  vector<Edge> e[MAXN];

  void init(int n, int source, int sink) {
    this->n = n;
    this->source = source;
    this->sink = sink;
    for (int i = 0; i < n; ++i) {
      e[i].clear();
    }
  }

  void addEdge(int a, int b, T c, S w) {
    e[a].push_back(Edge(b, c, w, e[b].size()));
    e[b].push_back(Edge(a, 0, -w, e[a].size() - 1));  // TODO
  }

  bool mark[MAXN];
  T maxc[MAXN];
  S minw[MAXN];
  int dist[MAXN];
  Edge* prev[MAXN];

  bool _spfa() {
    queue<int> q;
    fill(mark, mark + n, false);
    fill(maxc, maxc + n, 0);
    fill(minw, minw + n, numeric_limits<S>::max());
    fill(dist, dist + n, 0);
    fill(prev, prev + n, (Edge*)NULL);
    mark[source] = true;
    maxc[source] = numeric_limits<S>::max();
    minw[source] = 0;

    q.push(source);
    while (!q.empty()) {
      int cur = q.front();
      mark[cur] = false;
      q.pop();
      for (typename vector<Edge>::iterator it = e[cur].begin(); it != e[cur].end(); ++it) {
        T c = min(maxc[cur], it->c);
        if (c == 0) {
          continue;
        }

        int v = it->v;
        S w = minw[cur] + it->w;
        if (minw[v] > w || (minw[v] == w && maxc[v] < c)) { // TODO
          maxc[v] = c;
          minw[v] = w;
          dist[v] = dist[cur] + 1;
          if (dist[v] >= n) {
            return false;
          }
          prev[v] = &*it;
          if (!mark[v]) {
            mark[v] = true;
            q.push(v);
          }
        }
      }
    }
    return true;
  }

  pair<T, S> gao() {
    T sumc = 0;
    S sumw = 0;
    while (true) {
      if (!_spfa()) {
        throw NegativeCostCircuitExistsException();
      } else if (maxc[sink] == 0) {
        break;
      } else {
        T c = maxc[sink];
        sumc += c;
        sumw += c * minw[sink];

        int cur = sink;
        while (cur != source) {
          Edge* e1 = prev[cur];
          e1->c -= c;
          Edge* e2 = &e[e1->v][e1->b];
          e2->c += c;
          cur = e2->v;
        }
      }
    }
    return make_pair(sumc, sumw);
  }
};

int main(){

    return 0;
}
