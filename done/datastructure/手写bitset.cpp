/*
	预处理p[i] = 2^i
	保留N位
	get(d)获取d位
	set(d,x)将d位设为x
	count()返回1的个数
	zero()返回是不是0
	print()输出
*/
#define lsix(x) ((x)<<6)
#define rsix(x) ((x)>>6)
#define msix(x) ((x)-(((x)>>6)<<6))
ull p[64] = {1};
struct BitSet{
	ull s[rsix(N-1)+1];
	int cnt;
    void resize(int n){
    	if(n>N)n=N;
	    int t = rsix(n-1)+1;
	    if(cnt<t)
			memset(s+cnt,0,sizeof(ull)*(t-cnt));
		cnt = t;
	}
    BitSet(int n){
    	SET(s,0);
    	cnt=1;
	    resize(n);
	}
    BitSet(){cnt=1;SET(s,0);}
    BitSet operator & (BitSet &that){
	    int len = min(that.cnt, this->cnt);
	    BitSet ans(lsix(len));
	    Repr(i,len)ans.s[i] = this->s[i] & that.s[i];
	    ans.maintain();
	    return ans;
	}
    BitSet operator | (BitSet &that){
	    int len = max(that.cnt, this->cnt);
	    BitSet ans(lsix(len));
	    Repr(i,len)ans.s[i] = this->s[i] | that.s[i];
		ans.maintain();
	    return ans;
	}
    BitSet operator ^ (BitSet &that){
	    int len = max(that.cnt, this->cnt);
	    BitSet ans(lsix(len));
	    Repr(i,len)ans.s[i] = this->s[i] ^ that.s[i];
		ans.maintain();
	    return ans;
	}
    BitSet operator << (int x){
	    int c = rsix(x), r = msix(x);
	    BitSet ans(lsix(cnt+c+(r!=0)));
	    for (int i = min(ans.cnt-1, cnt+c);i-c >= 0; --i){
	    	if(i-c<cnt)
			    ans.s[i] = s[i-c] << r;
		    if (r && i-c-1 >= 0) ans.s[i] |= s[i-c-1] >> (64-r);
		}
		ans.maintain();
	    return ans;
	}
    BitSet operator >> (int x){
	    int c = rsix(x), r = msix(x);
	    BitSet ans(lsix(cnt));
	    if(c>=cnt)return ans;
	    Rep(i,cnt-c){
		    ans.s[i] = s[i+c] >> r;
		    if (r && i+c+1 < cnt) ans.s[i] |= s[i+c+1] << (64-r);
		}
		ans.maintain();
	    return ans;
	}
    int get(int d){
	    int c = rsix(d), r = msix(d);
	    if(c>=cnt)return 0;
	    return (s[c] & p[r]);
	}
    void set(int d, int x){
    	if(d>N)return;
	    int c = rsix(d), r = msix(d);
	    if(c>=cnt)
			resize(lsix(c+1));
	    if(x&&(s[c] & p[r]))return;
	    if(!x&&!(s[c] & p[r]))return;
	    s[c] ^= p[r];
	}
    int count(){
		int res=0;
		Rep(i,cnt){
			ull x = s[i];
			while(x){
				res++;
				x&=x-1;
			}
		}
		return res;
	}
	void maintain(){
		while(s[cnt-1]==0&&cnt>1)
			cnt--;
	    if(lsix(cnt)>N){
			while(lsix(cnt)>N)cnt--;
	   		if(lsix(cnt)<N){
		   		cnt++;
		   		for(int i = 63;i>N-lsix(cnt-1)-1;--i)
	   				if(p[i]&s[cnt-1])s[cnt-1]-=p[i];
	   		}
		}
	}
    bool zero(){
	    Rep(i,cnt)if(s[i])return 0;
	    return 1;
	}
    void print(){
	    if(lsix(cnt)<=N){
			rep(i,N-lsix(cnt))putchar('0');
			Repr(j,64)putchar(p[j] & s[cnt-1]?'1':'0');
		}else{
			Repr(i,N-lsix(cnt-1)-1)
				putchar(p[i] & s[cnt-1]?'1':'0');
		}
	    Repr(i,cnt-2){
		    ull x = s[i];
			Repr(j,64)putchar(p[j] & x?'1':'0');
		}
		putchar('\n');
	}
};
