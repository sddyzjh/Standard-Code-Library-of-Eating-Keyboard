/*
	以某个点为起点的欧拉回路数=该点为根的树形图数*(所有点出度-1)的乘积
	从1出发的欧拉回路的数量
	重边当作多种方案
*/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define each(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define reach(i, n) for (int(i) = n - 1; (i) >= 0; (i)--)
#define range(i, st, en) for (int(i) = (st); (i) <= (en); (i)++)
#define rrange(i, st, en) for (int(i) = (en); (i) >= (st); (i)--)
#define fill(ary, num) memset((ary), (num), sizeof(ary))

using namespace std;
typedef long long ll;

const int maxn = 410;
const int mod = 998244353;

int d[maxn][maxn], g[maxn][maxn];
ll c[maxn][maxn];
int in[maxn], mul[(int)2e5 + 10], out[maxn];

int n;

ll getDet(ll a[][maxn], int n)
{
    range(i, 1, n) range(j, 1, n) a[i][j] = (a[i][j] + mod) % mod;
    ll ret = 1;
    range(i, 2, n)
    {
        range(j, i + 1, n) while (a[j][i])
        {
            ll t = a[i][i] / a[j][i];
            range(k, i, n) a[i][k] = (a[i][k] - a[j][k] * t % mod + mod) % mod;
            range(k, i, n) swap(a[i][k], a[j][k]);
            ret = -ret;
        }
        if (a[i][i] == 0)
            return 0;
        ret = ret * a[i][i] % mod;
    }
    return (ret + mod) % mod;
}

ll fastPow(ll n, ll m)
{
    ll ans = 1;
    while (m) {
        if (m & 1)
            ans = ans * n % mod;
        n = n * n % mod;
        m >>= 1;
    }
    return ans;
}

bool judgeEuler()
{
    range(i, 1, n) if (in[i] != out[i]) return false;
    return true;
}

int main()
{
    int cas = 0;
    mul[0] = mul[1] = 1;
    range(i, 2, (int)(2e5 + 5)) mul[i] = (mul[i - 1] * 1LL * i) % mod;
    while (scanf("%d", &n) != EOF) {
        fill(in, 0), fill(d, 0), fill(out, 0);
        range(i, 1, n) range(j, 1, n)
        {
            scanf("%d", &g[i][j]);
            d[j][j] += g[i][j];
            in[j] += g[i][j];
            out[i] += g[i][j];
        }
        if (!judgeEuler()) {
            printf("Case #%d: 0\n", ++cas);
            continue;
        } else if (n == 1) {
            printf("Case #%d: %d\n", ++cas, mul[g[1][1]]);
            continue;
        }
        range(i, 1, n) range(j, 1, n) c[i][j] = d[i][j] - g[i][j];
        ll trees = getDet(c, n) % mod * mul[in[1]] % mod;
        range(i, 2, n) trees = trees * mul[in[i] - 1] % mod;
        range(i, 1, n) range(j, 1, n) trees = trees * fastPow(mul[g[i][j]], mod - 2) % mod;
        printf("Case #%d: %lld\n", ++cas, trees);
    }
    return 0;
}
/*
	欧拉回路：每条边恰走一次的回路
	欧拉通路：每条边恰走一次的路径
	欧拉图：存在欧拉回路的图
	半欧拉图：存在欧拉通路的图
	有向欧拉图：每个点入度=出度	
	无向欧拉图：每个点度数为偶数
	有向半欧拉图：一个点入度=出度+1，一个点入度=出度-1，其他点入度=出度
	无向半欧拉图：两个点度数为奇数，其他点度数为偶数
*/