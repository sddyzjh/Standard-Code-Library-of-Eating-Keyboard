int n, siz[N], maxs[N], r;
bitset<N> vis;
void getroot(int u, int f){
    siz[u] = 1, maxs[u] = 0;
    for (int i = point[u];i;i = G[i].n){
        if (G[i].v == f || vis[G[i].v])continue;
        getroot(G[i].v, u);
        siz[u] += siz[G[i].v];
        maxs[u] = max(maxs[u], siz[G[i].v]);
    }
    maxs[u] = max(maxs[u], n-siz[u]);
    if (maxs[r] > maxs[u])
        r = u;
}
queue<int> Q;
bitset<N> hh;
void bfs(int u){
    hh.reset();
    Q.push(u);
    hh[u] = 1;
    while (!Q.empty()){
        int i = Q.front();Q.pop();
        for (int p = point[i];p;p = G[p].n){
            if (hh[G[p].v] || vis[G[p].v])continue;
            Q.push(G[p].v);
        }
    }
}
int calc(int u){
	int res(0);
    bfs(u);
    return res;
}
void solve(int u){
    dis[u] = 0, vis[u] = 1;
    ans += calc(u);
    for (int i = point[u];i;i = G[i].n){
        if (vis[G[i].v])continue;
        dis[G[i].v] = G[i].w, ans -= calc(G[i].v);
        n = siz[G[i].v];
        maxs[r=0] = N, getroot(G[i].v, 0);
        solve(r);
    }
}
void p_d(){
	vis.reset();
	maxs[r=0]=n+1;
    getroot(1, 0);
    solve(r);
}