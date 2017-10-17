/*
	调用minCostMaxflow(s,t,cost)返回s到t的最大流,cost保存费用
	多组数据调用Ginit()
*/
struct E{
	int v,n,F,f,cost;
}G[M];
int point[N],cnt;
int pre[N];
int dis[N];
bool vis[N];
void Ginit(){
	cnt=1;
	SET(point,0);
}
void addedge(int u,int v,int F,int cost){
	G[++cnt]=(E){v,point[u],F,0,cost},point[u]=cnt;
	G[++cnt]=(E){u,point[v],0,0,-cost},point[v]=cnt;
}
bool spfa(int s,int t){
	queue<int>q;
	SET(vis,0);
	SET(pre,0);
	repab(i,s,t)
		dis[i]=infi;
	dis[s]=0;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=point[u];i;i=G[i].n){
			int v=G[i].v;
			if(G[i].F>G[i].f&&dis[v]-dis[u]-G[i].cost>0){
				dis[v]=dis[u]+G[i].cost;
				pre[v]=i;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return pre[t];
}
int minCostMaxflow(int s,int t,int &cost){
	int f=0;
	cost=0;
	while(spfa(s,t)){
		int Min=infi;
		for(int i=pre[t];i;i=pre[G[i^1].v]){
			if(Min>G[i].F-G[i].f)
				Min=G[i].F-G[i].f;
		}
		for(int i=pre[t];i;i=pre[G[i^1].v]){
			G[i].f+=Min;
			G[i^1].f-=Min;
			cost+=G[i].cost*Min;
		}
		f+=Min;
	}
	return f;
}