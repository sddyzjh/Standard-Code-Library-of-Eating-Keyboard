
/// KD 树.
/// 最近邻点查询.
/// 维度越少剪枝优化效率越高. ４维时是1/10倍运行时间, 8维时是1/3倍运行时间.
/// 板子使用欧几里得距离.
/// 可以把距离修改成曼哈顿距离之类的, **剪枝一般不会出错**.

///////////////////////////////////////////////////////////////

const int mxnc = 105000; // 最大的所有树节点数总量.
const int dem = 4; // 维度数量.

const db INF = 1e20;

/// 空间中的点.
struct point
{
    db v[dem]; // 维度坐标.
               // 注意你有可能用到每个维度坐标是不同的*类型*的点.
               // 此时需要写两个点对于第k个维度坐标的比较函数.
    point() { }
    point(db* coord) { memcpy(v, coord, sizeof(v)); }
    point(point const& x) { memcpy(v, x.v, sizeof(v)); }
    
    point& operator=(point const& x)
    { memcpy(v, x.v, sizeof(v)); return *this; }
    
    db& operator[](int const& k) { return v[k]; }
    db const& operator[](int const& k) const { return v[k]; }
};

db dist(point const& x, point const& y)
{
    db a = 0.0;
    for(int i=0; i<dem; i++) a += (x[i] - y[i]) * (x[i] - y[i]);
    return sqrt(a);
}

/// 树中的节点.
struct node
{
    point loc;  // 节点坐标点.
    int d;      // 该节点的下层节点从哪个维度切割. 切割坐标值由该节点坐标值给出.
    node* s[2]; // 左右子节点.
    
    int sep(point const& x) const { return x[d] >= loc[d]; }
};
node pool[mxnc]; node* curn = pool;

// 这个数组用来分配唯独切割顺序. 可以改用别的维度选择方式.
int flc[] = {3, 0, 2, 1};
node* newnode(point const& p, int dep)
{
    curn->loc = p;
    curn->d = flc[dep % dem];
    curn->s[0] = curn->s[1] = NULL;
    return curn++;
}

/// KD树.
struct KDTree
{
    node* root;
    
    KDTree() { root = NULL; }
    
    node* insert(point const& x)
    {
        node* cf = NULL;
        node* cur = root;
        int dep = 0;
        while(cur != NULL)
        {
            dep++;
            cf = cur;
            cur = cur->s[cur->sep(x)];
        }
        if(cf == NULL) return root = newnode(x, dep);
        return cf->s[cf->sep(x)] = newnode(x, dep);
    }
    
    // 求最近点的距离, 以及最近点.
    pair<db, point*> nearest(point const& p, node* x)
    {
        if(x == NULL) return make_pair(INF, (point*)NULL);
        
        int k = x->sep(p);
        
        // 拿到点 p 从属子区域的结果.
        pair<db, point*> sol = nearest(p, x->s[k]);
        
        // 用当前区域存储的点更新答案.
        db cd = dist(x->loc, p);
        if(sol.first > cd)
        {
            sol.first = cd;
            sol.second = &(x->loc);
        }
        
        //  如果当前结果半径和另一个子区域相交, 询问子区域并更新答案.
        db divDist = abs(p[x->d] - x->loc[x->d]);
        if(sol.first >= divDist)
        {
            pair<db, point*> solx = nearest(p, x->s[!k]);
            if(sol.first > solx.first) sol = solx;
        }
        
        return sol;
    }
    
    db nearestDist(point const& p) { return nearest(p, root).first; }
};

/// 初始化节点列表, 会清除**所有树**的信息.
void Init()
{
    curn = pool;
}
