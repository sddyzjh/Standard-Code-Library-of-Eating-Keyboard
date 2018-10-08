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

// 点 T 到直线 AB 的投影点.
pt projection(pt const& A, pt const& B, pt const& T)
{ return A + (A(B).norm() & A(T)) * A(B).norm(); }

// 直线 A + lm * S 和 B + mu * T 的距离.
db dist(pt const& A, pt const& S, pt const& B, pt const& T)
{
    if((S * T).len() < eps) { return (A(B) * S).len() / S.len(); }
    return abs(A(B) & (S * T).norm());
}

// 直线 A + lm * S 和 B + mu * T 上的最近点对.
// first 在 A + lm * S 上, second 在 B + mu * T 上.
pair<pt,pt> closest(pt const& A, pt const& S, pt const& B, pt const& T)
{
    if((S * T).len() < eps) { return {A, projection(B, T, A)}; }
    pt X = (S * T).norm();
    pt Z = S.norm();
    pt Y = Z * X;
    pt b = { A(B) & X, A(B) & Y, A(B) & Z };
    pt t = { 0, T & Y, T & Z };
    db mu = - b.y / t.y;
    db lm = (b.z + mu * t.z) / S.len();
    return { A + lm * S, B + mu * T };
}

// 点 T 在直线 AB 上.
bool contains(pt const& A, pt const* B, pt const& T)
{ return (A(B).norm() * T).len() < eps; }

// 点 T 在线段 AB 上.
bool overlap(pt const& A, pt const& B, pt const& T)
{ return (A(B) & A(T)) > -eps && (B(A) & B(T)) > -eps && (A(B).norm() * T).len() < eps; }

// 点 T 到线段 AB 的最近点.
pt nearest(pt const& A, pt const& B, pt const& T)
{
    pt G = projection(T);
    if(overlap(A, B, G)) return G;
    if(G(A).len() < G(B).len()) return A;
    return B;
}
