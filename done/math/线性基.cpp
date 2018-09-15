ll a[N],b[N];
// 插入一个数
void insert(ll *ff,ll x){
    repr(i,0,60)
        if((x>>i)&1ll)
            if(!ff[i]){
                ff[i] = x;
                return;
            }
            else
                x ^= ff[i];
}
// 查询一个数是否在异或集合内
bool check(ll x){
    repr(i,0,60){
        if((x>>i)&1){
            if(((b[i]>>i)&1)==0)return 0;
            x^=b[i];
            if(!x)return 1;
        }
    }
    return 0;
}
