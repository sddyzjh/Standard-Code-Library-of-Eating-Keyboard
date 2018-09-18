/// 凸包
/// 支持动态插点, 查询点是否在多边形内.

/// AC CF 70D.

/// a: 输入点.
/// stk: 用来存凸包上的点的栈.
/// st: 栈顶下标, 指向最后一个元素的下一个位置.
/// stk[0]: 凸包上ｙ值最小的点中, x值最小的点.

//////////////////////////////////////////////////////////////////////////

/// 需要数乘.
pt operator*(db const& v, pt const& p) { return pt{v * p.x, v * p.y}; }

bool operator<(pt const& a, pt const& b)
{
    return eq(a.a(), b.a()) ? a.len2() < b.len2() : a.a() < b.a();
}

struct ConvexHull // 极角序凸包.
{
    typedef set<pt>::iterator iter;
    
    set<pt> hull;       // 逆时针排列的壳. 坐标相对于中央点.
    pt c = pt{0, 0};    // 中央点.
    
    bool degen = true;  // 是否是退化多边形. 不影响算法, 可以删掉.
    
    iter pre(iter x) { if(x == hull.begin()) x = hull.end(); x--; return x; }
    iter nxt(iter x) { x++; if(x == hull.end()) x = hull.begin(); return x; }
    iter LowerBound(pt const& v)
    {
        iter t = hull.lower_bound(v);
        return t == hull.end() ? hull.begin() : t;
    }
    
    // 返回元素是否被插入.
    bool Add(pt v)
    {
        if(hull.size() < 2) return hull.insert(v).second;
        if(hull.size() == 2)
        {
            auto x = hull.begin();
            pt a = *x, b = *(++x);
            
            if(eq(v(a) * v(b), 0))
            {
                if(eq(v(a).len() + v(b).len(), a(b).len()))
                    return false;
                
                if(eq(a(v).len() + a(b).len(), v(b).len()))
                    hull.erase(hull.begin());
                else if(eq(b(v).len() + b(a).len(), a(v).len()))
                    hull.erase(x);
                
                return hull.insert(v).second;
            }
            
            hull.clear();
            c = 1 / 3.0 * (a + b + v);
            hull.insert(a - c);
            hull.insert(b - c);
            hull.insert(v - c);
            degen = false;
            return true;
        }
        
        if(eq(v.x, c.x) && eq(v.y, c.y)) return false;
        
        v = c(v);
        iter r = LowerBound(v);
        iter l = pre(r);
        
        if((*l)(v) * (v)(*r) <= -eps) return false;
        
        while(hull.size() > 2 && (*pre(l))(*l) * (*l)(v) <= eps)
        {
            l = hull.erase(l);
            l = pre(l);
        }
        
        while(hull.size() > 2 && v(*r) * (*r)(*nxt(r)) <= eps)
        {
            r = hull.erase(r);
            if(r == hull.end()) r = hull.begin();
        }
        
        return hull.insert(v).second;
    }
    
    bool Contains(pt v)
    {
        if(hull.size() == 0) return false;
        if(hull.size() == 1) return eq(hull.begin()->x, v.x) && eq(hull.begin()->y, v.y);
        if(hull.size() == 2)
        {
            pt a = *hull.begin();
            pt b = *std::next(hull.begin());
            return eq(v(a).len() + v(b).len(), a(b).len());
        }
        
        v = c(v);
        iter a = LowerBound(v);
        pt r = *a;
        pt l = *pre(a);
        return l(v) * v(r) < eps;
    }
    
    void Out() const
    {
        for(auto i : hull) printf("%.4f %.4f\n", i.x + c.x, i.y + c.y);
        printf("\n");
    }
};
