/*
	细节看main
	最后结果存在p为下标的数组内
*/
int n;
int a[N],v[N],h[N],sa[2][N],rk[2][N];
int p,q,k;
void init(){
	SET(a,0);
	SET(v,0);
	SET(h,0);
	SET(sa,0);
	SET(rk,0);
}
void calsa(int *sa,int *rk,int *SA,int *RK){
	rep(i,1,n)v[rk[sa[i]]]=i;
	repr(i,1,n)
		if(sa[i]>k)
			SA[v[rk[sa[i]-k]]--]=sa[i]-k;
	rep(i,n-k+1,n)SA[v[rk[i]]--]=i;
	rep(i,1,n)
		RK[SA[i]]=RK[SA[i-1]]+(rk[SA[i-1]]!=rk[SA[i]]||rk[SA[i-1]+k]!=rk[SA[i]+k]);
}
void getsa(){
	p=0,q=1,k=1;
	rep(i,1,n)v[a[i]]++;
	rep(i,1,26)v[i]+=v[i-1];
	rep(i,1,n)sa[p][v[a[i]]--]=i;
	rep(i,1,n)
		rk[p][sa[p][i]]=rk[p][sa[p][i-1]]+(a[sa[p][i]]!=a[sa[p][i-1]]);
	for(k=1;k<n;k<<=1,swap(p,q))
		calsa(sa[p],rk[p],sa[q],rk[q]);
}
void geth(){
	k=0;
	rep(i,1,n)
		if(rk[p][i]==1)h[rk[p][i]]=0;
		else{
			int j=sa[p][rk[p][i]-1];
			while(a[i+k]==a[j+k])k++;
			h[rk[p][i]]=k;
			if(k>0)k--;
		}
}
int main(){
	while(T--){
		init();
		scanf("%s",str+1);
		n = strlen(str+1);
		rep(i,1,n)a[i]=str[i]-'a'+1;
		getsa();
		geth();
		h[0] = h[1] = 0;h[n+1] = 0;
	}
	return 0;
}