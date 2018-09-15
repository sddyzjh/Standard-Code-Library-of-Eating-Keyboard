/*
	调用Dijkstra(s)得到从s出发的最短路,存在dist中
	多组数据时调用Ginit()
*/
struct qnode{
    int v,c;
    bool operator <(const qnode &r)const{
        return c>r.c;
    }
};
bool vis[N];
int dist[N];
void dij(int s){
    fill(vis,0,n+1);
    fill(dist,127,n+1); 
	dist[s]=0;
    priority_queue<qnode> que;
    while(!que.empty())que.pop();
    que.push((qnode){s,0});
    qnode tmp;
    while(!que.empty()){
        tmp=que.top();
        que.pop();
        int u=tmp.v;
        if(vis[u])continue;
        vis[u]=1;
        for_each_edge(u){
            int v = G[i].v;
            if(!vis[v]&&dist[v]>dist[u]+G[i].w){
                dist[v]=dist[u]+G[i].w;
                que.push((qnode){v,dist[v]});
            }
        }
    }
}