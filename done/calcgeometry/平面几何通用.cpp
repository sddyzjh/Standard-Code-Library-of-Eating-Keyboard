/// 计算几何专用. 按需选用.

db eps = 1e-12; // 线性误差范围; long double : 1e-16;
db eps2 = 1e-6; // 平方级误差范围; long double: 1e-8;
bool eq(db a, db b) { return abs(a-b) < eps; }

// ============================ 点和向量 =============================
struct pt
{
    db x, y;
    pt operator+(pt const& b) const { return {x + b.x, y + b.y}; }
    pt operator-(pt const& b) const { return {x - b.x, y - b.y}; }
    pt operator()(pt const& b) const { return b - *this; } // 从本顶点出发,指向另一个点的向量.
    
    db len2() const { return x*x+y*y; } // 模的平方.
    db len() const { return sqrt(len2()); } // 向量的模.
    pt norm() const { db l = len(); return pt(x/l, y/l); } // 标准化.
    
    // 把向量旋转f个弧度.
    pt rot(double const& f) const
    { return pt(x*cos(f) - y*sin(f), x*sin(f) + y*cos(f)); }
    
    // 极角, +x轴为0, 弧度制, (-π, π].
    db a() const { return atan2(y, x); }

    void out() const { printf("(%.2f, %.2f)", (double)x, (double)y); } // 输出.
};

// 数乘.
pt operator*(pt const& a, db const& b) { return {a.x * b, a.y * b}; }
pt operator*(db const& b, pt const& a) { return {a.x * b, a.y * b}; }

// 叉积.
db operator*(pt const& a, pt const& b) { return a.x * b.y - a.y * b.x; }
// 点积.
db operator&(pt const& a, pt const& b) { return a.x * b.x + a.y * b.y; }

bool operator==(pt const& a, pt const& b) { return eq(a.x, b.x) && eq(a.y, b.y); }

// ============================== 线段 ===============================
struct seg
{
    pt from,to;
    seg(pt const& a = pt(), pt const& b = pt()) : from(a), to(b) { }
    
    pt dir() const { return to - from; } // 方向向量,未标准化.
    
    db len() const { return dir().len(); } // 长度.
    
    // 点在线段上.
    bool overlap(pt const& v) const
    { return eq(from(to).len(), v(from).len() + v(to).len()); }
    
    pt projection(pt const& p) const // 点到直线上的投影.
    {
        db h = abs(dir() * from(p)) / len();
        db r = sqrt(from(p).len2() - h*h);
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
};

bool operator/(seg const& a, seg const& b) // 平行 (零向量平行于任意向量).
{
    return eq(a.dir() * b.dir(), 0);
}

// 相交. 不计线段端点则删掉 eq(..., 0) 的所有判断.
bool operator*(seg const& A, seg const& B)
{
    pt dia = A.from(A.to);
    pt dib = B.from(B.to);
    db a = dia * A.from(B.from);
    db b = dia * A.from(B.to);
    db c = dib * B.from(A.from);
    db d = dib * B.from(A.to);
    return ((a < 0 && b > 0) || (a > 0 && b < 0) || A.overlap(B.from) || A.overlap(B.to)) &&
        ((c < 0 && d > 0) || (c > 0 && d < 0) || B.overlap(A.from) || B.overlap(A.to));
}

// 直线相交. 假设其不平行.
pt Intersection(seg const& a, seg const& b)
{
    // if(eq(a.dir() * b.dir(), 0)) throw exception("No Intersection");
    db ax = (a.from(b.from) * b.dir()) / (a.dir() * b.dir());
    return a.from + ax * a.to;
}
