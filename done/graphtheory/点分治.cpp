/*
	问有多少对点它们两者间的距离小于等于K
*/
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <queue>
using namespace std;
#define N 40002
int n, K, dis[N], point[N], cnt, siz[N], maxs[N], r, son[N], ans;
bitset<N> vis;
struct E
{
    int v, w, next;
}G[N<<1];
inline void add(int u, int v, int w)
{
    G[++cnt] = (E){v, w, point[u]}, point[u] = cnt;
    G[++cnt] = (E){u, w, point[v]}, point[v] = cnt;
}
inline void getroot(int u, int f)
{
    siz[u] = 1, maxs[u] = 0;
    for (int i = point[u];i;i = G[i].next)
    {
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
inline void bfs(int u)
{
    hh.reset();
    Q.push(u);
    hh[u] = 1;
    while (!Q.empty())
    {
        int i = Q.front();Q.pop();
        for (int p = point[i];p;p = G[p].next)
        {
            if (hh[G[p].v] || vis[G[p].v])continue;
            son[++son[0]] = dis[G[p].v] = dis[i] + G[p].w;
            hh[G[p].v] = 1;
            Q.push(G[p].v);
        }
    }
}
/*inline void dfs(int u, int f)
{
    for (int i = point[u];i;i = G[i].next)
    {
        if (G[i].v == f || vis[G[i].v])continue;
        son[++son[0]] = dis[G[i].v] = dis[u] + G[i].w;
        dfs(G[i].v, u);
    }
}*/
inline int calc(int u)
{
    int res(0), i;
    son[son[0]=1] = dis[u], bfs(u);
    sort(son+1, son+son[0]+1);
    son[++son[0]] = 1<<30;
    for (i = 1;i <= son[0]; ++i)
    {
        if (son[i] > K)continue;
        int x = upper_bound(son+1, son+1+son[0], K-son[i])-(son);
        res += x-1;
        if (son[i] << 1 <= K)res--;
    }
    return res;
}
inline void solve(int u)
{
    dis[u] = 0, vis[u] = 1;
    ans += calc(u);
    for (int i = point[u];i;i = G[i].next)
    {
        if (vis[G[i].v])continue;
        dis[G[i].v] = G[i].w, ans -= calc(G[i].v);
        n = siz[G[i].v];
        maxs[r=0] = N, getroot(G[i].v, 0);
        solve(r);
    }
}
int main()
{
    int i, j, u, v, w;
    scanf("%d", &n);
    memset(point, 0, sizeof(point));
    vis.reset();
    for (i = 1;i < n; ++i)
    {
        scanf("%d %d %d", &u, &v, &w);
        add(u, v, w);
    }
    scanf("%d", &K);
    maxs[r=0]=n+1;
    getroot(1, 0);
    solve(r);
    printf("%d\n", ans>>1);
    ans = 0;
    return 0;
}
/*
	给一棵树,每条边有权.求一条简单路径,权值和等于K,且边的数量最小
*/
#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>
using namespace std;
#define N 200005
#define Max (N<<1)
bitset<N> vis;
struct hh
{
	int i, x;
	bool operator < (const hh &nb) const
	{
		return x < nb.x;
	}
}son[N];
int n, K, siz[N], maxs[N], dfn[N], point[N], belong[N], dis[N], dep[N], cnt, r, ans(Max);
char c;
inline void read(int &x)
{
	for (c = getchar();c > '9' || c < '0';c = getchar());
	for (x = 0;c >= '0' && c <= '9';c = getchar())
		x = (x << 3) + (x << 1) + c - '0';
}
struct E
{
	int v, w, next;
}G[N<<1];
inline void add(int u, int v, int w)
{
	G[++cnt] = (E){v, w, point[u]}, point[u] = cnt;
	G[++cnt] = (E){u, w, point[v]}, point[v] = cnt;
}
inline void getroot(int u, int f)
{
	siz[u] = 1, maxs[u] = 0;
	for (int i = point[u];i;i = G[i].next)
	{
		int v = G[i].v;
		if (v == f || vis[v])continue;
		getroot(v, u);
		siz[u] += siz[v], maxs[u] = max(maxs[u], siz[v]);
	}
	maxs[u] = max(maxs[u], n-siz[u]);
	if (maxs[u] < maxs[r])r = u;
}
inline void dfs(int u, int f)
{
	if (f != r)belong[u] = belong[f];
	for (int i = point[u];i;i = G[i].next)
	{
		int v = G[i].v;
		if (v == f || vis[v])continue;
		dep[v] = dep[u]+1;
		son[++son[0].i].x = dis[v] = dis[u] + G[i].w;
		son[son[0].i].i = v;
		dfs(v, u);
	}
	dfn[u] = ++cnt;
}
inline int calc(int u)
{
	int res(Max);
	son[++son[0].i].x = dis[u];
	son[1].i = u;
	belong[u] = u;
	for (int i = point[u];i;i = G[i].next)
	{
		int v = G[i].v;
		if (vis[v])continue;
		belong[v] = v;
	}
	dfs(u, 0);
	sort(son+1, son+1+son[0].i);
	son[++son[0].i].x = K<<1;
	for (int i = 1;i <= son[0].i; ++i)
	{
		son[i].x = K - son[i].x;
		int x = lower_bound(son+1, son+1+son[0].i, son[i])-(son);
		for (;son[i].x == son[x].x; ++x)
		{
			if (x == i)continue;
			if (belong[son[i].i] == belong[son[x].i])continue;
			res = min(res, dep[son[i].i]-dep[u]+dep[son[x].i]-dep[u]);
		}
		son[i].x = K - son[i].x;
	}
	return res;
}
inline void solve(int u)
{
	son[0].i = dis[u] = 0;
	vis[u] = 1;
	ans = min(ans, calc(u));
	for (int i = point[u];i;i = G[i].next)
	{
		int v = G[i].v;
		if (vis[v])continue;
		maxs[r=0] = N-1;
		n = siz[v];
		getroot(v, 0);
		solve(r);
	}
}
int main()
{
//	freopen("a.in", "r", stdin);
	int i, u, v, w;
	read(n), read(K);
//	scanf("%d %d", &n, &K);
	for (i = 1;i < n; ++i)
	{
		read(u), read(v), read(w);
		//scanf("%d %d %d", &u, &v, &w);
		add(u+1, v+1, w);
	}
	maxs[cnt=r=0] = N-1;
	getroot(1, 0);
	solve(r);
	printf("%d\n", ans == Max ? -1 : ans);
}