/// 类欧几里得
/// 类欧几里得用于计算 sum i = 0..n (a i + b) // c
/// 它的几何意义是计算区域 1 <= y <= a x + b, 0 <= x <= n 的整点个数.
/// 
/// Farey序列
/// 是一个用于枚举最简有理数 y/x 序列.
/// 序列由 1/0 和 0/1 构造,
/// 每次对相邻的两个数 ly/lx, ry/rx, 在其中插入一个数 (ly+ry)/(lx/rx) 构造新的序列.
/// 第 n 个序列满足 0 <= y <= n, 0 <= x <= n.
/// 
/// 可以使用类欧几里得统计的无限长Farey序列的前缀中 0 <= y <= n, 0 <= x <= m 的数字个数,
/// 进而可以在 0 <= y <= n, 0 <= x <= m 的序列上二分.
/// 
///////////////////////////////////////////////////////////////////////////////

// AC 牛客多校 2018 第十场 Rikka with Ants
// 注意对结果取模的方式.

const ll mod = 998244353;

struct Num
{
    ll val;
    Num() { }
    Num(ll const& v) : val(v >= mod ? v % mod : v) { }
};
Num operator+(Num const& a, Num const& b) { return { (a.val + b.val) % mod }; }
Num operator-(Num const& a, Num const& b) { return { ((a.val - b.val) % mod + mod) % mod }; }
Num operator*(Num const& a, Num const& b) { return { (a.val * b.val) % mod }; }

// 要求 a, b, n >= 0, c > 0.
Num euc(ll a, ll b, ll c, ll n)
{
    ll m =  n / c * a + (n % c * a + b) / c;
    return
        a == 0 ? Num(b / c) * (n + 1) :
        a >= c || b >= c ?
            euc(a % c, b % c, c, n)
            + Num(a / c) * (n * (n + 1) / 2)
            + Num(b / c) * (n + 1) :
        Num(n % mod) * m - euc(c, c - b - 1, a, m - 1);
}

int main()
{
    rep(T, 1, getint())
    {
        ll a = getint(); ll b = getint();
        ll c = getint(); ll d = getint();
        if(a * d == b * c) { printf("-1\n"); continue; }
        if(a * d > b * c) swap(a, c), swap(b, d);
        ll n = (a + b) * d / (b * c - a * d);
        Num ans = euc(a, a, b, n) - euc(c, 0, d, n) + n + 1;
        printf("%lld\n", ans.val);
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////////

// AC NAIPC 2018 Probe Droids (https://open.kattis.com/problems/probedroids)

struct pt { ll y, x; }; // y / x

ll euc(ll a, ll b, ll c, ll n)
{
    if(a == 0) return b / c * (n + 1);
    ll m = (a * n + b) / c;
    if(a >= c || b >= c) return euc(a % c, b % c, c, n) + a / c * (n * (n + 1) / 2) + b / c * (n + 1);
    return n * m - euc(c, c - b - 1, a, m - 1);
}

// 考虑上界: sum i=0..n, j=1..m [ j <= (ai+b)/c ]
ll euccut(ll a, ll b, ll c, ll n, ll m)
{
    ll lim = (m * c - b - 1) / a;
    return max(n - lim, 0LL) * m + euc(a, b, c, min(lim, n));
}

int main()
{
    ll m = getint(); ll n = getint(); int q = getint();
    rep(t, 1, q)
    {
        ll s = getll() + 1;
        if(s <= n) { printf("%lld %lld\n", 1LL, s); continue; }
        if(s > n * m - m + 1) { printf("%lld %lld\n", s - m * (n - 1), 1LL); continue; }
        pt l = pt { 0, 1 }, r = pt { 1, 0 };
        while(true) // Stern-Brocot Tree
        {
            pt mid = pt { l.y + r.y, l.x + r.x };
            ll cnt = euccut(mid.y, mid.x, mid.x, n-1, m);
            ll xcnt = min((n - 1) / mid.x, (m - 1) / mid.y);
            if(cnt - xcnt < s && s <= cnt) { l = r = mid; break; }
            if(s <= cnt) r = mid; else l = mid;
        }
        ll bcnt = euccut(l.y, l.x, l.x, n-1, m) - min((n-1) / l.x, (m-1) / l.y);
        printf("%lld %lld\n", l.y * (s - bcnt) + 1, l.x * (s - bcnt) + 1);
    }
    return 0;
}
