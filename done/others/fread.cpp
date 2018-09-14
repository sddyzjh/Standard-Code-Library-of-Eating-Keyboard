// sc(x) pr(x)
#define BUF_SIZE 100000
bool IOerror = 0;
inline char nc(){//next char
	static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
	if(p1 == pend){
		p1 = buf;
		pend = buf + fread(buf, 1, BUF_SIZE, stdin);
		if(pend == p1){
			IOerror = 1;
			return -1;
		}
	}
	return *p1++;
}
inline bool blank(char ch){
	return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}
inline int sc(int &x){
	char ch;
	int sgn = 1;
	while(blank(ch = nc()));
	if(IOerror)
		return -1;
	if(ch=='-')sgn=-1,ch=nc();
	for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	x*=sgn;
	return 1;
}
inline void pr(int x){
	if (x == 0){
		putchar('0');
		return;
	}
	short i, d[19];
	for (i = 0;x; ++i)
		d[i] = x % 10, x /= 10;
	while (i--)
		putchar(d[i] + '0');
}
#undef BUF_SIZE