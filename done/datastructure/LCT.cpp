struct node{
    node *pa, *ls, *rs;
    int sz;
}T[N], Empty;
inline void Init(node *x){
    x->pa = x->ls = x->rs = &Empty;
    x->sz = 1;
}
inline node *pu(node *x){
    x->sz = 1 + x->ls->sz + x->rs->sz;
    return x;
}
inline node *f(node *x){
    if (x->pa != &Empty)
        return (x->pa->ls == x || x->pa->rs == x) ? x->pa : &Empty;
    return x->pa;
}
inline node *rot(node * x){
    node *fx = f(x), *ffx = f(fx);
    bool c = fx->rs == x, fc = ffx->rs == fx;
    if (fx != &Empty){
        x->pa = fx->pa;
        if (c){
            fx->rs = x->ls;
            if (fx->rs != &Empty)
                fx->rs->pa = fx;
            pu((fx->pa = x)->ls = fx);
        }
        else{
            fx->ls = x->rs;
            if (fx->ls != &Empty)
                fx->ls->pa = fx;
            pu((fx->pa = x)->rs = fx);
        }
        if (ffx != &Empty){
            if (fc)
                ffx->rs = x;
            else
                ffx->ls = x;
        }
    }
    return x;
}
inline node *Splay(node *x, node *p){
    node *fx, *ffx;
    if (x == &Empty)return x;
    for(;(fx = f(x)) != p;rot(x))
        if((ffx = f(fx)) != p)
            rot((ffx->rs == fx) == (fx->rs == x) ? fx : x);
    return pu(x);
}
inline node *Access(node *v){
    node *t = &Empty, *y = v;
    while (1){
        Splay(v, &Empty);
        v->rs = t;
        if (t != &Empty)f(t);
        if (v->pa == &Empty)break;
        pu(v);
        t = v;
        v = t->pa;
    }
    Splay(y, &Empty);
    return y;
}

int n, m;
struct E{
	int v, n;
}G[N];
int cnt, point[N];
void adde(int u, int v){
	G[++cnt]=(E){v,point[u]},point[u]=cnt;
}
void Ginit(){
	cnt = 0;
	fill(point,0,n+1);
}
int fa[N][20];
void lca_init(){
	rep(k,1,19)rep(i,1,n)fa[i][k] = fa[fa[i][k-1]][k-1];
}
int dep[N];
int lca(int u, int v){
	if(dep[u]<dep[v])swap(u,v);
	repr(i,0,19)if(((dep[u]-dep[v])>>i)&1)u = fa[u][i];
	repr(i,0,19)if(fa[u][i]!=fa[v][i])u = fa[u][i], v = fa[v][i];
	if(u == v)return u;
	return fa[u][0];
}
void dfs(int u){
	for(int i = point[u];i;i=G[i].n){
		int v = G[i].v;
		dep[v] = dep[u]+1;
		SET(fa[v],0);
		fa[v][0] = u;
		dfs(v);
	}
}
void splay_init(){
    Empty.pa = Empty.ls = Empty.rs = 0;
    rep(i,1,n)
        Init(&T[i]);
}
int kth(int i, int k){
	int u = i;
	repr(t,0,19)if((k>>t)&1)u = fa[u][t];
	return u;
}
void link(int i, int k){
	if(k > dep[i]){
        T[i].pa = &Empty;
	}else{
        T[i].pa = T+kth(i,k);
    }
}
void modify(int i, int k){
    Access(T+i)->ls->pa = &Empty;
    f(T[i].ls);
    T[i].ls = &Empty;
    pu(&T[i])->pa = k > dep[i] ? &Empty : T+kth(i,k);
}
void ask(int i){
    pr(Access(T+i)->ls->sz+1), ln;
}
int main(){
//	freopen("1", "r", stdin);
	int Case, k, x, a;
	sc(Case);
	rep(ca, 1, Case){
		sc(n);
		splay_init();
		Ginit();
		rep(i,2,n){
			sc(k);
			adde(k,i);
		}
		dfs(1);
		lca_init();
		rep(i,1,n){
			sc(k);
			link(i,k);
		}
		sc(m);
		while(m--){
			sc(k);
			if(k==1){
				sc(x);
				ask(x);
			}else{
				sc(x),sc(a);
				modify(x,a);
			}
		}
	}
	return 0;
}

