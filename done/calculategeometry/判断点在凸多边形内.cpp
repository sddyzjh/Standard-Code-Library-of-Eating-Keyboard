/// 在线, 单次询问O(logn), st为凸包点数, 包括多边形上顶点和边界.
/// 要求凸包上没有相同点, 仅包含顶点.

bool agcmp(point const& a,point const& b) { return sp(a) * sp(b) < 0; }
bool PointInside(point target)
{
    sp = stk[0];
    point vt = sp(stk[1]);
    point vb = sp(stk[st-2]);
    db mt = vt * sp(target);
    db mb = vb * sp(target);
    bool able = (eq(mt, 0) && eq(mb, 0)) ||
        (eq(mt, 0) && mb > 0) || (eq(mb, 0) && mt < 0) ||
        (mt < 0 && mb > 0);
    if(able)
    {
        int xp = (int)(lower_bound(stk+1, stk+st-2, target, agcmp) - stk);
        able &= !(segment(sp, target) * segment(stk[xp], stk[xp-1]));
        able |= segment(stk[xp], stk[xp-1]).overlap(target);
    }
    return able;
}

/// 在线, 单次询问O(logn), st为凸包点数, **不**包括多边形上顶点和边界.

bool agcmp(point const& a,point const& b) { return sp(a) * sp(b) < 0; }
bool PointInside(point target)
{
    sp = stk[0];
    point vt = sp(stk[1]);
    point vb = sp(stk[st-2]);
    db mt = vt * sp(target);
    db mb = vb * sp(target);
    bool able = mt < 0 && mb > 0;
    if(able)
    {
        int xp = (int)(lower_bound(stk+1, stk+st-2, target, agcmp) - stk);
        able &= !(segment(sp, target) * segment(stk[xp], stk[xp-1]));
    }
    return able;
}
