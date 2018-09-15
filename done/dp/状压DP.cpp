//CF 580D
//有n种菜，选m种。每道菜有一个权值，有些两个菜按顺序挨在一起会有combo的权值加成。求最大权值
const int maxn = 20;
typedef long long LL;
int a[maxn];
int comb[maxn][maxn];
LL dp[(1 << 18) + 10][maxn];
LL ans = 0;
int n, m, k;
int Cnt(int st){
	int res = 0;
	for (int i = 0; i < n; i++){
		if (st & (1 << i)){
			res++;
		}
	}
	return res;
}
int main(){
	memset(comb, 0, sizeof comb);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < k; i++){
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		x--;
		y--;
		comb[x][y] = c;
	}
	int end = (1 << n);
	memset(dp, 0, sizeof dp);
	for (int st = 0; st < end; st++){
		for (int i = 0; i < n; i++){
			if (st & (1 << i)){
				bool has = false;
				for (int j = 0; j < n; j++){
					if (j != i && (st & (1 << j))){
						has = true;
						dp[st][i] = max(dp[st][i], dp[st ^ (1 << i)][j] + a[i] + comb[j][i]);
					}
				}
				if (!has){
					dp[st][i] = a[i];
				}
			}
			if (Cnt(st) == m){
				ans = max(ans, dp[st][i]);
			}
		}
	}
	cout << ans << endl;
	return 0;
}