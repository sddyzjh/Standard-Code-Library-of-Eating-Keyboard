/// 线段树.
/// 带乘法和加法标记.
/// 只作为样例解释.
/// 线段树池子开到节点数的五倍.

/// mxn: 区间节点数. 线段树点数是它的四倍.
const int mxn = 105000;
/// n: 实际节点数.
/// a: 初始化列表.

/// 重新初始化:
build(); // 可以不使用初始化数组A.

//////////////////////////////////////////////////////////////////////////

ll a[mxn]; 
int n,m;
ll MOD;

#define L (x<<1)
#define R (x<<1|1)
ll t[mxn * 5]; // 当前真实值.
ll tagm[mxn * 5]; // 乘法标记. 
ll taga[mxn * 5]; // 加法标记. 在乘法之后应用. 
void pushtag(int x,int l,int r)
{
    if(tagm[x]==1 && taga[x]==0) return;
    ll &m = tagm[x]; ll &a = taga[x];
    // 向下合并标记.
    (tagm[L] *= m) %= MOD;
    (tagm[R] *= m) %= MOD;
    taga[L] = (taga[L] * m % MOD + a) % MOD;
    taga[R] = (taga[R] * m % MOD + a) % MOD;
    // 修改子节点真实值.
    int mid = (l+r)>>1;
    t[L] = (t[L] * m % MOD + (mid-l+1) * a) % MOD;
    t[R] = (t[R] * m % MOD + (r-mid) * a) % MOD;
    // 清理当前标记.
    tagm[x] = 1;
    taga[x] = 0;
}

/// 从子节点更新当前节点真实值.
/// 以下程序可以保证在Update之前该节点已经没有标记.
void update(int x) { t[x] = (t[L] + t[R]) % MOD; }

void build(int x=1,int l=0,int r=n) // 初始化.
{
    taga[x] = 0; tagm[x] = 1;
    if(l==r) { t[x] = a[l] % MOD; return; }
    int mid=(l+r)>>1;
    build(L,l,mid); build(R,mid+1,r);
    update(x);
}

int cl,cr; ll cv; int ct;
void Change(int x=1,int l=0,int r=n)
{
    if(cr<l || r<cl) return;
    if(cl<=l && r<=cr) // 是最终访问节点, 修改真实值并打上标记.
    {
        if(ct == 1)
        {
            (tagm[x] *= cv) %= MOD;
            (taga[x] *= cv) %= MOD;
            (t[x] *= cv) %= MOD;
        }
        else if(ct == 2)
        {
            (taga[x] += cv) %= MOD;
            (t[x] += (r-l+1) * cv) %= MOD;
        }
        return;
    }
    pushtag(x,l,r); // 注意不要更改推标记操作的位置.
    int mid = (l+r)>>1;
    Change(L,l,mid); Change(R,mid+1,r); update(x);
}

void Modify(int l,int r,ll v,int type)
{ cl=l; cr=r; cv=v; ct=type; Change(); }

int ql,qr;
ll Query(int x=1,int l=0,int r=n)
{
    if(qr<l || r<ql) return 0;
    if(ql<=l && r<=qr) return t[x];
    pushtag(x,l,r); // 注意不要更改推标记操作的位置.
    int mid=(l+r)>>1;
    return (Query(L,l,mid) + Query(R,mid+1,r)) % MOD;
}
ll Getsum(int l,int r)
{ ql=l; qr=r; return Query(); }

void Output(int x=1,int l=0,int r=n,int depth=0)
{
    printf("[%d] [%d,%d] t:%lld m:%lld a:%lld\n",x,l,r,t[x],taga[x],tagm[x]);
    if(l==r) return;
    int mid=(l+r)>>1; Output(L,l,mid); Output(R,mid+1,r);
}

int main()
{
    n=getint(); MOD=getint();
    for(int i=1;i<=n;i++) a[i]=getint();
    build();
    m=getint();
    for(int i=0;i<m;i++)
    {
        int type = getint();
        if(type==3)
        {
            int l = getint();
            int r = getint();
            printf("%lld\n",Getsum(l,r));
        }
        else
        {
            int l = getint();
            int r = getint();
            int v = getint();
            Modify(l,r,v,type);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////

/// 线段树 II.
/// 求区间中数字的平方和与和的平方.
/// 可以用来求区间中数字的两两之积, 它等于 二分之一倍和的平方减去平方之和. 0.5 * ((sigma{ai})^2 - sigma{ai^2})

struct Num
{
    static const int mod = 1e9+7;
    int v;
    Num() { }
    Num(int const& x) : v(x) { }
    Num operator+(Num const& a) const { return { (a.v + v) % mod }; }
    Num operator-(Num const& a) const { return { (v - a.v + mod) % mod }; }
    Num operator*(Num const& a) const { return { (int)((1LL * a.v * v) % mod) }; }
};

struct TD   /// 线段树数据池子.
{
    Num sum;    /// 区间和.
    Num sqs;    /// 区间每个数平方的和.
    Num add;    /// 区间加标记.
} t[mxn * 5];

inline void pushtag(int x, int l, int r)
{
    if(t[x].add.v == 0) return;
    int mid = (l + r) >> 1;
    
    Num v = t[x].add; t[x].add = 0;
    
    t[L].add = t[L].add + v;
    t[L].sqs = t[L].sqs + t[L].sum * v * 2 + v * v * (mid - l + 1);
    t[L].sum = t[L].sum + v * (mid - l + 1);
    
    t[R].add = t[R].add + v;
    t[R].sqs = t[R].sqs + t[R].sum * v * 2 + v * v * (r - mid);
    t[R].sum = t[R].sum + v * (r - mid);
}

inline void upd(int x,int l,int r)
{
    t[x].sum = t[L].sum + t[R].sum;
    t[x].sqs = t[L].sqs + t[R].sqs;
}
