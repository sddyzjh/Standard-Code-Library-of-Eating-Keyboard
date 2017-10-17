/*
	计算形式为a[n] = sigma(b[n-i]*c[i])的卷积,结果存在c中
	下标从0开始
	调用juanji(n,b,c)
	P为模数
	G是P的原根
*/
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
void NTT_(ll y[],int len,int on){
	change(y,len);
	for(int h=2;h<=len;h<<=1){
		ll wh=powm(G,(P-1)/h,P);
		if(on<0)wh=powm(wh,P-2,P);
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
		ll I=powm((ll)len,P-2,P);
		Rep(i,len)y[i]=y[i]*I%P;
	}
}
void juanji(int n, ll *b, ll *c){
	int len=1;
	while(len<(n<<1))len<<=1;
	Repab(i,n,len)c[i]= b[i] = 0;
	NTT_(b,len,1);
	NTT_(c,len,1);
	Rep(i,len)
		c[i]= c[i]*b[i]%P;
	NTT_(c,len,-1);
}