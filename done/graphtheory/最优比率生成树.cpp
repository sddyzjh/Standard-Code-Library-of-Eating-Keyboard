#include<map>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long 
#define mod 1000000009
#define inf 1000000000
#define eps 1e-8
using namespace std;
int n,cnt;
int x[1005],y[1005],z[1005],last[1005];
double d[1005],mp[1005][1005],ans;
bool vis[1005];
void prim(){
	for(int i=1;i<=n;i++){
		d[i]=inf;vis[i]=0;
	}
	d[1]=0;
	for(int i=1;i<=n;i++){
		int now=0;d[now]=inf;
		for(int j=1;j<=n;j++)if(d[j]<d[now]&&!vis[j])now=j;
		ans+=d[now];vis[now]=1;
		for(int j=1;j<=n;j++)
			if(mp[now][j]<d[j]&&!vis[j])
				d[j]=mp[now][j];
	}
}
double sqr(double x){
	return x*x;
}
double dis(int a,int b){
	return sqrt(sqr(x[a]-x[b])+sqr(y[a]-y[b]));
}
void cal(double mid){
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			mp[i][j]=mp[j][i]=abs(z[i]-z[j])-mid*dis(i,j);
	prim();
}
int main(){
	while(scanf("%d",&n)){
		if(n==0)break;
		for(int i=1;i<=n;i++)
			scanf("%d%d%d",&x[i],&y[i],&z[i]);
		double l=0,r=1000;
		for(int i=1;i<=30;i++)
		{
			double mid=(l+r)/2;
			cal(mid);
			if(ans<0)r=mid;
			else l=mid;
		}
		printf("%.3f\n",l);
	}
	return 0;
}