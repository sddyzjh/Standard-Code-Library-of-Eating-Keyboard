int n,m,sz;  
int root[200005],ls[2000005],rs[2000005],v[2000005],deep[2000005];  
void build(int &k,int l,int r){
    if(!k)k=++sz;  
    if(l==r){v[k]=l;return;}  
    int mid=(l+r)>>1;  
    build(ls[k],l,mid);  
    build(rs[k],mid+1,r);  
}  
void modify(int l,int r,int x,int &y,int pos,int val){
    y=++sz;  
    if(l==r){v[y]=val;return;}  
    ls[y]=ls[x];rs[y]=rs[x];
    int mid=(l+r)>>1;
    if(pos<=mid)
        modify(l,mid,ls[x],ls[y],pos,val);  
    else modify(mid+1,r,rs[x],rs[y],pos,val);  
}  
int query(int k,int l,int r,int pos){  
    if(l==r)return k;  
    int mid=(l+r)>>1;  
    if(pos<=mid)return query(ls[k],l,mid,pos);  
    else return query(rs[k],mid+1,r,pos);  
}  
void add(int k,int l,int r,int pos){  
    if(l==r){deep[k]++;return;}  
    int mid=(l+r)>>1;  
    if(pos<=mid)add(ls[k],l,mid,pos);  
    else add(rs[k],mid+1,r,pos);  
}  
int find(int k,int x){  
    int p=query(k,1,n,x);  
    if(x==v[p])return p;  
    return find(k,v[p]);  
}  
int la=0;  
int main(){  
    n=read();m=read();  
    build(root[0],1,n);  
    int f,k,a,b;  
    for(int i=1;i<=m;i++){  
        f=read();  
        if(f==1){//合并
            root[i]=root[i-1];  
            a=read()^la;b=read()^la;  
            int p=find(root[i],a),q=find(root[i],b);  
            if(v[p]==v[q])continue;  
            if(deep[p]>deep[q])swap(p,q);  
            modify(1,n,root[i-1],root[i],v[p],v[q]);  
            if(deep[p]==deep[q])add(root[i],1,n,v[q]);  
        }  
        if(f==2)//返回第k次的状态
        {k=read()^la;root[i]=root[k];}  
        if(f==3){//询问
            root[i]=root[i-1];  
            a=read()^la;b=read()^la;  
            int p=find(root[i],a),q=find(root[i],b);  
            if(v[p]==v[q])puts("1"),la=1;  
            else puts("0"),la=0;  
        }  
    }  
    return 0;  
}