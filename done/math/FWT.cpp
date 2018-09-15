void fwt1(int *a, int len){
	for(int i=0;i<len;i+=2)
		_add(a[i+1],a[i]);
	for(int i=4;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<i/2;k+=2){
				_add(a[j+k+i/2],a[j+k]);
				_add(a[j+k+i/2+1],a[j+k+1]);
			}
}
void fwt2(int *a, int len){
	for(int i=0;i<len;i+=2)
		_sub(a[i+1],a[i]);
	for(int i=4;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<i/2;k+=2){
				_sub(a[j+k+i/2],a[j+k]);
				_sub(a[j+k+i/2+1],a[j+k+1]);
			}
}
void fwt3(int *a, int len){
	for(int i=2;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<i/2;k++){
				int u=a[j+k];
				int v=a[j+k+i/2];
				_add(a[j+k],v);
				_sub(u,v);
				a[j+k+i/2]=u;
			}
}
void fwt4(int *a, int len){
	for(int i=2;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<i/2;k++){
				int u=a[j+k];
				int v=a[j+k+i/2];
				_add(a[j+k],v);
				_sub(u,v);
				a[j+k+i/2]=u;
			}
	ll inv=pw(len%MOD,MOD-2);
	for(int i=0;i<len;i++)
		_mul(a[i],inv);
}
void fwt5(int *a, int len){
	for(int i=2;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<i/2;k++)
				_add(a[j+k],a[j+k+i/2]);
}
void fwt6(int *a, int len){
	for(int i=2;i<=len;i<<=1)
		for(int j=0;j<len;j+=i)
			for(int k=0;k<i/2;k++)
				_sub(a[j+k],a[j+k+i/2]);
}
int bitcount[N];
int a1[18][N],a2[18][N];
void or_conv(int *a,int *b,int *c, int len){
	for(int i=0;i<len;i++)
		a1[bitcount[i]][i]=a[i];
	int width=bitcount[len-1];
	for(int i=0;i<=width;i++)
		fwt1(a1[i],len);
	for(int i=width;i>=0;i--)
		for(int j=0;j<=i;j++)
			for(int k=0;k<len;k++)
				a2[i][k]=(a2[i][k]+(ll)a1[i-j][k]*a1[j][k])%MOD;
	for(int i=0;i<=width;i++)
		fwt2(a2[i],len);
	for(int i=0;i<len;i++)
		c[i]=a2[bitcount[i]][i];
}
void xor_conv(int *a,int *b,int *c, int len){
	static int a1[N],a2[N];
	memcpy(a1,a,sizeof a1);
	memcpy(a2,b,sizeof a2);
	fwt3(a1,len);
	fwt3(a2,len);
	for(int i=0;i<len;i++)
		a1[i]=(ll)a1[i]*a2[i]%MOD;
	fwt4(a1,len);
	memcpy(c,a1,sizeof a1);
}
void and_conv(int *a,int *b,int *c, int len){
	static int a1[N],a2[N];
	memcpy(a1,a,sizeof a1);
	memcpy(a2,b,sizeof a2);
	fwt5(a1,len);
	fwt5(a2,len);
	for(int i=0;i<len;i++)
		a1[i]=(ll)a1[i]*a2[i]%MOD;
	fwt6(a1,len);
	memcpy(c,a1,sizeof a1);
}