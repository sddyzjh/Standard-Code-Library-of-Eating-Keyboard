db eps = 1e-12; // 线性误差范围; long double : 1e-16;
db eps2 = 1e-6; // 平方级误差范围; long double: 1e-8;
bool eq(db a, db b) { return abs(a-b) < eps; }

// ============================ 点和向量 =============================
struct point;
struct point
{
    db x, y, z;
    point():x(0),y(0),z(0) { }
    point(db a,db b,db c):x(a),y(b),z(c) { }
    point(point const& f):x(f.x),y(f.y),z(f.z) { } 
    point operator=(point const& f) { x=f.x; y=f.y; z=f.z; return *this; }
    
    point operator+(point const& b) const { return point(x + b.x, y + b.y, z + b.z); }
    point operator-(point const& b) const { return point(x - b.x, y - b.y, z - b.z); }
    point operator()(point const& b) const { return b - *this; } // 从本顶点出发,指向另一个点的向量.
    
    db len2() const { return x*x+y*y+z*z; } // 模的平方.
    db len() const { return sqrt(len2()); } // 向量的模.
    point norm() const { db l = len(); return point(x/l, y/l, z/l); } // 标准化.
    
    void out(const char* c) const { printf("(%.2f, %.2f, %.2f)%s", x, y, z, c); } // 输出.
};

// 数乘.
point operator*(point const& a, db const& b) { return point(a.x * b, a.y * b, a.z * b); }
point operator*(db const& b, point const& a) { return point(a.x * b, a.y * b, a.z * b); }

// 叉积.
point operator*(point const& a, point const& b)
{ return point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }

// 点积.
db operator&(point const& a, point const& b)
{ return a.x * b.x + a.y * b.y + a.z * b.z; }

bool operator==(point const& a, point const& b)
{ return eq(a.x, b.x) && eq(a.y, b.y) && eq(a.z, b.z); }


// ============================== 线段 ===============================
struct segment
{
    point from,to;
    segment() : from(), to() { }
    segment(point const& a, point const& b) : from(a), to(b) { }
    
    point dir() const { return to - from; } // 方向向量,未标准化.
    db len() const { return dir().len(); } // 长度.
    db len2() const { return dir().len2(); }
    
    // 点在线段上.
    bool overlap(point const& v) const
    { return eq(from(to).len(), v(from).len() + v(to).len()); }
    
    point projection(point const& p) const // 点到直线上的投影.
    {
        db h2 = abs((dir() * from(p)).len2()) / len2();
        db r = sqrt(from(p).len2() - h2);
        if(eq(r, 0)) return from;
        if((from(to) & from(p)) < 0) return from + from(to).norm() * (-r);
        else return from + from(to).norm() * r;
    }
    
    point nearest(point const& p) const // 点到线段的最近点.
    {
        point g = projection(p);
        if(overlap(g)) return g;
        if(g(from).len() < g(to).len()) return from;
        return to;
    }
    
    point nearest(segment const& x) const // 线段x上的离本线段最近的点.
    {
        db l = 0.0, r = 1.0;
        while(r - l > eps)
        {
            db delta = r - l;
            db lmid = l + 0.4 * delta;
            db rmid = l + 0.6 * delta;
            point lp = x.interpolate(lmid);
            point rp = x.interpolate(rmid);
            point lnear = nearest(lp);
            point rnear = nearest(rp);
            if(lp(lnear).len2() > rp(rnear).len2()) l = lmid;
            else r = rmid;
        }
        return x.interpolate(l);
    }
    
    point interpolate(db const& p) const { return from + p * dir(); }
};

bool operator/(segment const& a, segment const& b) // 平行 (零向量平行于任意向量).
{
    return eq((a.dir() * b.dir()).len(), 0);
}
