//f[i]表示前缀LIS,g[i]表示长为i的LIS的最小结尾数字
int LIS(int *f, int *g){
	memset(f,0,(n+1)*sizeof(int));
	f[1] = 1;
	memset(g,127,(n+1)*sizeof(int));
	g[0] = -infi;
	int nmax = 1;
	g[nmax] = a[1];
	rep(i,2,n){
		int v = lower_bound(g,g+nmax+1,a[i])-g-1;
		f[i] = v+1;
		nmax = max(nmax, v+1);
		g[v+1] = min(g[v+1], a[i]);
	}
	return nmax;
}