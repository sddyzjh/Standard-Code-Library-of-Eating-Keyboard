/// 无向图的最少欧拉路径覆盖
/// mxn : 点数.
/// mxm : 边数.
/// 最终结果存在 ls 中, 代表边的编号.
/// 初始化: 直接将图和结果链表清除即可.

// et = pool;
// memset(eds, 0, sizeof(edge*) * (n + 1));
// ls.clear();

/// AC HDU 6311

///////////////////////////////////////////////////////////////////////////////

typedef list<edge*>::iterator iter;

const int mxn = 1e5 + 50;
cosnt int mxm = 1e5 + 50;
struct edge { int id; int in; edge* nxt; bool used; } pool[mxm * 2]; edge* et = pool;
edge* opp(edge* t) { int x = (int)(t - pool); if(x & 1) return t - 1; return t + 1; }
edge* eds[mxn]; // 注意这一数组在运算时可能改变. 需要原图的话应做备份.
void addedge(int a, int b, int id)
{
    et->used = false; et->id = id; et->in = b; et->nxt = eds[a]; eds[a] = et++;
    et->used = false; et->id = -id; et->in = a; et->nxt = eds[b]; eds[b] = et++;
}
int n, m;
int deg[mxn]; //度数.
list<edge*> ls;
iter pos[mxn];
bool inq[mxn];
queue<int> q;
int stk[mxn]; int st = 0;
// 走一条路, 清除路上的边.
// 如果起点是奇数度, 最终会走到另一个度数为奇数的点.
// 如果起点是偶数度, 最终会走回起点.
void Reduce(int x, iter loc)
{
    stk[st++] = x;
    while(true)
    {
        while(eds[x] && eds[x]->used) eds[x] = eds[x]->nxt;
        if(!eds[x]) break;
        edge* e = eds[x];
        opp(e)->used = true;
        e->used = true;
        deg[x]--;
        deg[e->in]--;
        pos[x] = ls.insert(loc, e);
        x = stk[st++] = e->in;
    }
    repr(i, 0, st-1) if(deg[stk[i]] != 0 && !inq[stk[i]])
    {
        q.push(stk[i]);
        inq[stk[i]] = true;
    }
    st = 0;
}
// 使用欧拉路清除同一个连通分量内部的边.
void ReduceIteration()
{
    while(!q.empty())
    {
        int x = q.front(); q.pop(); inq[x] = false;
        if(deg[x] & 1)
        {
            Reduce(x, ls.end());
            ls.insert(ls.end(), nullptr);
        }
        else if(deg[x] != 0)  Reduce(x, pos[x]);
    }
}

......

{
    // 读入数据.
    rep(i, 1, m)
    {
        int a = getint();
        int b = getint();
        deg[a]++;
        deg[b]++;
        addedge(a, b, i);
    }
    
    // 初始化.
    rep(i, 1, n) pos[i] = ls.end();
    
    // 先清除所有奇数度节点所在联通块.
    rep(i, 1, n) if(deg[i] & 1) q.push(i);
    ReduceIteration();
    
    // 清除所有仅包含偶数度节点的联通块.
    rep(i, 1, n) if(deg[i] != 0)
    {
        q.push(i);
        inq[i] = true;
        ReduceIteration();
        ls.insert(ls.end(), nullptr);
    }
}