/*
	合并ai在模mi下的结果为模m_0*m_1*...*m_n-1
*/
inline int exgcd(int a, int b, int &x, int &y){
	if(!b){
		x = 1, y = 0;
		return a;
	}
	else{
		int d = exgcd(b, a % b, x, y), t = x;
		x = y, y = t - a / b * y;
		return d;
	}
}
inline int inv(int a, int p){
	int d, x, y;
	d = exgcd(a, p, x, y);
	return d == 1 ? (x + p) % p : -1;
}
int china(int n,int *a,int *m){
	int __M = MOD - 1, d, x = 0, y;
	for(int i = 0;i < n; ++i){
		int w = __M / m[i];
		d = exgcd(m[i], w, d, y);
		x = (x + ((long long)y*w%__M)*(long long)a[i]%__M)%__M;
	}
	while(x <= 0)
		x += __M;
	return x;
}