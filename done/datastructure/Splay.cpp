/// Splay.
///　没有特殊功能的平衡树. 预留了一个自底向上更新的update函数.
/// pool: 点的池子. Splay数据结构本身只保存根节点指针.
/// 重新初始化: nt = pool + 1; 不要更改nil.

/// mxn: 节点池子大小.
const int mxn = 205000;

//////////////////////////////////////////////////////////////////////////

struct node* nil;
struct node
{
   int v;
   int cnt;
   node*s[2];
   node*f;
   void update()
   {
       cnt=1;
       if(s[0]!=nil) cnt+=s[0]->cnt;
       if(s[1]!=nil) cnt+=s[1]->cnt;
   }
}
pool[mxn]; node* nt=pool;

node*newnode(int v, node*f)
{
   nt->v=v;
   nt->cnt=1;
   nt->s[0]=nt->s[1]=nil;
   nt->f=f;
   return nt++;
}


struct SplayTree
{
    node*root;
    SplayTree():root(nil){}

    void rot(node*x)
    {
        node*y=x->f;
        int k=(x==y->s[0]);
        
        y->s[k^1]=x->s[k];
        if(x->s[k]!=nil) x->s[k]->f=y;
        
        x->f=y->f;
        if(y->f!=nil) y->f->s[y==y->f->s[1]]=x;
        
        y->f=x; x->s[k]=y;
        
        y->update();
    }

    node* splay(node*x,node*t=nil)
    {
        while(x->f!=t)
        {
            node*y=x->f;
            if(y->f!=t)
            if((x==y->s[0])^(y==y->f->s[0]))
                rot(x); else rot(y);
            rot(x);
        }
        x->update();
        if(t==nil) root=x;
        return x;
    }

    //=============================================

    void Insert(int v)
    {
        if(root==nil) { root=newnode(v, nil); return; }
        node *x=root, *y=root;
        while(x!=nil) { y=x; x=x->s[x->v <= v]; }
        splay(y->s[y->v<=v] = newnode(v, y));
    }


    node*Find(int v) // 查找值相等的节点. 找不到会返回nil.
    {
        node *x=root, *y=root;
        node *r=nil;
        while(x!=nil)
        {
            y=x;
            if(x->v==v) r=x;
            x=x->s[x->v < v];
        }
        splay(y);
        return r;
    }

    node* FindRank(int k) // 查找排名为k的节点.
    {
        node *x=root, *y=root;
        while(x!=nil)
        {
            y=x;
            if(k==x->s[0]->cnt+1) break;
            if(k<x->s[0]->cnt+1) x=x->s[0];
            else { k-=x->s[0]->cnt+1; x=x->s[1]; }
        }
        splay(y);
        return x;
    }

    // 排名从1开始.
    int GetRank(node*x) { return splay(x)->s[0]->cnt+1; }
    
    node*Delete(node*x)
    {
        int k=GetRank(x);
        node*L=FindRank(k-1);
        node*R=FindRank(k+1);
        
        if(L!=nil) splay(L);
        if(R!=nil) splay(R,L);
        
        if(L==nil && R==nil) root=nil;
        else if(R==nil) L->s[1]=nil;
        else R->s[0]=nil;
        
        if(R!=nil) R->update();
        if(L!=nil) L->update();
        
        return x;
    }
    
    node*Prefix(int v) // 前驱.
    {
        node *x=root, *y=root;
        node*r=nil;
        while(x!=nil)
        {
            y=x;
            if(x->v<v) r=x;
            x=x->s[x->v<v];
        }
        splay(y);
        return r;
    }

    node*Suffix(int v) // 后继.
    {
        node *x=root, *y=root;
        node*r=nil;
        while(x!=nil)
        {
            y=x;
            if(x->v>v) r=x;
            x=x->s[x->v<=v];
        }
        splay(y);
        return r;
    }

    //===========================================
    void output() { output(root); printf("%s\n",root==nil ? "empty tree!" : ""); }
    void output(node*x)
    {
        if(x==nil)return ;
        output(x->s[0]);
        printf("%d ",x->v);
        output(x->s[1]);
    }

    void test() { test(root); printf("%s\n",root==nil ? "empty tree!" : ""); }
    void test(node*x)
    {
        if(x==nil)return ;
        test(x->s[0]);
        printf("%p [ v:%d f:%p L:%p R:%p cnt:%d ] \n",x,x->v,x->f,x->s[0],x->s[1],x->cnt);
        test(x->s[1]);
    }

};


int n;

int main()
{
   nil=newnode(-1, nullptr);
   nil->cnt=0;
   nil->f=nil->s[0]=nil->s[1]=nil;
   
   n=getint();
   SplayTree st;
    
   for(int i=0;i<n;i++)
   {
       int c;
       c=getint();
       switch(c)
       {
           case 1: //Insert
               c=getint();
               st.Insert(c);
           break;
           case 2: //Delete
               c=getint();
               st.Delete(st.Find(c));
           break;
           case 3: //Rank
               c=getint();
               printf("%d\n",st.GetRank(st.Find(c)));
           break;
           case 4: //FindRank
               c=getint();
               printf("%d\n",st.FindRank(c)->v);
           break;
           case 5: //prefix
               c=getint();
               printf("%d\n",st.Prefix(c)->v);
           break;
           case 6: //suffix
                c=getint();
                printf("%d\n",st.Suffix(c)->v);
           break;
           case 7: //test
               st.test();
           break;
           default: break; 
       } 
   }

   return 0;
}
