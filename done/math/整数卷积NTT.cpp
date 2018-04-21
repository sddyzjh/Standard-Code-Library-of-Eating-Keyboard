/*
	计算形式为a[n] = sigma(b[n-i]*c[i])的卷积,结果存在c中
	下标从0开始
	调用convolution(a,n,b,m,c)
	MOD为模数,CRT合并
*/
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
const ll P=998244353;
const ll G=3;
void change(ll y[],int n){
	int b=n>>1,s=n-1;
	for(int i=1,j=n>>1;i<s;i++){
		if(i<j)swap(y[i],y[j]);
		int k=b;
		while(j>=k){
			j-=k;
			k>>=1;
		}
		j+=k;
	}
}
void NTT(ll y[],int len,int on){
	change(y,len);
	for(int h=2;h<=len;h<<=1){
		ll wh=powM(G,(P-1)/h,P);
		if(on<0)wh=powM(wh,P-2,P);
		for(int i=0;i<len;i+=h){
			ll w=1;
			int r=h>>1;
			for(int k=i,s=r+i;k<s;k++){
				ll u=y[k];
				ll t=w*y[k+r]%P;
				y[k]=u+t;
				if(y[k]>=P)y[k]-=P;
				y[k+r]=u-t;
				if(y[k+r]<0)y[k+r]+=P;
				w=w*wh%P;
			}
		}
	}
	if(on<0){
		ll I=powM((ll)len,P-2,P);
		rep(i,len)y[i]=y[i]*I%P;
	}
}
ll x1[N], x2[N], x3[N], x4[N];
void convolution(ll a[], int l1, ll b[], int l2, ll c[]){
	int len = 1;
	while(len < l1*2 || len < l2*2)len <<= 1;
	rep(i,l1)
		x1[i] = a[i];
	repab(i,l1,len)
		x1[i] = 0;
	rep(i,l2)
		x2[i] = b[i];
	repab(i,l2,len)
		x2[i] = 0;
	NTT(x1,len,1,m1);
	NTT(x2,len,1,m1);
	rep(i,len)
		x3[i] = x1[i]*x2[i]%m1;
	NTT(x3,len,-1,m1);
		
	rep(i,l1)
		x1[i] = a[i];
	repab(i,l1,len)
		x1[i] = 0;
	rep(i,l2)
		x2[i] = b[i];
	repab(i,l2,len)
		x2[i] = 0;
	NTT(x1,len,1,m2);
	NTT(x2,len,1,m2);
	rep(i,len)
		x4[i] = x1[i]*x2[i]%m2;
	NTT(x4,len,-1,m2);
	rep(i,len)
		c[i] = CRT(x3[i], x4[i]);
}