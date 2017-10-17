/// 可持久化线段树.

/// 动态开点的权值线段树; 查询区间k大;
/// 线段树节点记录区间内打上了标记的节点有多少个; 只支持插入; 不带懒标记.
/// 如果要打tag和推tag, 参考普通线段树. 注意这样做以后基本就不能支持两棵树相减.

/// 池子大小.
const int pg = 4000000;

/// 树根数量.
const int mxn = 105000;

/// 权值的最大值. 默认线段树的插入范围是 [0, INF].
const int INF=(1<<30)-1;

/// 重新初始化:
nt = 0;
...
SegmentTreeInit(n);

//////////////////////////////////////////////////////////////////////////

struct node
{
    int t;
    node*l,*r;
    node(){ t=0; l=r=NULL;  }
    void update() { t=l->t+r->t; }
}pool[pg];

int nt;

node* newnode() { return &pool[nt++]; }

node* nil;
node* root[mxn];

void SegmentTreeInit(int size = 0)
{
    nil = newnode();
    nil->l = nil->r = nil;
    nil->t = 0;
    for(int i=0; i<=size; i++) root[i] = nil;
}

/// 在(子)树y的基础上新建(子)树x, 修改树中位置为cp的值.
int cp;
node*Change(node*x, node*y, int l = 0, int r = INF)
{
    if(cp<l || r<cp) return y;
    x=newnode();
    if(l==r) { x->t = 1 + y->t; return x; }
    int mid = (l+r)>>1;
    x->l = Change(x->l, y->l, l, mid);
    x->r = Change(x->r, y->r, mid+1, r);
    x->update();
    return x;
}

/// 查询树r减去树l的线段树中的第k大.
int Query(int ql,int qr,int k)
{
    node*x=root[ql],*y=root[qr];
    int l=0, r=INF;
    while(l != r)
    {
        int mid = (l+r)>>1;
        if(k <= x->l->t - y->l->t)
             r = mid, x = x->l,y = y->l;
        else
        {
            k -= x->l->t-y->l->t;
            l = mid+1, x = x->r, y = y->r;
        }
    }
    return l;
}

int n;

int main()
{
    
    int q;
    scanf("%d",&n);
    scanf("%d",&q);
    
    SegmentTreeInit(n);
    
    
    for(int i=0;i<n;i++)
    {
        int c;
        scanf("%d",&c);
        cp=c;
        root[i+1]=Change(root[i+1],root[i],0,INF);
    }
    
    
    for(int i=0;i<q;i++)
    {
        int a,b,k;
        scanf("%d%d%d",&a,&b,&k);
        printf("%d\n",Query(b,a-1,k));
    }
    
    return 0;
}