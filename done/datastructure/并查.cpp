/// 并查集  


/// 简易的集合合并并查集,带路径压缩.
/// 重新初始化:
memset(f, 0, sizeof(int) * (n+1));
//////////////////////////////////////////////////////////////////////////
int f[mxn];
int fidnf(int x){ return f[x]==x ? x : f[x]=findf(f[x]); }
int connect(int a,int b){ f[findf(a)]=findf(b); }


/// 集合并查集,带路径压缩和按秩合并.
/// c[i]: 点i作为集合表头时, 该集合大小.
/// 重新初始化:
memset(f, 0, sizeof(int) * (n+1));
memset(c, 0, sizeof(int) * (n+1));
//////////////////////////////////////////////////////////////////////////
int f[mxn];
int c[mxn];
int connect(int a,int b)
{
    if(c[findf(a)]>c[findf(b)]) // 把b接到a中.
    { c[findf(a)]+=c[findf(b)]; f[findf(b)] = findf(a); } // 执行顺序不可对调.
    else // 把a接到b中.
    { c[findf(b)]+=c[findf(a)]; f[findf(a)] = findf(b); }
}


/// 集合并查集,带路径压缩,非递归.
/// 重新初始化:
memset(f, 0, sizeof(int) * (n+1));
//////////////////////////////////////////////////////////////////////////
int f[mxn];
int findf(int x) // 传入参数x不可为引用.
{
    stack<int> q;
    while(f[x]!=x) q.push(x), x=f[x];
    while(!q.empty()) f[q.top()]=x, q.pop();
}
void connect(int a,int b){ f[findf(a)]=findf(b); } // *可以换成按秩合并版本*.