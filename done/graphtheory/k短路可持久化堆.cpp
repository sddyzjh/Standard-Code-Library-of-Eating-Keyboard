/*
	G为原图，E为反图
	细节看solve()
*/
namespace Leftist_Tree{
    struct Node{
        int l, r, x, h;
        int val;
    }T[N*50];
    int Root[N];
    int node_num;
    int newnode(const Node& o){
        T[node_num] = o;
        return node_num++;
    }
    void init(){
        node_num = 1;
        T[0].l = T[0].r = T[0].x = T[0].h = 0;
        T[0].val = infi;
    }
    int merge(int x, int y){
        if(!x)return y;
        if(T[x].val> T[y].val)swap(x,y);
        int o = newnode(T[x]);
        T[o].r = merge(T[o].r,y);
        if(T[T[o].l].h<T[T[o].r].h)swap(T[o].l,T[o].r);
        T[o].h = T[T[o].r].h + 1;
        return o;
    }
    void insert(int& x, int val, int v){
        int o = newnode(T[0]);
        T[o].val = val, T[o].x = v;
        x = merge(x, o);
    }
}
using namespace Leftist_Tree;
struct Edge{
	int v, w, n;
}G[N], E[N];
int cnt, point[N], cnt1, point1[N];
void adde(int u, int v, int w = 0){
	G[++cnt]=(Edge){v,w,point[u]},point[u]=cnt;
	E[++cnt1]=(Edge){u,w,point1[v]},point1[v]=cnt1;
}
int n, m, Len;
void Ginit(){
	cnt = cnt1 = 0;
	fill(point,0,n+1);
	fill(point1,0,n+1);
}
int vis[N];
int in[N], p[N];
int d[N];
void dij(int s){
    priority_queue<pii> q;
    d[s] = 0;
    q.push(mp(0, s));
    while(!q.empty()){
        int u = q.top().se;
        q.pop();
        if(vis[u])continue;
        vis[u] = 1;
        for(int i = point1[u];i;i=E[i].n){
            int v = E[i].v;
            if(d[v]> d[u] + E[i].w){
                p[v] = u;
                d[v] = d[u] + E[i].w;
                q.push(mp(-d[v], v));
            }
        }
    }
}

void dfs(int u){
    if(vis[u])return;
    vis[u] = 1;
    if(p[u])Root[u] = Root[p[u]];
    int flag = 1;
    for(int i = point[u];i;i=G[i].n){
        int v = G[i].v;
        if(d[v] == infi)continue;
        if(p[u] == v && d[u] == G[i].w + d[v] && flag){
            flag = 0;
            continue;
        }
        int val = d[v] - d[u] + G[i].w;
        insert(Root[u], val, v);
    }
    for(int i = point1[u];i;i=E[i].n){
        if(p[E[i].v] == u)dfs(E[i].v);
    }
}

int kth(int s, int t, int k){
    dij(t);
    if(d[s] == infi){
        return -1;
    }
    if(s != t)--k;
    if(!k){
		return -1;
    }
    fill(vis,0,n+1);
    init();
    Root[t] = 0;
    dfs(t);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    if(Root[s])q.push(mp(d[s] + T[Root[s]].val, Root[s]));
    while(k--){
        if(q.empty()){
            return -1;
        }
        pii u = q.top();
        q.pop();
        if(!k){
			return u.fi;
        }
        int x = T[u.se].l, y = T[u.se].r, v = T[u.se].x;
        if(Root[v])q.push(mp(u.fi + T[Root[v]].val, Root[v]));
        if(x)q.push(mp(u.fi + T[x].val - T[u.se].val, x));
        if(y)q.push(mp(u.fi + T[y].val - T[u.se].val, y));
    }
}

void solve(){
	Ginit();
    rep(i,1,n){
        d[i] = infi;
        vis[i] = 0;
        p[i] = 0;
    }
    int s, t, k;
    sc(s),sc(t),sc(k),sc(Len);
    rep(i,1,m){
        int u, v, c;
        sc(u),sc(v),sc(c);
        adde(u, v, c);
    }
    int res = kth(s,t,k);
    if(res >= 0 && res <= Len)
		printf("yareyaredawa\n");
	else
		printf("Whitesnake!\n");
}

int main(){
    while(~scanf("%d%d", &n, &m))solve();
    return 0;
}
