/// 线段树.
/// 带乘法和加法标记.
/// 只作为样例解释.

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
ll t[mxn<<2]; // 当前真实值.
ll tagm[mxn<<2]; // 乘法标记. 
ll taga[mxn<<2]; // 加法标记. 在乘法之后应用. 
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

void build(int x=1,int l=1,int r=n) // 初始化.
{
    taga[x] = 0; tagm[x] = 1;
    if(l==r) { t[x] = a[l] % MOD; return; }
    int mid=(l+r)>>1;
    build(L,l,mid); build(R,mid+1,r);
    update(x);
}

int cl,cr; ll cv; int ct;
void Change(int x=1,int l=1,int r=n)
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
ll Query(int x=1,int l=1,int r=n)
{
    if(qr<l || r<ql) return 0;
    if(ql<=l && r<=qr) return t[x];
    pushtag(x,l,r); // 注意不要更改推标记操作的位置.
    int mid=(l+r)>>1;
    return (Query(L,l,mid) + Query(R,mid+1,r)) % MOD;
}
ll Getsum(int l,int r)
{ ql=l; qr=r; return Query(); }

void Output(int x=1,int l=1,int r=n,int depth=0)
{
    printf("[%d] [%d,%d] t:%lld m:%lld a:%lld\n",x,l,r,t[x],taga[x],tagm[x]);
    if(l==r) return;
    int mid=(l+r)>>1;
    Output(L,l,mid); Output(R,mid+1,r);
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

