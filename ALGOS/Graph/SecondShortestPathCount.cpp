int solve(int s, int f){
    priority_queue<node> que;
    fill(dist, dist + MAX_N, inf);
    fill(dist2, dist2 + MAX_N, inf);
    fill(cnt, cnt + MAX_N, 0);
    fill(cnt2, cnt2 + MAX_N, 0);

    dist[s] = 0;
    cnt[s]  = 1;
    que.push(node(s, 0, 0));

    while(que.size()){
        node p = que.top(); que.pop();
        int u = p.to, d = p.dis, w = p.id;
        if(w == 0 && d > dist[u]) continue;
        if(w == 1 && d > dist2[u]) continue;
        for(int i = 0; i < G[u].size(); i++){
            pii& e = G[u][i];
            int d2 = d + e.Y, t = e.X;
            if(d2 < dist[t]){
                dist2[t] = dist[t]; cnt2[t] = cnt[t]; que.push(node(t, dist2[t], 1));
                dist[t]  = d2; cnt[t] = (w == 0 ? cnt[u]: cnt2[u]); que.push(node(t, dist[t], 0));
            }else if(d2 == dist[t]){
                cnt[t]  += (w == 0 ? cnt[u]: cnt2[u]);
            }else if(d2 < dist2[t]){
                dist2[t] = d2; cnt2[t] = (w == 0 ? cnt[u]: cnt2[u]); que.push(node(t, dist2[t], 1));
            }else if(d2 == dist2[t]){
                cnt2[t] += (w == 0 ? cnt[u]: cnt2[u]);
            }
        }
    }
    //return dist2[f];
    int ans = cnt[f];
    if(dist2[f] == dist[f] + 1) ans += cnt2[f];
    return ans;
}

