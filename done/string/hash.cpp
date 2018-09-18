/// 字符串/数字串双模哈希.
/// 另外一些大质数, 可以用来做更多模数的哈希.
/// 992837513, 996637573, 996687641, 996687697, 996687721
///////////////////////////////////////////////////////////////////////////////
const int mxn = 1e6 + 50;
const int hashmod1 = 1000000007;
const int hashmod2 = 992837507;
const int sysnum1 = 31;
const int sysnum2 = 29;
ll hx[mxn];
ll hy[mxn];
struct Hash { int x; int y; };
bool operator<(Hash const& a, Hash const& b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
bool operator==(Hash const& a, Hash const& b) { return a.x == b.x && a.y == b.y; }
bool operator!=(Hash const& a, Hash const& b) { return !(a == b); }
/// 取子串的哈希值. 自觉改值域, 进制数和串类型.
Hash GetHash(int* c, int l, int r)
{
    Hash v = {0, 0};
    rep(i, l, r)
    {
        v.x = (((1LL * v.x * sysnum1) % hashmod1) + c[i] + 1) % hashmod1;
        v.y = (((1LL * v.y * sysnum2) % hashmod2) + c[i] + 1) % hashmod2;
    }
    return v;
}
/// 合并两个串的哈希值. 注意左右顺序.
Hash MergeHash(Hash left, Hash right, int rightLen)
{
    return Hash {
        (int)((1LL * left.x * hx[rightLen] % hashmod1  + right.x) % hashmod1),
        (int)((1LL * left.y * hy[rightLen] % hashmod2  + right.y) % hashmod2),
    };
}
/// 哈希计算初始化.
void HashInit(int sz)
{
    hx[0] = hy[0] = 1;
    rep(i, 1, sz)
    { 
        hx[i] = hx[i-1] * sysnum1 % hashmod1;
        hy[i] = hy[i-1] * sysnum2 % hashmod2;
    }
}
