/*
	调用lca_init()后
	调用lca(u,v)得到u,v的lca
*/
int fa[N][M];
void lca_init(){
	rep(k,1,M-1)rep(i,1,n)
		fa[i][k] = fa[fa[i][k-1]][k-1];
}
int lca(int u,int v){
	if(dep[u] < dep[v])
		swap(u, v);
	repr(i,0,M-1)
		if(((dep[u] - dep[v])>>i) & 1)
			u = fa[u][i];
	repr(i,0,M-1)
		if(fa[u][i] != fa[v][i]){
			u = fa[u][i];
			v = fa[v][i];
		}
	if(u != v)
		return fa[u][0];
	return u;
}