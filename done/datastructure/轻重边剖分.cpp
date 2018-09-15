/// 轻重边剖分+dfs序.
const int mxn = 105000; // 最大节点数.

/// n: 实际点数.
/// c[i]: 顶点i属于的链的编号.
/// f[i]: 顶点i的父节点.
/// mxi[i]: 记录点i的重边应该连向哪个子节点.　用于dfs序构建.
/// sz[i]: 子树i的节点个数.
int n;
int c[mxn];
int f[mxn];
int mxi[mxn];
int sz[mxn];
/// ct: 链数.
/// ch[i]: 链头节点编号.
int ct;
int ch[mxn];
/// loc[i]: 节点i在dfs序中的位置.
/// til[i]: 子树i在dfs序中的末尾位置.
int loc[mxn];
int til[mxn];

/// 操作子树i的信息　<=> 操作线段树上闭区间 loc[i], til[i].
/// 操作路径信息 <=> 按照LCA访问方式访问线段树上的点.

/// 重新初始化:
et = pool;
for(int i=0; i<n; i++) eds[i] = NULL;

//////////////////////////////////////////////////////////////////////////


struct edge{ int in; edge*nxt; } pool[mxn<<1];
edge*eds[mxn]; edge*et=pool;
void addedge(int a,int b){ et->in=b; et->nxt=eds[a]; eds[a]=et++; }
#define FOREACH_EDGE(e,x) for(edge*e=eds[x];e;e=e->nxt)
#define FOREACH_SON(e,x) for(edge*e=eds[x];e;e=e->nxt) if(f[x]!=e->in)

int q[mxn]; int qh,qt;
void BuildChain(int root) ///　拓扑序搜索(逆向广搜).　防爆栈.
{
    f[root]=-1; // 不要修改! 用于在走链时判断是否走到头了.
    q[qt++]=root;
    while(qh!=qt) { int x = q[qh++]; FOREACH_SON(e,x) { f[e->in] = x; q[qt++] = e->in;} }
    for(int i=n-1; i>=0; i--)
    {
        int x = q[i];
        sz[x] = 0;
        if(!eds[x]) { sz[x] = 1; ch[ct] = x; c[x] = ct++; continue; }        
        int mxp = eds[x]->in;
        FOREACH_SON(e,x)
        {
            sz[x] += sz[e->in];
            if(sz[e->in] > sz[mxp]) mxp = e->in;
        }
        c[x] = c[mxi[x] = mxp]; ch[c[x]] = x;
    }
}

// 如果不需要dfs序, 只需要节点所在链的信息, 该函数可以放空.
int curl;
void BuildDFSOrder(int x)
{
    loc[x] = curl++;
    if(eds[x]) BuildDFSOrder(mxi[x]); // dfs序按照重边优先顺序构造, 可以保证所有重边在dfs序上连续.
    FOREACH_SON(e,x) if(e->in != mxi[x]) BuildDFSOrder(e->in);
    til[x] = curl-1;
}

void HLD(int root)
{
    ct = 0;
    BuildChain(root);
    curl = 0;
    BuildDFSOrder(root);
}

/// 线段树.
#define L (x<<1)
#define R (x<<1|1)
int t[mxn<<3];
int tag[mxn<<3];

inline void pushtag(int x,int l,int r)
{
    if(tag[x]==0) return;
    tag[L] = tag[R] = tag[x];
    int mid = (l+r)>>1;
    if(tag[x]==-1) { t[L]=t[R]=0; }
    else if(tag[x]==1) { t[L]=mid-l+1; t[R]=r-mid; }
    tag[x]=0;
}
inline void Update(int x,int l,int r)
{ t[x] = t[L] + t[R]; }

int cl, cr, cv;
void Change(int x=1, int l=0, int r=n-1)
{
    if(cr<l || r<cl) return;
    if(cl<=l && r<=cr)
        { tag[x] = cv; t[x] = ( tag[x]==-1 ? 0 : r-l+1 ); return; }
    pushtag(x,l,r);
    int mid = (l+r)>>1;
    Change(L,l,mid); Change(R,mid+1,r); Update(x,l,r);
}
void Modify(int l,int r,int v) { cl=l; cr=r; cv=v; Change(); }

int ql,qr;
int Query(int x=1, int l=0, int r=n-1)
{
    pushtag(x,l,r);
    if(qr<l || r<ql) return 0;
    if(cl<=l && r<=cr) return t[x];
    int mid = (l+r)>>1;
    return Query(L,l,mid) + Query(R,mid+1,r);
}
int GetTotalSum() { return t[1]; }

/// 修改到根的路径上的信息.　按需更改.
void Install(int p)
{
    do{
        Modify(loc[ch[c[p]]], loc[p], 1);
        p=f[ch[c[p]]];
    }
    while(p!=-1);
}

/// 修改子树信息. 按需更改.
void Remove(int p)
{
    Modify(loc[p], til[p], -1);
}
