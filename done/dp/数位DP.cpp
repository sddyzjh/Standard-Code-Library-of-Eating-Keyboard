//HDU-2089 输出不包含4和62的数字的个数

int dp[10][10];
int k = 0;
int dig[100];

void init()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 7; i++){
        for (int j = 0; j < 10; j++){
            for (int k = 0; k < 10; k++){
                if (j != 4 && !(j == 6 && k == 2)){
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }
}

int  solve (int num)
{
    int ret = num, ans = 0;
    memset(dig, 0, sizeof(dig));
    k = 1;
    while (ret > 0)
    {
        dig[k++] = ret % 10;
        ret /= 10;
    }
    for (int i = k; i > 0; i--)
    {
        for (int j = 0; j < dig[i]; j++)
        {
            if (!(j == 2 && dig[i + 1] == 6) && j != 4)
            {
                ans += dp[i][j];
            }
        }
        if (dig[i] == 4 || (dig[i] == 2 && dig[i + 1] == 6))
        {
            break;
        }
    }
    return ans;
}

int main() {
    int n, m;
    init();
    while (cin >> n >> m && (n + m))
    {
        int ans = solve(m + 1) - solve(n);
        cout << ans << endl;
    }
    return 0;
}
