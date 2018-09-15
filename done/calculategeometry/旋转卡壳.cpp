
/// 旋转卡壳求最远点对距离.
/// stk[]: 按顺序存储的凸壳上的点的数组.
//////////////////////////////////////////////////////////////////////////
int GetmaxDistance()
{
    int res=0;
    int p=2;
    for(int i=1;i<st;i++)
    {
        while( p!=st && area(stk[i-1], stk[i], stk[p+1]) > area(stk[i-1], stk[i], stk[p]))
            p++;
        // 此时stk[i]的对踵点是stk[p].
        if(p==st) break;
        // 修改至想要的部分.
        res=max(res,stk[i-1](stk[p]).dist2());
        res=max(res,stk[i](stk[p]).dist2());
    }
    return res;
}
