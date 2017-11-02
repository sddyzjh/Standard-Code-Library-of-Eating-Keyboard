/*
	s到t的k短路
	G为原边
	E为反向边
	预处理t的单源最短路
	调用kth()返回k短路
*/
const ll INF = 1e18;
namespace Leftist_Tree{
    struct Node{
        int l, r, x, h;
        ll val;
    }T[N*40];
    int Root[N];
    int node_num;
    int newnode(const Node& o){
        T[node_num] = o;
        return node_num++;
    }
    void init(){
        node_num = 1;
        T[0].l = T[0].r = T[0].x = T[0].h = 0;
        T[0].val = INF;
    }
    int merge(int x, int y){
        if(!x)return y;
        if(T[x].val > T[y].val)swap(x, y);
        int o = newnode(T[x]);
        T[o].r = merge(T[o].r, y);
        if(T[T[o].l].h < T[T[o].r].h)swap(T[o].l, T[o].r);
        T[o].h = T[T[o].r].h + 1;
        return o;
    }
    void insert(int& x, ll val, int v){
        int o = newnode(T[0]);
        T[o].val = val, T[o].x = v;
        x = merge(x, o);
    }
    void show(int o){
        printf("%d %I64d %I64d %I64d\n", o, T[o].val, T[T[o].l].val, T[T[o].r].val);
        if(T[o].l)show(T[o].l);
        if(T[o].r)show(T[o].r);
    }
}
using namespace Leftist_Tree;
vector<pii> G[N], E[N];
int vis[N];
int in[N], p[N];
ll d[N];
int s, t; 
int n, m, k;
void addedge(int u, int v, int c){
    G[u].push_back(pii(v, c));
    E[v].push_back(pii(u, c));
    in[u]++;
}
void dfs(int u){
    if(vis[u])return;
    vis[u] = 1;
    if(p[u])Root[u] = Root[p[u]];
    int flag = 1;
    Rep(i,G[u].size()){
        int v = G[u][i].st;
        if (d[v] == INF)continue;
        if (p[u] == v && d[u] == G[u][i].ed + d[v] && flag){
            flag = 0;
            continue;
        }
        ll val = d[v] - d[u] + G[u][i].ed;
        insert(Root[u], val, v);
    }
    Rep(i,E[u].size()){
        if (p[E[u][i].st] == u)dfs(E[u][i].st);
    }
}
ll kth(){
    if(d[s] == INF){
        return -1;
    }
    if(s != t)--k;
    if(!k){
        return d[s];
    }
    init();
    Root[t] = 0;
    dfs(t);
    priority_queue<pli, vector<pli>, greater<pli> >q;//升序
    if (Root[s])q.push(pli(d[s] + T[Root[s]].val, Root[s]));
    while (k--){
        if (q.empty()){
            return -1;
        }
        pli u = q.top();
        q.pop();
        if (!k){
            return u.st;
        }
        int x = T[u.ed].l, y = T[u.ed].r, v = T[u.ed].x;
        if(Root[v])q.push(pli(u.st + T[Root[v]].val, Root[v]));
        if(x)q.push(pli(u.st + T[x].val - T[u.ed].val, x));
        if(y)q.push(pli(u.st + T[y].val - T[u.ed].val, y));
    }
}
