#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef double db;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef set<int> si;

int sc(int &x){return scanf("%d", &x);}
int sc(uint &x){return scanf("%u", &x);}
int sc(ll &x){return scanf("%lld", &x);}
int sc(ull &x){return scanf("%llu", &x);}
int sc(db &x){return scanf("%lf", &x);}
int sc(ld &x){return scanf("%Lf", &x);}
int sc(char *x){return scanf("%s", x);}
int sc(char &x){return scanf("%c", &x);}
template<typename T, typename... Args> void sc(T& v, Args&... args) { sc(v); sc(args...); }

void pr(const int &x){printf("%d", x);}
void pr(const uint &x){printf("%u", x);}
void pr(const ll &x){printf("%lld", x);}
void pr(const ull &x){printf("%llu", x);}
void pr(const db &x){printf("%.10lf", x);}
void pr(const ld &x){printf("%.10Lf", x);}
void pr(const char *x){printf("%s", x);}
void pr(const char &x){printf("%c", x);}
template<typename T, typename... Args> void pr(T const& v, Args const& ... args) { pr(v); pr(' '); pr(args...); }

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

#define for_edge(u) for(int i = point[u];i;i = G[i].n)

const int N = 100010;
const int M = 1024;
const int mod = 1000000007;
inline void _add(int &a, int b){a = (a+b)%mod;}
inline void _sub(int &a, int b){a = (a+mod-b)%mod;}
inline void _mul(int &a, int b){a = (ll)a*b%mod;}

inline int _Add(int a, int b){return (a+b)%mod;}
inline int _Sub(int a, int b){return (a+mod-b)%mod;}
inline int _Mul(int a, int b){return (ll)a*b%mod;}

template<typename T>inline void _max(T &a, T b){if(b > a)a = b;}
template<typename T>inline void _min(T &a, T b){if(b < a)a = b;}

#define gcd __gcd

int pw(int a, int b){int res(1);while(b){if(b&1)_mul(res,a);_mul(a,a);b>>=1;}return res;}
int pwM(int a, int b, int m){int res(1);while(b){if(b&1)res=(ll)res*a%m;a=(ll)a*a%m;b>>=1;}return res;}

const int infi = 2147483647;
const ll infl = 9223372036854775807ll;
const db PI = 3.14159265358979323846;
const int inf = 1000000000+100;
/*
struct E{
	int v, w, n;
}G[N*2];
int cnt, point[N];
void add_d(int u, int v, int w = 0){
	G[++cnt]=(E){v,w,point[u]},point[u]=cnt;
}
void add_u(int u, int v, int w = 0){
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