typedef long double db;
const db eps=1e-12;
struct pt
{
    db x,y;
    pt operator+(pt const& t) const { return pt{ x + t.x, y + t.y }; }
    pt operator-(pt const& t) const { return pt{ x - t.x, y - t.y }; }
    pt operator*(db const& t) const { return pt{ x * t, y * t }; }
    pt operator/(db const& t) const { return pt{ x / t, y / t }; }
    bool operator<(pt const& t) const { return eq(x, t.x) ? y < t.y : x < t.x; }
    bool operator==(pt const& t) const { return eq(x, t.x) && eq(y, t.y); }
    db len() const { return sqrt(x * x + y * y); }
    pt rot90() const { return {-y, x}; }
};

struct Circle
{
    pt o;
    db r;
    friend vector<pt> operator&(Circle const& c1,Circle const& c2)
    {
        db d=(c1.o-c2.o).len();
        if(d>c1.r+c2.r+eps || d<abs(c1.r-c2.r)-eps) return vector<pt>();
        db dt=(c1.r*c1.r-c2.r*c2.r)/d,d1=(d+dt)/2;
        pt dir=(c2.o-c1.o)/d,pcrs=c1.o+dir*d1;
        dt=sqrt(max(0.0L,c1.r*c1.r-d1*d1)),dir=dir.rot90();
        return vector<pt>{pcrs+dir*dt,pcrs-dir*dt};
    }
};
