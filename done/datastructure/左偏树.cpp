int n,m,root,add;
struct node{
	int key,l,r,fa,add;
}heap1[maxn*2+1],heap2[maxn*2+1];
void down(int x){
	heap1[heap1[x].l].key+=heap1[x].add;
	heap1[heap1[x].l].add+=heap1[x].add;
	heap1[heap1[x].r].key+=heap1[x].add;
	heap1[heap1[x].r].add+=heap1[x].add;
	heap1[x].add=0;
}
int fa(int x){
	int tmp=x;
	while (heap1[tmp].fa) tmp=heap1[tmp].fa;
	return tmp;
}
int sum(int x){
	int tmp=x,sum=0;
	while (tmp=heap1[tmp].fa) sum+=heap1[tmp].add;
	return sum;
}
int merge1(int x,int y){
	if (!x || !y) return x?x:y;
	if (heap1[x].key<heap1[y].key) swap(x,y);
	down(x);
	heap1[x].r=merge1(heap1[x].r,y);
	heap1[heap1[x].r].fa=x;
	swap(heap1[x].l,heap1[x].r);
	return x;
}
int merge2(int x,int y){
	if (!x || !y) return x?x:y;
	if (heap2[x].key<heap2[y].key) swap(x,y);
	heap2[x].r=merge2(heap2[x].r,y);
	heap2[heap2[x].r].fa=x;
	swap(heap2[x].l,heap2[x].r);
	return x;
}
int del1(int x){
	down(x);
	int y=merge1(heap1[x].l,heap1[x].r);
	if (x==heap1[heap1[x].fa].l) heap1[heap1[x].fa].l=y;else heap1[heap1[x].fa].r=y;
	heap1[y].fa=heap1[x].fa;
	return fa(y);
}
void del2(int x){
	int y=merge2(heap2[x].l,heap2[x].r);
	if (root==x) root=y;
	if (x==heap2[heap2[x].fa].l) heap2[heap2[x].fa].l=y;else heap2[heap2[x].fa].r=y;
	heap2[y].fa=heap2[x].fa;
}
void renew1(int x,int v){
	heap1[x].key=v;
	heap1[x].fa=heap1[x].l=heap1[x].r=0;
}
void renew2(int x,int v){
	heap2[x].key=v;
	heap2[x].fa=heap2[x].l=heap2[x].r=0;
}
//建树
int heapify(){
	queue<int> Q;
	for (int i=1;i<=n;++i) Q.push(i);
	while (Q.size()>1){
		int x=Q.front();Q.pop();
		int y=Q.front();Q.pop();
		Q.push(merge2(x,y));
	}
	return Q.front();
}
//合并两棵树
void U(){
	int x,y;scanf("%d%d",&x,&y);
	int fx=fa(x),fy=fa(y);
	if (fx!=fy) if (merge1(fx,fy)==fx) del2(fy);else del2(fx);
}
//单点修改
void A1(){
	int x,v;scanf("%d%d",&x,&v);
	del2(fa(x));
	int y=del1(x);
	renew1(x,heap1[x].key+v+sum(x));
	int z=merge1(y,x);
	renew2(z,heap1[z].key);
	root=merge2(root,z);
}
//联通块修改
void A2(){
	int x,v,y;scanf("%d%d",&x,&v);
	del2(y=fa(x));
	heap1[y].key+=v;
	heap1[y].add+=v;
	renew2(y,heap1[y].key);
	root=merge2(root,y);
}
//全局修改
void A3(){
	int v;scanf("%d",&v);
	add+=v;
}
//单点查询
void F1(){
	int x;scanf("%d",&x);
	printf("%d\n",heap1[x].key+sum(x)+add);
}
//联通块最大值
void F2(){
	int x;scanf("%d",&x);
	printf("%d\n",heap1[fa(x)].key+add);
}
//全局最大值
void F3(){
	printf("%d\n",heap2[root].key+add);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",&heap1[i].key),heap2[i].key=heap1[i].key;
	root=heapify();
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%s",s);
		if (s[0]=='U') U();
		if (s[0]=='A'){
			if (s[1]=='1') A1();
			if (s[1]=='2') A2();
			if (s[1]=='3') A3();
		}
		if (s[0]=='F'){
			if (s[1]=='1') F1();
			if (s[1]=='2') F2();
			if (s[1]=='3') F3();
		}
	}
	return 0;
}