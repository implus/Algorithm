/*************************************************************************
    > File Name: Dinic.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 五  4/ 4 10:43:56 2014
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

const int  maxn = 555;
const int  maxm = 555;
const int inf = (1<<30);

struct Dinic{
  int n, m, s, t;
  struct Edge{
    int from, to, cap, flow, cost;
    Edge(){} Edge(int from, int to, int cap, int flow, int cost):from(from), to(to), cap(cap), flow(flow), cost(cost){}
  };
  vector<Edge> edges;
  vector<int> G[maxn];
  bool vis[maxn];
  int d[maxn];
  int cur[maxn];// current edge
  //MCMF
  int inq[maxn];
  int p[maxn];  // last edge
  int a[maxn];  // min cost flow
  void init(int n){
    this->n = n;
    edges.clear();
    for(int i = 0; i < n; i++) G[i].clear();
  }
  void add(int u, int v, int f, int cost = 0){
    //printf("%d -> %d, v = %d\n", u, v, f);
    edges.push_back(Edge(u, v, f, 0, cost));
    edges.push_back(Edge(v, u, 0, 0, cost));
    m = edges.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
  }
  bool bfs(){
    fill(vis, vis + n, 0); fill(d, d + n, 0);
    vis[s] = 1;            
    queue<int> q; q.push(s);
    while(q.size()){
      int p = q.front(); q.pop();
      for(int i = 0; i < G[p].size(); i++){
        Edge e = edges[G[p][i]];
        if(e.cap - e.flow == 0 || vis[e.to]) continue;
        vis[e.to] = 1, d[e.to] = d[p] + 1;
        q.push(e.to);
      }
    }
    return d[t];
  }
  int dfs(int x, int a){
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i++){
      Edge& e = edges[G[x][i]];
      if(d[e.to] == d[x] + 1 && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0){
        flow += f; a -= f;
        e.flow += f, edges[G[x][i]^1].flow -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }
  int maxFlow(int s, int t){
    this->s = s; this->t = t;
    int flow = 0;
    while(bfs()){
      memset(cur, 0, sizeof(cur));
      flow += dfs(s, inf);
    }
    return flow;
  }
// mcmf:
  bool spfa(int s, int t, int &flow, int &cost){
    fill(d, d + n, inf);
    fill(inq, inq + n, 0);
    d[s] = 0, inq[s] = 1, p[s] = 0, a[s] = inf;
    queue<int> q;
    q.push(s);
    while(q.size()){
      int u = q.front(); q.pop();
      for(int i = 0; i < G[u].size(); i++){
        Edge &e = edges[G[u][i]];
        if(e.cap - e.flow > 0 && d[e.to] < d[u] + e.cost){
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) { q.push(e.to), inq[e.to] = 1; }
        }
      }
    }
    if(d[t] == inf) return false;
    flow += a[t];
    cost += a[t] * d[t];
    int u = t;
    while(u != s){
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
      u = edges[p[u]].from;
    }
    return true;
  }
  int Mincost(int s, int t){
    int flow = 0, cost = 0;
    while(spfa(s, t, flow, cost));
    return cost;
  }
}g;

