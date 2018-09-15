inline int lowbit(int x){return x&-x;}
//前缀和,可改前缀最值
void update(int d, int x=1){
	if(!d)return;
	while(d<=n){
		T[d]+=x;
		d+=lowbit(d);
	}
}
int ask(int d){
	int res(0);
	while(d>0){
		res+=T[d];
		d-=lowbit(d);
	}
	return res;
}