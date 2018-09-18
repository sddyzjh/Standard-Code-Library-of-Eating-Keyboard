
/// 可持久化线段树.

/// 动态开点的权值线段树; 查询区间k大;
/// 线段树节点记录区间内打上了标记的节点有多少个; 只支持插入; 不带懒标记.
/// 如果要打tag和推tag, 参考普通线段树. 注意这样做以后基本就不能支持两棵树相减(因为查询时要推tag).

/// AC : vijos 1081 野生动物园

/// 池子大小. 通常需要直接开到 log(V).
/// 离散化可以缩小需要的点数.
const int pg = 3200000;

/// 树根数量.
const int mxn = 105000;

/// 权值的最大值. 默认线段树的插入范围是 [0, INF]. 离散化可以改成n.
const int INF=(1<<30)-1;

/// 重新初始化:
SegmentTreeInit(n);

//////////////////////////////////////////////////////////////////////////

struct node
{
    node *l, *r;
    int t;
    void upd() { t = l->t + r->t; }
}pool[pg];
node* nt;
node* newnode() { memset(nt, 0, sizeof(node)); return nt++; }

node* nil;
node* root[mxn];

void SegTreeInit(int sz = 0)
{
    nt = pool;
    nil = newnode();
    nil->l = nil->r = nil;
    nil->t = 0;
    root[0] = nil;
}

/// 在(子)树y的基础上新建(子)树x, 修改树中位置为cp的值.
int cp;
node*Change(node*y, int l = 0, int r = INF)
{
    if(cp<l || r<cp) return y;
    node* x = newnode();
    if(l==r) { x->t = 1 + y->t; return x; }
    int mid = (l+r)>>1;
    x->l = Change(y->l, l, mid);
    x->r = Change(y->r, mid+1, r);
    x->upd();
    return x;
}

/// 查询区间[l,r]中的第k大.
int Query(int ql, int qr, int k)
{
    node *x = root[qr], *y = root[ql-1];
    int l = 0, r = INF;
    while(l != r)
    {
        int mid = (l+r)>>1;
        if(k <= x->l->t - y->l->t)
             r = mid, x = x->l, y = y->l;
        else
        {
            k -= x->l->t-y->l->t;
            l = mid+1, x = x->r, y = y->r;
        }
    }
    return l;
}
