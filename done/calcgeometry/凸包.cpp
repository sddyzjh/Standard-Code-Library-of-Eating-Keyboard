/// 凸包
/// 去除输入中重复顶点, 保留头尾重复, 顺时针顺序.

/// a: 输入点.
/// stk: 用来存凸包上的点的栈.
/// st: 栈顶下标, 指向最后一个元素的下一个位置.
/// stk[0]: 凸包上ｙ值最小的点中, x值最小的点.

//////////////////////////////////////////////////////////////////////////

int n;
point a[105000];
point stk[105000]; int st;

bool operator<(point const& a, point const& b) { return eq(a.y, b.y) ? a.x < b.x : a.y < b.y; }
// 使用 >= eps 则取凸包上的点.
// 使用 >= -eps 不取凸包上的点.
void Graham()
{
    sort(a,a+n);
    int g = (int)(unique(a, a+n) - a);
    st=0;
    
    rep(i, 0, g-1)
    {
        while(st>1 && stk[st-2](stk[st-1]) * stk[st-1](a[i]) >= eps) st--;
        stk[st++]=a[i];
    }
    int p=st;
    repr(i, 0, g-2)
    {
        while(st>p && stk[st-2](stk[st-1]) * stk[st-1](a[i]) >= eps) st--;
        stk[st++]=a[i];
    }
}

/// [.] AC HDU 1392
