/// Tarjan 割点, 割边和双联通分量
///
/// 割点: 删除后使原图(边)双联通分量增加的点
/// 割边: 删除后是原图(边)双联通分量增加的边
///
/// 基于如下定理:
/// 一个点是割点当且仅当:
///    1. 这个点是搜索树的根, 并且该根的子树超过一个.
///    2. 这个点不是搜索树的根, 且存在一个子节点, 子节点不存在绕过其父节点返回其祖先的路径.
/// 一条边是割边当且仅当:
///    1. 在搜索树上, 这条边是树边, 并且子节点不存在绕过其父节点返回其祖先的路径.
///
/// 注意一个割点可能会被不止一个点双联通分量包含.
///
/// 一个图按照点双联通分量缩边后是一条链.
/// 因而凡是搜索树中的横叉边, 一定是连接一个双联通分量中的两点的边.
/// 因而使用横叉边更新low值是正确的.
/// 每找到一个割点, 将子树所有边出栈, 它们属于同一个点双.
///
/// 点双: 至少两个环公用一条路.
/// 边双: 至少两个环公用一个点.
///
///////////////////////////////////////////////////////////////////////////////

/// dfs编号 dfn 从1开始.
/// 块编号 bcnt 从1开始.

// AC 洛谷 P3388 (无向图割点)

int n, m, bcnt;
int dfn[mxn], low[mxn], ft[mxn];
bool used[mxn], ins[mxn];
int dfx = 0;

int ans[mxn]; int anst = 0; // 存割点.

void Reset()
{
    et = pool;
    eg = dfx = anst = 0;
    memset(used, 0, sizeof(bool) * (n + 1));
}

void DFS(int x, bool rt = true)
{
    low[x] = dfn[x] = ++dfx;
    used[x] = true;
    int cut = 0;
    foredges(e, x)
    {
        if(!used[e->in])
        {
            ft[e->in] = x;
            DFS(e->in, false);
            low[x] = min(low[x], low[e->in]);
            if(low[e->in] >= dfn[x]) cut++;
        }
        else if(e->in != ft[x])
        {
            low[x] = min(low[x], dfn[e->in]);
        }
    }
    if(cut > rt)
    {
        ans[anst++] = x; // 记录割点.
    }
}



int main()
{
    n = getint();
    m = getint();
    rep(i, 1, m)
    {
        int a = getint();
        int b = getint();
        addedge(a, b);
        addedge(b, a);
    }
    
    rep(i, 1, n) if(!used[i]) DFS(i);
    
    sort(ans, ans + anst);
    printf("%d\n", anst);
    rep(i, 0, anst-1) printf("%d ", ans[i]);
}

///////////////////////////////////////////////////////////////////////////////

/// dfs编号 dfn 从1开始.
/// 点双编号从 1 开始.
/// 注意每条边只有一个方向会被标记. 未标记的边, 所属点双应该记为 0.

// AC HDU 3394 (无向图割边和点双)

const int mxn = 1e5 + 50; // 点数
const int mxm = 2e5 + 50; // 单向边数
struct edge { int in; edge* nxt; int blc; } pool[mxm]; edge* et = pool;
edge* eds[mxn];
void addedge(int a, int b) { et->blc = 0; et->in = b; et->nxt = eds[a]; eds[a] = et++; }
#define foredges(i,x) for(edge*i=eds[x]; i; i= i->nxt)

int n, m;
int dfn[mxn], low[mxn], ft[mxn];
bool used[mxn];
int dfx, anst;
stack<pair<int, edge*>> ek; int eg = 0; // eg : 点双数量.

void Reset()
{
    et = pool;
    eg = dfx = anst = 0;
    memset(used, 0, sizeof(bool) * (n + 1));
    memset(eds, 0, sizeof(edge*) * (n + 1));
}

void DFS(int x, bool rt = true)
{
    low[x] = dfn[x] = ++dfx;
    used[x] = true;
    foredges(e, x) if(!used[e->in])
    {
        ek.push(make_pair(x, e)); // 树边.
        ft[e->in] = x;
        DFS(e->in, false);
        low[x] = min(low[x], low[e->in]);
        if(low[e->in] >= dfn[x])
        {
            if(low[e->in] > dfn[x])
            {
                // 确认 e 是一条割边.
                anst++;
            }
            
            if(!ek.empty()) // 找到一个点双.
            {
                eg++;
                while(!ek.empty())
                {
                    // 确认 ek.top().second 是在点双内的边.
                    ek.top().second->blc = eg;
                    int cur = ek.top().first; ek.pop();
                    if(cur == x) break;
                }
            }
        }
    }
    else if(e->in != ft[x])
    {
        if(dfn[e->in] < dfn[x]) ek.push(make_pair(x, e)); // 返祖边. 无向图没有横叉边.
        low[x] = min(low[x], dfn[e->in]);
    }
}

int main()
{
    while(true)
    {
        n = getint();
        m = getint();
        if(n == 0 && m == 0) break;
        Reset();
        
        rep(i, 0, m-1)
        {
            int a = getint();
            int b = getint();
            addedge(a, b);
            addedge(b, a);
        }
        
        rep(i, 0, n-1) if(!used[i]) DFS(i);
        
        int ansg = 0;
        map<int,set<int>> cntp;
        map<int,int> cnte;
        rep(x, 0, n-1) foredges(e, x) if(e->blc != 0)
        {
            if(cntp[e->blc].empty() || cntp[e->blc].find(x) == cntp[e->blc].end())
                cntp[e->blc].insert(x);
            if(cntp[e->blc].empty() || cntp[e->blc].find(e->in) == cntp[e->blc].end())
                cntp[e->blc].insert(e->in);
            cnte[e->blc]++;
        }
        rep(i, 1, eg) { if((int)cntp[i].size() < cnte[i]) ansg += cnte[i]; }
        
        printf("%d %d\n", anst, ansg);
    }
    return 0;
}
