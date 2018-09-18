/// AC自动机.

/// mxn: 自动机的节点池子大小.
const int mxn = 105000;

/// ct: 字符集大小.
const int cst = 26;

/// 重新初始化:
node*pt = pool;

//////////////////////////////////////////////////////////////////////////

struct node
{
    node*s[cst];     // Trie 转移边.
    node*trans[cst]; // 自动机转移边.
    node*f;          // Fail 指针.
    char v;          // 当前节点代表字符(父节点指向自己的边代表的字符).
    bool leaf;       // 是否是某个字符串的终点. 注意该值为true不一定是叶子.
}
pool[mxn]; node*pt=pool;
node* newnode() { memset(pt, 0, sizeof(node)); return pt++; }

/// 递推队列.
node*qc[mxn];
node*qf[mxn];
int qh,qt;

struct Trie
{
    node*root;
    Trie(){ root = newnode(); root->v = '*' - 'a'; }
    
    /// g: 需要插入的字符串; len:长度.
    void Insert(char* g, int len)
    {
        node*x=root;
        for(int i=0;i<len;i++)
        {
            int v = g[i]-'a';
            if(!x->s[v])
            {
                x->s[v] = newnode();
                x->s[v]->v = v;
            }
            x = x->s[v];
        }
        x->leaf = true;
    }
    
    /// 在所有字符串插入之后执行.
    /// BFS递推, qc[i]表示队中节点指针, qf表示队中对应节点的fail指针.
    void Construct()
    {
        node*x = root;
        qh = qt = 0;
        for(int i=0; i<cst; i++) if(x->s[i])
        {
            x->s[i]->f = root;
            for(int j=0; j<cst; j++) if(x->s[i]->s[j])
            { qc[qt] = x->s[i]->s[j]; qf[qt]=root; qt++; }
        }
        
        while(qh != qt)
        {
            node*cur = qc[qh], *fp = qf[qh]; qh++;
            
            while(fp != root && !fp->s[cur->v]) fp = fp->f;
            if(fp->s[cur->v]) fp = fp->s[cur->v];
            cur->f = fp;
            
            for(int i=0; i<cst; i++)
                if(cur->s[i]) { qc[qt] = cur->s[i]; qf[qt] = fp; qt++; }
        }
    }
    
    // 拿到转移点.
    // 暴力判定.
    node* GetTrans(node*x, int v)
    {
        while(x != root && !x->s[v]) x = x->f;
        if(x->s[v]) x = x->s[v];
        return x;
    }
    
    // 拿到转移点.
    // 记忆化搜索.
    node* GetTrans(node*x, int v)
    {
        if(x->s[v]) return x->trans[v] = x->s[v];
        
        if(!x->trans[v])
        {
            if(x == root) return root;
            return x->trans[v] = GetTrans(x->f, v);
        }
        
        return x->trans[v];
    }
};
