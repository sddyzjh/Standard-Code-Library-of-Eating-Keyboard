/*
	MATN为矩阵大小
	MOD为模数
	调用pamt(a,k)返回a^k
*/
struct mat{
	int n, m;
	int c[MATN][MATN];
};
mat cheng(const mat &a, const mat &b){
	mat w;
	SET(w.c,0);
	w.n = a.n, w.m = b.m;
	Rep(i,a.n)Rep(j,b.m)Rep(k,a.m){
		w.c[i][j] += (ll)a.c[i][k] * b.c[k][j] % MOD;
		if(w.c[i][j]>MOD)w.c[i][j]-=MOD;
	}
	return w;
}
mat pmat(mat a, ll k){
	mat i;
	i.n = i.m = MATN;
	SET(i.c,0);
	Rep(i,MATN)
		i.c[i][i] = 1;
	while(k){
		if(k&1)
			i=cheng(i,a);
		a=cheng(a,a);
		k>>=1;
	}
	return i;
}
