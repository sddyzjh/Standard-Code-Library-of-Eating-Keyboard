/*HDOJ2829
题目大意：给定一个长度为n的序列，至多将序列分成m段，每段序列都有权值，权值为序列内两个数两两相乘之和。m<=n<=1000. 令权值最小。
状态转移方程:
dp[c][i]=min(dp[c][i],dp[c-1][j]+w[j+1][i])
url->:http://blog.csdn.net/bnmjmz/article/details/41308919
*/

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 1 << 30;
const int MAXN = 1000 + 10;
typedef long long LL;
LL dp[MAXN][MAXN];//dp[c][j]表示前j个点切了c次后的最小权值
int val[MAXN];
int w[MAXN][MAXN];//w[i][j]表示i到j无切割的权值
int s[MAXN][MAXN];//s[c][j]表示前j个点切的第c次的位置
int sum[MAXN];
int main()
{
	int n, m;
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0)break;
		memset(s, 0, sizeof(s));
		memset(w, 0, sizeof(w));
		memset(dp, 0, sizeof(dp));
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &val[i]);
			sum[i] += sum[i - 1] + val[i];
		}
		for (int i = 1; i <= n; ++i)
		{
			w[i][i] = 0;
			for (int j = i + 1; j <= n; ++j)
			{
				w[i][j] = w[i][j - 1] + val[j] * (sum[j - 1] - sum[i - 1]);
			}
		}
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= m; ++j)
			{
				dp[j][i] = INF;
			}
		}
		for (int i = 1; i <= n; ++i)
		{
			dp[0][i] = w[1][i];
			s[0][i] = 0;
		}
		for (int c = 1; c <= m; ++c)
		{
			s[c][n + 1] = n; //设置边界
			for (int i = n; i > c; --i)
			{
				int tmp = INF, k;
				for (int j = s[c - 1][i]; j <= s[c][i + 1]; ++j)
				{
					if (dp[c - 1][j] + w[j + 1][i] < tmp)
					{
						tmp = dp[c - 1][j] + w[j + 1][i]; //状态转移方程，j之前切了c-1次，第c次切j到j+1间的
						k = j;
					}
				}
				dp[c][i] = tmp;
				s[c][i] = k;
			}
		}
		printf("%d\n", dp[m][n]);
	}
	return 0;
}