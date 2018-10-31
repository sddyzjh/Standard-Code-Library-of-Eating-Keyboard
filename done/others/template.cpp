#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef double db;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;

void sc(int &x){scanf("%d", &x);}
void sc(uint &x){scanf("%u", &x);}
void sc(ll &x){scanf("%lld", &x);}
void sc(ull &x){scanf("%llu", &x);}
void sc(db &x){scanf("%lf", &x);}
void sc(ld &x){scanf("%Lf", &x);}
void sc(char *x){scanf("%s", x);}
void sc(char &x){scanf("%c", &x);}

void pr(const int &x){printf("%d", x);}
void pr(const uint &x){printf("%u", x);}
void pr(const ll &x){printf("%lld", x);}
void pr(const ull &x){printf("%llu", x);}
void pr(const db &x){printf("%lf", x);}
void pr(const ld &x){printf("%Lf", x);}
void pr(const char *x){printf("%s", x);}
void pr(const char &x){printf("%c", x);}

#define sp pr(" ")
#define ln pr("\n")

#define retunr return

#define pb push_back
#define mp make_pair

#define null NULL

#define rep(i,l,r) for (int i = l, lim = r;i <= lim; ++i)
#define repr(i,l,r) for (int i = r, lim = l;i >= lim; --i)

#define fi first
#define se second

#define SET(__set, val) memset(__set, val, sizeof __set)

#define fill(a,v,n) memset((a),(v),sizeof(a[0])*(n))

#define copy(a,b,n) memcpy((a),(b),sizeof(a[0])*(n))

#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())

#define for_each_edge(u) for(int i = point[u];i;i=G[i].n)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 100010;
const int M = 1024;
const int MOD = 1000000007;
void _add(int &a, int b){a = (a+b)%MOD;}
void _sub(int &a, int b){a = (a+MOD-b)%MOD;}
void _mul(int &a, int b){a = (ll)a*b%MOD;}

int _Add(int a, int b){return (a+b)%MOD;}
int _Sub(int a, int b){return (a+MOD-b)%MOD;}
int _Mul(int a, int b){return (ll)a*b%MOD;}

void _max(int &a, int b){a = max(a,b);}
void _min(int &a, int b){a = min(a,b);}

#define gcd __gcd

ll pw(ll a, ll b){ll res(1);while(b){if(b&1)res=res*a%MOD;a=a*a%MOD;b>>=1;}return res;}
ll pwM(ll a, ll b, ll mod){ll res(1);while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}

const int infi = 2147483647;
const ll infl = 9223372036854775807ll;
const db PI = 3.14159265358979323846;

/*
struct E{
	int v, w, n;
}G[N];
int cnt, point[N];
void adde(int u, int v, int w = 0){
	G[++cnt]=(E){v,w,point[u]},point[u]=cnt;
	G[++cnt]=(E){u,w,point[v]},point[v]=cnt;
}
void Ginit(int n){
	cnt = 0;
	fill(point,0,n+1);
}
*/
/*
struct hh{
	int a, b;
	bool operator < (const hh &x) const{
		if(a==x.a)return b<x.b;
		return a<x.a;
	}
}a[N];
*/
int n, m, k, q;
int main(){
	freopen("1", "r", stdin);
/*
	int Case;
	sc(Case);
	rep(ca, 1, Case){
	    printf("Case #%d: ", ca);
	}
*/
	return 0;
}

