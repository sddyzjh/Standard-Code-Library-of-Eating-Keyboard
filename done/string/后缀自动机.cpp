/*
	init() 初始化
	ins(w) 从后插入新点
	getsz() 做出parent树，求出right集合大小=sz
*/
struct SAM{
	static const int K = 26;
	int rt, la, nodes;
	int len[N], n[N][K], pa[N], sz[N];
	void init(){
		nodes = 0;
		rt = la = newnode(0);
	}
	int newnode(int pl){
		int i = ++nodes;
		len[i] = pl;
		return i;
	}
	void ins(int w){
		int p = la, np = newnode(len[p]+1);
		la = np;
		sz[np] = 1;
		while(p && !n[p][w])n[p][w] = np, p = pa[p];
		if(!p)pa[np] = rt;
		else{
			int q = n[p][w];
			if(len[q] == len[p]+1)pa[np] = q;
			else{
				int nq = newnode(len[p]+1);
				memcpy(n[nq], n[q], sizeof(n[q]));
				pa[nq] = pa[q];
				pa[q] = pa[np] = nq;
				while(p && n[p][w] == q)n[p][w] = nq, p = pa[p];
			}
		}
	}
	void getsz(){
		rep(i,2,nodes)
			adde(pa[i],i);
		dfs(rt);
	}
	void dfs(int u){
		for(int i = point[u];i;i=G[i].n){
			int v = G[i].v;
			dfs(v);
			sz[u] += sz[v];
		}
	}
}sam;