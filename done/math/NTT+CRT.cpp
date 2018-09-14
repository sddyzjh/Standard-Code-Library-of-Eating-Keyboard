/*
	计算形式为a[n] = sigma(b[n-i]*c[i])的卷积,结果存在c中
	下标从0开始
	调用convolution(a,n,b,m,c)
	MOD为模数,CRT合并
	若模数为m1，卷积做到x3，把x3替换为c
	首先调用GetWn(m1,WN[0]),GetWn(m2,WN[1])
	模数满足的性质为mod=2^k*(奇数)+1 2^k>2n时可以在模意义下做FFT
	998244353 = 2^23*7*17+1
	1004535809 = 2^21*479+1
*/
const int G = 3;
const int MOD=1000003,m1=998244353,m2=1004535809;
const ll P=1002772198720536577LL;
inline ll mul(ll a,ll b){
	ll d=(ll)floor(a*(double)b/P+0.5);
	ll ret=a*b-d*P;
	if(ret<0)ret+=P;
	return ret;
}
inline int CRT(int r1,int r2){
	ll a = mul(r1,m2);
	a = mul(a,332747959ll);
	ll b = mul(r2,m1);
	b = mul(b,669690699ll);
	a = (a+b)%P;
	return a%MOD;
}
int mul(int x, int y, int mod){
	ll z = 1LL*x*y;
	return z-z/mod*mod;
}
int add(int x, int y, int mod){
	x += y;
	if(x >= mod)x -= mod;
	return x;
}
const int NUM = 20;
int WN[2][NUM];
void GetWn(int mod, int wn[]){
	rep(i,0,NUM-1){
		int t = 1<<i;
		wn[i] = pwM(G, (mod - 1) / t, mod);
	}
} 
void NTT(int a[], int len, int t, int mod, int wn[]){
	for(int i = 0,j = 0;i < len; ++i){
		if(i > j)swap(a[i], a[j]);
		for(int l = len >> 1;(j ^= l) < l;l >>= 1);
	}
	int id = 0;
	for(int h = 2;h <= len;h <<= 1){
		id++;
		for(int j = 0;j < len;j += h){
			int w = 1;
			for(int k = j;k < j+h/2; ++k){
				int u = a[k];
				int t = mul(w, a[k+h/2], mod);
				a[k] = add(u, t, mod);
				a[k+h/2] = add(u, mod-t, mod);
				w = mul(w, wn[id], mod);
			}
		}
	}
	if(t == -1){
		rep(i,1,len/2-1)swap(a[i], a[len-i]);
		int inv = pwM(len, mod-2, mod);
		rep(i,0,len-1)a[i] = mul(a[i], inv, mod);
	}
}
int x1[N], x2[N], x3[N], x4[N];
void convolution(ll a[], int l1, ll b[], int l2, ll c[]){
	int len = 1;
	while(len < l1*2 || len < l2*2)len <<= 1;
	rep(i,0,l1-1)x1[i] = a[i]%m1;
	rep(i,l1,len-1)x1[i] = 0;
	rep(i,0,l2-1)x2[i] = b[i]%m1;
	rep(i,l2,len-1)x2[i] = 0;
	NTT(x1,len,1,m1,WN[0]);NTT(x2,len,1,m1,WN[0]);
	rep(i,0,len-1)x3[i] = (ll)x1[i]*x2[i]%m1;
	NTT(x3,len,-1,m1,WN[0]);
	// 单模数到这里结束
	rep(i,0,l1-1)x1[i] = a[i]%m2;
	rep(i,l1,len-1)x1[i] = 0;
	rep(i,0,l2-1)x2[i] = b[i]%m2;
	rep(i,l2,len-1)x2[i] = 0;
	NTT(x1,len,1,m2,WN[1]);NTT(x2,len,1,m2,WN[1]);
	rep(i,0,len-1)x4[i] = (ll)x1[i]*x2[i]%m2;
	NTT(x4,len,-1,m2,WN[1]);
	// 合并两次卷积的结果
	rep(i,0,len-1)c[i] = CRT(x3[i], x4[i]);
}