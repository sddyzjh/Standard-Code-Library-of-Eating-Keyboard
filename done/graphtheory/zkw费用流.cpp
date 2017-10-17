/*
	调用zkw(s,t,cost)返回s到t的最大流,cost保存费用
	多组数据调用Ginit()
*/
struct E{
	int v,n,F,f,c;
}G[M];
int point[N],cnt;
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
			if(G[i].F>G[i].f&&dis[v]-dis[u]-G[i].c>0){
				dis[v]=dis[u]+G[i].c;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[t]!=infi;
}
bool mark[N];
int dfs(int u,int t,int f,int &ans){
	mark[u]=1;
	if(u==t)return f;
	double w;
	int used=0;
	for(int i=point[u];i;i=G[i].n){
		if(G[i].F>G[i].f&&!mark[G[i].v]&&dis[u]+G[i].c-dis[G[i].v]==0){
			w=dfs(G[i].v,t,min(G[i].F-G[i].f,f-used),ans);
			G[i].f+=w;
			G[i^1].f-=w;
			ans+=G[i].c*w;
			used+=w;
			if(used==f)return f;
		}
	}
	return used;
}
int zkw(int s,int t,int &ans){
	int tmp=0;
	ans=0;
	while(spfa(s,t)){
		mark[t]=1;
		while(mark[t]){
			SET(mark,0);
			tmp+=dfs(s,t,infi,ans);
		}
	}
	return tmp;
}