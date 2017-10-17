/*
	矩阵树定理
	令g为度数矩阵,a为邻接矩阵
	生成树的个数为g-a的任何一个n-1阶主子式的行列式的绝对值
	det(a,n)返回n阶矩阵a的行列式
	所以直接调用det(g-a,n-1)就得到答案
	O(n^3)
	有取模版和double版
	无向图生成树的个数与根无关
	有必选边时压缩边
	有向图以i为根的树形图的数目=基尔霍夫矩阵去掉第i行和第i列的主子式的行列式的值(即Matrix-Tree定理不仅适用于求无向图生成树数目,也适用于求有向图树形图数目)
*/
int det(int a[N][N], int n){
	rep(i,n)
		rep(j,n)
			a[i][j]=(a[i][j]+mod)%mod;
	ll ans=1,f=1;
	rep(i,n){
		repab(j,i+1,n){
			ll A=a[i][i],B=a[j][i];
			while(B!=0){
				ll t=A/B;A%=B;swap(A,B);
				repab(k,i,n)
					a[i][k]=(a[i][k]-t*a[j][k]%mod+mod)%mod;
				repab(k,i,n)
					swap(a[i][k],a[j][k]);
				f=-f;
			}
		}
		if(!a[i][i])return 0;
		ans=ans*a[i][i]%mod;
	}
	if(f==-1)return (mod-ans)%mod;
	return ans;
}
double det(double a[N][N],int n){
	int i, j, k, sign = 0;
	double ret = 1, t;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			b[i][j] = a[i][j];
	for (i = 1; i <= n; i++) {
		if (zero(b[i][i])) {
			for (j = i + 1; j <= n; j++)
				if (!zero(b[j][i]))
					break;
			if (j > n)
				return 0;
			for (k = i; k <= n; k++)
				t = b[i][k], b[i][k] = b[j][k], b[j][k] = t;
			sign++;
		}
		ret *= b[i][i];
		for (k = i + 1; k <= n; k++)
			b[i][k] /= b[i][i];
		for (j = i + 1; j <= n; j++)
			for (k = i + 1; k <= n; k++)
				b[j][k] -= b[j][i] * b[i][k];
	}
	if (sign & 1)
		ret = -ret;
	return ret;
}
/*
	最小生成树计数
*/
#define dinf 1e10
#define linf (LL)1<<60
#define LL long long
#define clr(a,b) memset(a,b,sizeof(a))
LL mod;
struct Edge{
	int a,b,c;
	bool operator<(const Edge & t)const{
		return c<t.c;
	}
}edge[M];
int n,m;
LL ans;
int fa[N],ka[N],vis[N];
LL gk[N][N],tmp[N][N];
vector<int>gra[N];
int findfa(int a,int b[]){return a==b[a]?a:b[a]=findfa(b[a],b);}
LL det(LL a[][N],int n){
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)a[i][j]%=mod;
	long long ret=1;
	for(int i=1;i<n;i++){
		for(int j=i+1;j<n;j++)
			while(a[j][i]){
				LL t=a[i][i]/a[j][i];
				for(int k=i;k<n;k++)
					a[i][k]=(a[i][k]-a[j][k]*t)%mod;
				for(int k=i;k<n;k++)
					swap(a[i][k],a[j][k]);
				ret=-ret;
			}
		if(a[i][i]==0)return 0;
		ret=ret*a[i][i]%mod;
		//ret%=mod;
	}
	return (ret+mod)%mod;
}
int main(){
	while(scanf("%d%d%I64d",&n,&m,&mod)==3){
		if(n==0 && m==0 && mod==0)break;
		memset(gk,0,sizeof(gk));
		memset(tmp,0,sizeof(tmp));
		memset(fa,0,sizeof(fa));
		memset(ka,0,sizeof(ka));
		memset(tmp,0,sizeof(tmp));
		for(int i=0;i<N;i++)gra[i].clear();
		for(int i=0;i<m;i++)
			scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].c);
		sort(edge,edge+m);
		for(int i=1;i<=n;i++)fa[i]=i,vis[i]=0;
		int pre=-1;
		ans=1;
		for(int h=0;h<=m;h++){
			if(edge[h].c!=pre||h==m){
				for(int i=1;i<=n;i++)
					if(vis[i]){
						int u=findfa(i,ka);
						gra[u].push_back(i);
						vis[i]=0;
					}
				for(int i=1;i<=n;i++)
					if(gra[i].size()>1){
						for(int a=1;a<=n;a++)
							for(int b=1;b<=n;b++)
								tmp[a][b]=0;
						int len=gra[i].size();
						for(int a=0;a<len;a++)
							for(int b=a+1;b<len;b++){
								int la=gra[i][a],lb=gra[i][b];
								tmp[a][b]=(tmp[b][a]-=gk[la][lb]);
								tmp[a][a]+=gk[la][lb];tmp[b][b]+=gk[la][lb];
							}
						long long ret=(long long)det(tmp,len);
						ret%=mod;
						ans=(ans*ret%mod)%mod;
						for(int a=0;a<len;a++)fa[gra[i][a]]=i;
					}
				for(int i=1;i<=n;i++){
					ka[i]=fa[i]=findfa(i,fa);
					gra[i].clear();
				}
				if(h==m)break;
				pre=edge[h].c;
			}
			int a=edge[h].a,b=edge[h].b;
			int pa=findfa(a,fa),pb=findfa(b,fa);
			if(pa==pb)continue;
			vis[pa]=vis[pb]=1;
			ka[findfa(pa,ka)]=findfa(pb,ka);
			gk[pa][pb]++;gk[pb][pa]++;
		}
		int flag=0;
		for(int i=2;i<=n&&!flag;i++)if(ka[i]!=ka[i-1])flag=1;
		ans%=mod;
		printf("%I64d\n",flag?0:ans);
	}
	return 0;
}