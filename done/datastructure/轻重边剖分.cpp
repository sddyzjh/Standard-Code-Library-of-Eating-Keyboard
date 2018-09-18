
/// 轻重边剖分+dfs序.
/// **节点编号从1开始**.
const int mxn = 105000; // 最大节点数.

int n;              /// 树上的点数.
int vat[mxn];       /// 树上点的初始权值.
int c[mxn];         /// 顶点i属于的链的编号.
int f[mxn];         /// 顶点i的父节点.
int dep[mxn];       /// 节点深度.
int mxi[mxn];       /// 记录点i的重边应该连向哪个子节点.　用于dfs序构建.
int sz[mxn];        /// 子树i的节点个数.
int ct;             /// 链的数量. 也是叶节点数量.
int ch[mxn];        /// 链头节点编号. 从0开始.
int loc[mxn];       /// 节点i在dfs序中的位置. 从0开始.
int til[mxn];       /// 以节点i为根的子树在dfs序中的末尾位置. **闭区间**, 从0开始.

/// 操作子树i的信息　<=> 操作线段树上闭区间 loc[i], til[i].
/// 操作路径信息 <=> 按照LCA访问方式访问线段树上的点.

/// 重新初始化:
et = pool;
memset(eds, 0, sizeof(edge*) * (n + 1));

//////////////////////////////////////////////////////////////////////////

struct edge{ int in; edge*nxt; } pool[mxn<<1];
edge*eds[mxn]; edge*et=pool;
void addedge(int a,int b){ et->in=b; et->nxt=eds[a]; eds[a]=et++; }
#define forsons(e,x) for(edge*e=eds[x];e;e=e->nxt) if(f[x]!=e->in)

void BuildChain(int root) ///　拓扑序搜索(逆向广搜).
{
    static int q[mxn]; int qh = 0, qt = 0;
    f[root]=-1; // 不要修改! 清除根的f标记能够使递推在不清除f数组的情况下正确运行.
    q[qt++]=root;
    dep[root] = 1;
    while(qh != qt)
    {
        int x = q[qh++];
        forsons(e,x) f[e->in] = x, dep[e->in] = dep[x] + 1, q[qt++] = e->in;
    }
    repr(i, 0, n-1)
    {
        int x = q[i];
        sz[x] = 0;
        mxi[x] = -1; // 不要修改! 这个标记不能和节点编号冲突.
        forsons(e, x)
        {
            sz[x] += sz[e->in];
            if(mxi[x] == -1 || sz[e->in] > sz[mxi[x]]) mxi[x] = e->in;
        }
        if(mxi[x] == -1) { sz[x] = 1; ch[ct] = x; c[x] = ct++; continue; } // 叶子. 开一条链.
        c[x] = c[mxi[x]]; ch[c[x]] = x;
    }
}

// 如果不需要dfs序, 只需要节点所在链的信息, 该函数可去掉.
int curl;
void BuildDFSOrder(int x)
{
    loc[x] = curl++;
    if(mxi[x] != -1) BuildDFSOrder(mxi[x]); // dfs序按照重边优先顺序构造, 可以保证所有重边在dfs序上连续.
    forsons(e,x) if(e->in != mxi[x]) BuildDFSOrder(e->in);
    til[x] = curl-1;
}

void HLD(int root)
{
    ct = 0; BuildChain(root);
    curl = 0; BuildDFSOrder(root);
}

/// 求最近公共祖先;
/// 在路径a<->b上执行函数F, 其中第一个参数是底部节点的编号, 第二个是左端界, 第三个是右端界. 闭区间.
int Link(int a, int b, function<void(int,int,int)> const& F)
{
    while(c[a] != c[b])
    {
        if(dep[ch[c[a]]] < dep[ch[c[b]]]) swap(a, b);
        F(a, loc[ch[c[a]]], loc[a]);
        a = f[ch[c[a]]];
    }
    if(dep[a] < dep[b]) swap(a, b);
    F(a, loc[b], loc[a]);
    return b;
}
