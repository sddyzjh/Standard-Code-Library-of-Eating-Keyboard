/*
POJ 2096

一个软件有s个子系统，会产生n种bug
某人一天发现一个bug,这个bug属于一个子系统，属于一个分类
每个bug属于某个子系统的概率是1/s,属于某种分类的概率是1/n
问发现n种bug,每个子系统都发现bug的天数的期望。
 
dp[i][j]表示已经找到i种bug,j个系统的bug，达到目标状态的天数的期望
dp[n][s]=0;要求的答案是dp[0][0];
dp[i][j]可以转化成以下四种状态:
     dp[i][j],发现一个bug属于已经有的i个分类和j个系统。概率为(i/n)*(j/s);
     dp[i][j+1],发现一个bug属于已有的分类，不属于已有的系统.概率为 (i/n)*(1-j/s);
     dp[i+1][j],发现一个bug属于已有的系统，不属于已有的分类,概率为 (1-i/n)*(j/s);
     dp[i+1][j+1],发现一个bug不属于已有的系统，不属于已有的分类,概率为 (1-i/n)*(1-j/s);
整理便得到转移方程
*/

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int MAXN = 1010;
double dp[MAXN][MAXN];

int main()
{
	int n, s;
	while (scanf("%d%d", &n, &s) != EOF)
	{
		dp[n][s] = 0;
		for (int i = n; i >= 0; i--)
			for (int j = s; j >= 0; j--)
			{
				if (i == n && j == s)continue;
				dp[i][j] = (i * (s - j) * dp[i][j + 1] + (n - i) * j * dp[i + 1][j] + (n - i) * (s - j) * dp[i + 1][j + 1] + n * s) / (n * s - i * j);
			}
		printf("%.4lf\n", dp[0][0]);
	}
	return 0;
}