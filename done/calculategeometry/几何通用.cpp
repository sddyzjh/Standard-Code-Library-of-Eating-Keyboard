/// 计算几何专用. 按需选用.

db eps = 1e-12; // 线性误差范围; long double : 1e-16;
db eps2 = 1e-6; // 平方级误差范围; long double: 1e-8;
bool eq(db a, db b) { return abs(a-b) < eps; }

// ============================ 点和向量 =============================
struct point;
struct point
{
    db x, y;
    point():x(0),y(0) { }
    point(db a,db b):x(a),y(b) { }
    point(point const& f):x(f.x),y(f.y) { } 
    point operator=(point const& f) { x=f.x; y=f.y; return *this; }
    
    point operator+(point const& b) const { return point(x + b.x, y + b.y); }
    point operator-(point const& b) const { return point(x - b.x, y - b.y); }
    point operator()(point const& b) const { return b - *this; } // 从本顶点出发,指向另一个点的向量.
    
    db len2() const { return x*x+y*y; } // 模的平方.
    db len() const { return sqrt(len2()); } // 向量的模.
    point norm() const { db l = len(); return point(x/l, y/l); } // 标准化.
    
    // 把向量旋转f个弧度.
    point rot(double const& f) const
    { return point(x*cos(f) - y*sin(f), x*sin(f) + y*cos(f)); }
    
    // 极角, +x轴为0, 弧度制, (-π, π].
    db pangle() const { if(y >= 0) return acos(x / len()); else return - acos(x / len()); }

    void out() const { printf("(%.2f, %.2f)", x, y); } // 输出.
};

// 数乘.
point operator*(point const& a, db const& b) { return point(a.x * b, a.y * b); }
point operator*(db const& b, point const& a) { return point(a.x * b, a.y * b); }

// 叉积.
db operator*(point const& a, point const& b) { return a.x * b.y - a.y * b.x; }
// 点积.
db operator&(point const& a, point const& b) { return a.x * b.x + a.y * b.y; }

bool operator==(point const& a, point const& b) { return eq(a.x, b.x) && eq(a.y, b.y); }

// 判断本向量在另一个向量的顺时针方向. 注意选用eps或0.
bool operator>>(point const& a, point const& b) { return a*b > eps; }
// 判断本向量在另一个向量的顺时针方向或同向. 注意选用eps或0.
bool operator>>=(point const& a, point const& b) { return a*b > -eps; }

// ============================== 线段 ===============================
struct segment
{
    point from,to;
    segment(point const& a = point(), point const& b = point()) : from(a), to(b) { }
    
    point dir() const { return to - from; } // 方向向量,未标准化.
    
    db len() const { return dir().len(); } // 长度.
    
    // 点在线段上.
    bool overlap(point const& v) const
    { return eq(from(to).len(), v(from).len() + v(to).len()); }
    
    point projection(point const& p) const // 点到直线上的投影.
    {
        db h = abs(dir() * from(p)) / len();
        db r = sqrt(from(p).len2() - h*h);
        if(eq(r, 0)) return from;
        if((from(to) & from(p)) < 0) return from(to).norm() * (-r);
        else return from(to).norm() * r;
    }
    
    point nearest(point const& p) const // 点到线段的最近点.
    {
        point g = projection(p);
        if(overlap(g)) return g;
        if(g(from).len() < g(to).len()) return from;
        return to;
    }
};

bool operator/(segment const& a, segment const& b) // 平行 (零向量平行于任意向量).
{
    return eq(a.dir() * b.dir(), 0);
}

// 相交. 不计线段端点则删掉 eq(..., 0) 的所有判断.
bool operator*(segment const& A, segment const& B)
{
    point dia = A.from(A.to);
    point dib = B.from(B.to);
    db a = dia * A.from(B.from);
    db b = dia * A.from(B.to);
    db c = dib * B.from(A.from);
    db d = dib * B.from(A.to);
    return ((a < 0 && b > 0) || (a > 0 && b < 0) || A.overlap(B.from) || A.overlap(B.to)) &&
        ((c < 0 && d > 0) || (c > 0 && d < 0) || B.overlap(A.from) || B.overlap(A.to));
}