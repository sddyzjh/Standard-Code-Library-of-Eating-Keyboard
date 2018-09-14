//POJ 2411
//一个row*col的矩阵，希望用2*1或者1*2的矩形来填充满，求填充的总方案数
//输入为长和宽
#define LL long long 
const int maxn=2053;
struct Node{
	int H[maxn];
	int S[maxn];
	LL N[maxn];
	int size;
	void init(){
		size=0;
		memset(H,-1,sizeof(H));
	}
	void push(int SS,LL num){
		int s=SS%maxn;
		while( ~H[s] && S[H[s]]!=SS )
			s=(s+1)%maxn;

		if(~H[s]){
			N[H[s]]+=num;
		}
		else{
			S[size]=SS;
			N[size]=num;
			H[s]=size++;
		}
	}
	LL get(int SS){
		int s=SS%maxn;
		while( ~H[s] && S[H[s]]!=SS )
			s=(s+1)%maxn;

		if(~H[s]){
			return N[H[s]];
		}
		else{
			return 0;
		}
	}
}dp[2];
int now,pre;
int get(int S,int p,int l=1){
	if(p<0) return 0;
	return (S>>(p*l))&((1<<l)-1);
}
void set(int &S,int p,int v,int l=1){
	S^=get(S,p,l)<<(p*l);
	S^=(v&((1<<l)-1))<<(p*l);
}
int main(){
	int n,m;
	while( scanf("%d%d",&n,&m),n||m ){
		if(n%2 && m%2) {puts("0");continue;}
		int now=1,pre=0;
		dp[now].init();
		dp[now].push(0,1);
		for(int i=0;i<n;i++) for(int j=0;j<m;j++){
			swap(now,pre);
			dp[now].init();
			for(int s=0;s<dp[pre].size;s++){
				int S=dp[pre].S[s];
				LL num=dp[pre].N[s];
				int p=get(S,j);
				int q=get(S,j-1);
				int nS=S;
				set(nS,j,1-p);
				dp[now].push(nS,num);
				if(p==0 && q==1){
					set(S,j-1,0);
					dp[now].push(S,num);
				}
			}
		}
		printf("%lld\n",dp[now].get(0));
	}
}