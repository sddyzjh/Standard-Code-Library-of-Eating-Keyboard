db eps = 1e-12; // 线性误差范围; long double : 1e-16;
db eps2 = 1e-6; // 平方级误差范围; long double: 1e-8;
bool eq(db a, db b) { return abs(a-b) < eps; }

// ============================ 点和向量 =============================
struct pt;
struct pt
{
    db x, y, z;
    pt operator+(pt const& b) const { return {x + b.x, y + b.y, z + b.z}; }
    pt operator-(pt const& b) const { return {x - b.x, y - b.y, z - b.z}; }
    pt operator()(pt const& b) const { return b - *this; } // 从本顶点出发,指向另一个点的向量.
    
    db len2() const { return x*x+y*y+z*z; } // 模的平方.
    db len() const { return sqrt(len2()); } // 向量的模.
    pt norm() const { db l = len(); return pt(x/l, y/l, z/l); } // 标准化.
    
    void out(const char* c) const { printf("(%.2f, %.2f, %.2f)%s", x, y, z, c); } // 输出.
};

// 数乘.
pt operator*(pt const& a, db const& b) { return pt(a.x * b, a.y * b, a.z * b); }
pt operator*(db const& b, pt const& a) { return pt(a.x * b, a.y * b, a.z * b); }

// 叉积.
pt operator*(pt const& a, pt const& b)
{ return pt(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }

// 点积.
db operator&(pt const& a, pt const& b)
{ return a.x * b.x + a.y * b.y + a.z * b.z; }

bool operator==(pt const& a, pt const& b)
{ return eq(a.x, b.x) && eq(a.y, b.y) && eq(a.z, b.z); }


// ============================== 线段 ===============================
struct segment
{
    pt from,to;
    segment() : from(), to() { }
    segment(pt const& a, pt const& b) : from(a), to(b) { }
    
    pt dir() const { return to - from; } // 方向向量,未标准化.
    db len() const { return dir().len(); } // 长度.
    db len2() const { return dir().len2(); }
    
    // 点在线段上.
    bool overlap(pt const& v) const
    { return eq(from(to).len(), v(from).len() + v(to).len()); }
    
    pt projection(pt const& p) const // 点到直线上的投影.
    {
        db h2 = abs((dir() * from(p)).len2()) / len2();
        db r = sqrt(from(p).len2() - h2);
        if(eq(r, 0)) return from;
        if((from(to) & from(p)) < 0) return from + from(to).norm() * (-r);
        else return from + from(to).norm() * r;
    }
    
    pt nearest(pt const& p) const // 点到线段的最近点.
    {
        pt g = projection(p);
        if(overlap(g)) return g;
        if(g(from).len() < g(to).len()) return from;
        return to;
    }
    
    pt nearest(segment const& x) const // 线段x上的离本线段最近的点.
    {
        db l = 0.0, r = 1.0;
        while(r - l > eps)
        {
            db delta = r - l;
            db lmid = l + 0.4 * delta;
            db rmid = l + 0.6 * delta;
            pt lp = x.interpolate(lmid);
            pt rp = x.interpolate(rmid);
            pt lnear = nearest(lp);
            pt rnear = nearest(rp);
            if(lp(lnear).len2() > rp(rnear).len2()) l = lmid;
            else r = rmid;
        }
        return x.interpolate(l);
    }
    
    pt interpolate(db const& p) const { return from + p * dir(); }
};

bool operator/(segment const& a, segment const& b) // 平行 (零向量平行于任意向量).
{
    return eq((a.dir() * b.dir()).len(), 0);
}
