/*
	调用init(),且处理出dep数组后
	调用lca(x,y)得到x,y的lca
*/
int p[M], f[N][M];
void init(){
	p[0] = 1;
	rep(i,M-1){
		p[i] = p[i-1]<<1;
		rep(j,n)
			if(f[j][i-1])
				f[j][i] = f[f[j][i-1]][i-1]
	}
}
int lca(int x,int y){
	if(dep[x] > dep[y])
		swap(x, y);
	if(dep[x] < dep[y])
		Rep(i,M)
			if((dep[y] - dep[x]) & p[i])
				y = f[y][i];
	Repr(i,M)
		if(f[x][i] != f[y][i]){
			x = f[x][i];
			y = f[y][i];
		}
	if(x != y)
		return f[x][0];
	return x;
}