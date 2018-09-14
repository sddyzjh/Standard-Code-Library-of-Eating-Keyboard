/*
	用法类似sam
	本质不同的回文串有O(n)个
	回文树有两个根
	a向b有一个c的转移表示对a表示的回文串两端都加上c变成b
	分别为even,odd，长度分别是0和-1
	len为一个点代表的字符串的实际长度
	suffix为这个点失配后的最长回文后缀，且下标比i小
	n是自动机的边
	cnt是出现次数，向suffix传递，需要调用calc()
*/
struct PAM{
	char str[N];
	int n[N][M], suffix[N], len[N], cnt[N];
	int tot, suf;
	int newnode(){
		int i = tot++;
		SET(n[i],0);
		suffix[i] = len[i] = cnt[i] = 0;
		return i;
	}
	void init(){
		tot = 0;
		int p = newnode(), q = newnode();
		len[p] = 0;
		suffix[p] = q;
		len[q] = -1;
		suffix[q] = q;
		suf = 0;
	}
	int getfail(int x, int l){
		while(str[l-1-len[x]] != str[l])
			x = suffix[x];
		return x;
	}
	int insert(int x){
		int c = str[x]-'a';
		int p = getfail(suf,x);
		if(!n[p][c]){
			int q = newnode();
			len[q] = len[p]+2;
			suffix[q] = n[getfail(suffix[p],x)][c];
			n[p][c] = q;
		}
		p = n[p][c];
		cnt[p]++;
		suf = p;
		return suf;
	}
	void calc(){
		repr(i,0,tot-1)
			cnt[suffix[i]] += cnt[i];
	}
	void debug(){
		rep(i,0,tot-1){
			pr(i),sp,pr(suffix[i]),sp,pr(cnt[i]),ln;
			rep(j,0,M-1)if(n[i][j])putchar('a'+j),sp,pr(n[i][j]),ln;
		}
	}
	void solve(){
		init();
		cin>>str;
		rep(i,0,strlen(str)-1)
			insert(i);
	}
};
