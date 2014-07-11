#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 300;

struct Graph{
    bool mat[maxn][maxn];// 图
    bool inque[maxn];
    int n, match[maxn], fa[maxn], base[maxn];//匹配的点,父亲
	queue <int> q;
    void init(int nt){
        n = nt;
        for (int i = 1; i <= n; ++i){
            match[i] = 0;
            for (int j = 1; j <= n; ++j)
                mat[i][j] = false;
        }
    }
    void addEdge(int u, int v){
        mat[u][v] = mat[v][u] = true;
    }
    int inpath[maxn];
    static int pcnt;
    int lca(int u, int v){
        ++pcnt;
        while (u){
            u = base[u];
            inpath[u] = pcnt;
            u = fa[match[u]];
        }
        while (true){
            v = base[v];
            if (inpath[v] == pcnt) return v;
            v = fa[match[v]];
        }
    }
    int inblossom[maxn];
    static int bcnt;
    void reset(int u, int anc){
        while (u != anc){
            int v = match[u];
            inblossom[base[v]] = bcnt;
            inblossom[base[u]] = bcnt;
            v = fa[v];
            if (base[v] != anc) fa[v] = match[u];
            u = v;
        }
    }
    void contract(int u, int v){
        int anc = lca(u, v);
        ++bcnt;
        reset(u, anc);
        reset(v, anc);
        if (base[u] != anc) fa[u] = v;
        if (base[v] != anc) fa[v] = u;
        for (int i = 1; i <= n; ++i)
            if (inblossom[base[i]] == bcnt){
                base[i] = anc;
                if (!inque[i]){
				   	q.push(i);
					inque[i] = 1;
				}
            }
    }
    int bfs(int st){
        for (int i = 1; i <= n; ++i){
            fa[i] = 0;
            inque[i] = false;
            base[i] = i;
        }
		while (!q.empty()) q.pop();
		q.push(st);
        while (!q.empty()){
            int u = q.front(); q.pop();
            for (int v = 1; v <= n; ++v)
                if (mat[u][v] && base[v] != base[u] && match[v] != u){
                    if (v == st || (match[v] && fa[match[v]]))
                        contract(u, v);
                    else{
                        if (fa[v] == 0){
                            if (match[v]){
                                q.push(match[v]);
								inque[match[v]] = 1;
                                fa[v] = u;
                            }
                            else{
                                fa[v] = u;
                                return v;
                            }
                        }
                    }
                }
        }
        return 0;
    }
    void augment(int finish){
        int u = finish, v, w;
        while (u){
            v = fa[u];
            w = match[v];
            match[u] = v;
            match[v] = u;
            u = w;
        }
    }
    int graph_max_match(){//最大匹配
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            if (match[i] == 0){
                int finish = bfs(i);
                if (finish){
                    augment(finish);
                    ans += 2;
                }
            }
        return ans;
    }
}g;
int Graph :: bcnt = 0, Graph :: pcnt = 0;
int main(){
    int n;
    scanf("%d", &n);
    g.init(n);
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF)
        g.addEdge(a, b);
    printf("%d\n", g.graph_max_match());
    for (int i = 1; i <= n; ++i)//输出一组解
        if (g.match[i]){
            printf("%d %d\n", i, g.match[i]);
            g.match[g.match[i]] = 0;
        }
    return 0;
}
