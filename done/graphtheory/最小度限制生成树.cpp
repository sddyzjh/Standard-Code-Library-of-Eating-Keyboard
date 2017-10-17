/*
	只限制一个点的度数
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <ctime>
#include <queue>
#include <map>

#define CL(arr, val)    memset(arr, val, sizeof(arr))
#define REP(i, n)       for((i) = 0; (i) < (n); ++(i))
#define FOR(i, l, h)    for((i) = (l); (i) <= (h); ++(i))
#define FORD(i, h, l)   for((i) = (h); (i) >= (l); --(i))
#define L(x)    (x) << 1
#define R(x)    (x) << 1 | 1
#define MID(l, r)   (l + r) >> 1
#define Min(x, y)   x < y ? x : y
#define Max(x, y)   x < y ? y : x
#define E(x)    (1 << (x))

const double eps = 1e-8;
typedef long long LL;
using namespace std;
const int inf = ~0u>>2;
const int N = 33;

int parent[N];
int g[N][N];
bool flag[N][N];
map<string, int> NUM;

int n, k, cnt, ans;

struct node {
    int x;
    int y;
    int v;
} a[1<<10];

struct edge {
    int x;
    int y;
    int v;
} dp[N];

bool cmp(node a, node b) {
    return a.v < b.v;
}

int find(int x) {   //并查集查找
    int k, j, r;
    r = x;
    while(r != parent[r]) r = parent[r];
    k = x;
    while(k != r) {
        j = parent[k];
        parent[k] = r;
        k = j;
    }
    return r;
}

int get_num(string s) {    //求编号
    if(NUM.find(s) == NUM.end()) {
        NUM[s] = ++cnt;
    }
    return NUM[s];
}

void kruskal() {  //。。。
    int i;
    FOR(i, 1, n) {
        if(a[i].x == 1 || a[i].y == 1)  continue;
        int x = find(a[i].x);
        int y = find(a[i].y);
        if(x == y)  continue;
        flag[a[i].x][a[i].y] = flag[a[i].y][a[i].x] = true;
        parent[y] = x;
        ans += a[i].v;
    }
   //printf("%d\n", ans);
}

void dfs(int x, int pre) {   //dfs求1到某节点路程上的最大值
    int i;
    FOR(i, 2, cnt) {
        if(i != pre && flag[x][i]) {
            if(dp[i].v == -1) {
                if(dp[x].v > g[x][i])   dp[i] = dp[x];
                else {
                    dp[i].v = g[x][i];
                    dp[i].x = x;    //记录这条边
                    dp[i].y = i;
                }
            }
            dfs(i, x);
        }
    }
}

void init() {
    ans = 0; cnt = 1;
    CL(flag, false);
    CL(g, -1);
    NUM["Park"] = 1;
    for(int i = 0; i < N; ++i)  parent[i] = i;
}

int main() {
    //freopen("data.in", "r", stdin);

    int i, j, v;
    string s;
    scanf("%d", &n);
    init();
    for(i = 1; i <= n; ++i) {
        cin >> s;
        a[i].x = get_num(s);
        cin >> s;
        a[i].y = get_num(s);
        scanf("%d", &v);
        a[i].v = v;
        if(g[a[i].x][a[i].y] == -1)     g[a[i].x][a[i].y] = g[a[i].y][a[i].x] = v;
        else    g[a[i].x][a[i].y] = g[a[i].y][a[i].x] = min(g[a[i].x][a[i].y], v);
    }
    scanf("%d", &k);
    int set[N], Min[N];
    REP(i, N)   Min[i] = inf;
    sort(a + 1, a + n + 1, cmp);
    kruskal();
    FOR(i, 2, cnt) {    //找到1到其他连通块的最小值
        if(g[1][i] != -1) {
            int x = find(i);
            if(Min[x] > g[1][i]) {
                Min[x] = g[1][i];
                set[x] = i;
            }
        }
    }
    int m = 0;
    FOR(i, 1, cnt) {  //把1跟这些连通块连接起来
        if(Min[i] != inf) {
            m++;
            flag[1][set[i]] = flag[set[i]][1] = true;
            ans += g[1][set[i]];
        }
    }
    //printf("%d\n", ans);
    for(i = m + 1; i <= k; ++i) {  //从度为m+1一直枚举到最大为k，找ans的最小值
        CL(dp, -1);
        dp[1].v = -inf;   //dp初始化
        for(j = 2; j <= cnt; ++j) {
            if(flag[1][j])  dp[j].v = -inf;
        }
        dfs(1, -1);
        int tmp, mi = inf;
        for(j = 2; j <= cnt; ++j) {    
            if(g[1][j] != -1) {
                if(mi > g[1][j] - dp[j].v) {    //找到一条dp到连通块中某个点的边，替换原来连通块中的边（前提是新找的这条边比原来连通块中那条边要大）
                    mi = g[1][j] - dp[j].v;
                    tmp = j;
                }
            }
        }
        if(mi >= 0) break;    //如果不存在这样的边，直接退出
        int x = dp[tmp].x, y = dp[tmp].y;

        flag[1][tmp] = flag[tmp][1] = true;   //加上新找的边
        flag[x][y] = flag[y][x] = false;    //删掉被替换掉的那条边

        ans += mi;
    }
    printf("Total miles driven: %d\n", ans);

    return 0;

}