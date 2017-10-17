/*
	求一条从1到n的路径,使得路径上的边的异或和最大。
*/
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 50001
#define M 100001
struct E
{
	int u, v, next;
	long long w;
	E(int _u = 0, int _v = 0, int _next = 0, long long _w = 0){u = _u, v = _v, next = _next, w = _w;}
}G[M<<1];
int cnt, point[N], n, m;
char c;
template<class T>
inline void read(T &x)
{
	T opt(1);
	for (c = getchar();c > '9' || c < '0';c = getchar())if (c == '-')opt = -1;
	for (x = 0;c >= '0' && c <= '9';c = getchar())x = (x << 3) + (x << 1) + c - '0';
	x *= opt;
}
bool vis[N];
long long dis[N];
long long a[M<<1];
int Gauss()
{
	int i, j(0), k;
	for (i = 63;i >= 0; --i)
	{
		for (k = j+1;k <= n; ++k)
		if ((a[k] >> i) & 1)break;
		if (k > n)continue;
		swap(a[k], a[j+1]);
		for (k = 1;k <= n; ++k)
			if (j+1 != k && ((a[k] >> i) & 1))
				a[k] ^= a[j+1];
		j++;
	}
	return j;
}inline void dfs(int u)
{
	vis[u] = 1;
	int i, v;
	for (i = point[u];i;i = G[i].next)
	{
		v = G[i].v;
		if (vis[v])
			a[++m] = dis[u] ^ dis[v] ^ G[i].w;
		else
		{
			dis[v] = dis[u] ^ G[i].w;
			dfs(v);
		}
	}
}
int main()
{
	read(n), read(m);
	int i, j, u, v, k;
	long long w, ans;
	for (i = 1;i <= m; ++i)
	{
		read(u), read(v), read(w);
		G[++cnt] = E(u, v, point[u], w), point[u] = cnt;
		G[++cnt] = E(v, u, point[v], w), point[v] = cnt;
	}
	m = 0;
	dfs(1);
	ans = dis[n];
	n = m;
	k = Gauss();
	for (i = k;i; --i)
		ans = max(ans, ans ^ a[i]);
	printf("%lld\n", ans);
	return 0;
}