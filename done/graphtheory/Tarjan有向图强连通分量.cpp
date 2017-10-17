/*
	调用SCC()得到强连通分量,调用suodian()缩点
	belong[i]为所在scc编号,sccnum为scc数量
	原图用addedge,存在G,缩点后的图用addedge2,存在G1
	多组数据时调用Ginit()
*/
int n, m;
int point[N], cnt;
int low[N], dfn[N], belong[N], Stack[N];
bool instack[N];
int dfsnow, Stop, sccnum;
struct E{
	int u, v, nex;
}G[M],G1[M];
void tarjan(int u){
	int v;
	dfn[u] = low[u] = ++dfsnow;
	instack[u] = 1;
	Stack[++Stop] = u;
	for (int i = point[u];i;i = G[i].nex){
		v = G[i].v;
		if (!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else
			if (instack[v])
				low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]){
		sccnum++;
		do{
			v = Stack[Stop--];
			instack[v] = 0;
			belong[v] = sccnum;
			num[sccnum][++num[sccnum][0]] = v;
		}
		while (v != u);
	}
}
void Ginit(){
	cnt = 0;
	SET(point,0);
}
void SCC(){
	Stop = sccnum = dfsnow = 0;
	SET(dfn, 0);
	rep(i,n)
		if (!dfn[i])
			tarjan(i);
}
void addedge(int a, int b){
	G[++cnt] = (E){a,b,point[a]}, point[a] = cnt;
}
void addedge2(int a, int b){
	G1[++cnt] = (E){a,b,point[a]}, point[a] = cnt;
}
int degre[N];
void suodian(){
	Ginit();
	SET(degre,0);
	rep(i,m)
		if (belong[G[i].u] != belong[G[i].v]){
			addedge2(belong[G[i].u], belong[G[i].v]);
			degre[belong[G[i].v]]++;
		}
}
/*
	割点和桥
	割点：删除后使图不连通
	桥(割边)：删除后使图不连通
	对图深度优先搜索，定义DFS(u)为u在搜索树（以下简称为树）中被遍历到的次序号。定义Low(u)为u或u的子树中能通过非树边追溯到的DFS序号最小的节点。
	𝐿𝑜𝑤(𝑢)=𝑀𝑖𝑛{𝐷𝐹𝑆(𝑢);𝐷𝐹𝑆(𝑣),(𝑢,𝑣)为非树边;𝐿𝑜𝑤(𝑣),(𝑢,𝑣)为树边}
	一个顶点u是割点，当且仅当满足(1)或(2)
	(1) u为树根，且u有多于一个子树。 (2) u不为树根，且满足存在(u,v)为树边，使得DFS(u)<=Low(v)。
	一条无向边(u,v)是桥，当且仅当(u,v)为树边，且满足DFS(u)<Low(v)。
*/