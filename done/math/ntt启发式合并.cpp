// 2017 CCPC Hangzhou G
const int MOD = 998244353;
const int G = 3;
const int m1=998244353;
const int NUM = 20;
int WN[2][NUM];
void GetWn(int mod, int wn[]){
	rep(i,0,NUM-1){
		int t = 1<<i;
		wn[i] = pwM(G, (mod - 1) / t,mod);
	}
} 
void NTT(vi &a, int len, int t, int mod, int wn[]){
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
				int t = _Mul(w, a[k+h/2]);
				a[k] = _Add(u, t);
				a[k+h/2] = _Add(u, mod-t);
				w = _Mul(w, wn[id]);
			}
		}
	}
	if(t == -1){
		rep(i,1,len/2-1)swap(a[i], a[len-i]);
		int inv = pw(len, mod-2);
		rep(i,0,len-1)a[i] = _Mul(a[i], inv);
	}
}
int n, m, k, q;
struct VI{
	vector<int> r;
	int len;
	void clear(){
		len = 0;
		r.clear();
	}
	void out(){
		pr(len),pr(':');
		for(auto x:r)pr(' '),pr(x);
		ln;
	}
	VI operator *=(VI &a){
		int L = 1;
		while(L < len+a.len)L <<= 1;
		rep(i,len,L-1)r.pb(0);
		rep(i,a.len,L-1)a.r.pb(0);
		NTT(r,L,1,m1,WN[0]);NTT(a.r,L,1,m1,WN[0]);
		rep(i,0,L-1)r[i] = (ll)r[i]*a.r[i]%m1;
		NTT(r,L,-1,m1,WN[0]);
		while(L-1 >= 1 && r[L-1] == 0)L--;
		r.resize(L);
		len = L;
		return *this;
	}
}A[N];
set<pii> s;
int a[N], b[N];
int jc[N];
int inv[N];
int C(int n, int m){
	return _Mul(jc[n],_Mul(inv[m],inv[n-m]));
}
int main(){
//	freopen("1", "r", stdin);
	n = 100000;
	jc[0] = 1;
	rep(i,1,n)jc[i] = _Mul(jc[i-1],i);
	inv[n] = pw(jc[n],MOD-2);
	repr(i,0,n-1)inv[i] = _Mul(inv[i+1],i+1);
	GetWn(m1,WN[0]);
	int Case;
	sc(Case);
	rep(ca, 1, Case){
		sc(n);
		s.clear();
		m = 0;
		rep(i,1,n){
			sc(a[i]),sc(b[i]);
			m += a[i];
		}
		rep(i,1,n){
			A[i].r.resize(A[i].len = min(a[i],b[i])+1);
			rep(j,0,min(a[i],b[i]))
				A[i].r[j] = _Mul(jc[j],_Mul(C(a[i],j),C(b[i],j)));
			s.insert(mp(A[i].len,i));
		}
		while(s.size() > 1){
			int i = s.begin()->se;
			s.erase(s.begin());
			int j = s.begin()->se;
			s.erase(s.begin());
			A[i] *= A[j];
			A[j].clear();
			s.insert(mp(A[i].len,i));
		}
		int i = s.begin()->se;
		s.erase(s.begin());
		int ans = 0;
		rep(j,0,A[i].len-1){
			_mul(A[i].r[j], jc[m-j]);
			if(j&1)
				_sub(ans,A[i].r[j]);
			else
				_add(ans,A[i].r[j]);
		}
		pr(ans),ln;
	}
	return 0;
}
