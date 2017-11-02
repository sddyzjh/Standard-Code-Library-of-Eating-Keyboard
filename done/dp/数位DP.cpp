//HDU-2089 输出不包含4和62的数字的个数
#include <bits/stdc++.h>
using namespace std;
int dp[22][2][10];
int digit[20];
int dps(int pos, int lim, int pre, int alr) //pos:当前位置;lim:是否考虑位数;pre:前一位;alr:已经匹配?
{
    if(pos < 0)
    {
        return alr;
    }
    if(!lim && (dp[pos][alr][pre] != -1))
    {
        return dp[pos][alr][pre];
    }
    int result = 0;
    int len = lim ? digit[pos] : 9;
    for(int i = 0; i <= len; i++)
    {
        result += dps(pos - 1, lim && (i == len), i, alr || (pre == 6 && i == 2)||(i==4));
    }
    if(!lim)
    {
        dp[pos][alr][pre] = result;
    }
    return result;
}
int solve(int x)
{
    memset(dp, -1, sizeof(dp));
    int length = 0;
    while(x)
    {
        digit[length++] = (x % 10);
        x /= 10;
    }
    return dps(length - 1, 1, 0, 0);
}
int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b),a||b)
    {
        printf("%d\n", b-a+1-slove(b>0?b:1)+slove((a-1)>0?(a-1):1));
    }
    return 0;
}