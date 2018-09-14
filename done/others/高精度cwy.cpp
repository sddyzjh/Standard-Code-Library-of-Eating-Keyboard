#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <iostream>
#include <algorithm>

#include <map>
#include <stack>

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef double db;
typedef unsigned char uchar;

using namespace std;
inline bool isnum(char  c) { return '0' <= c && c <= '9'; }
inline int getint(int x=0) { scanf("%d", &x); return x; }
inline ll getll(ll x=0) { scanf("%lld", &x); return x; }
double getdb(double x=0) { scanf("%lf",&x); return x; }

//=============================================================

/// 大整数模板.
/// 这个模板保证把一个数字存成 v[0]*SYS^0 + v[1]*SYS^1 +... 的形式.
/// 支持负数运算.
struct bign
{
    static const int SYS = 10; // 多少进制数.
    static const int SIZE = 200; //  数位数.
    int v[SIZE]; // 数位, 从0到N从低到高. 注意可能会爆栈, 可以把它换成指针.
    int len;
    
    //====================================================
    //                       工具函数
    //====================================================
    
    // 进位和退位整理.
    void Advance(int const& i)
    {
        int k = v[i] / SYS;
        v[i] %= SYS;
        if(v[i] < 0) { k--; v[i] += SYS; }
        v[i+1] += k;
    }
    
    /// 进位和退位处理. 注意不会减少len.
    void Advance()
    { for(int i=0; i<len; i++) Advance(i); if(v[len] != 0) len++; }
    
    /// 去除前导0和前导-1.
    void Strip()
    {
        while(len > 0 && v[len-1] == 0) len--;
        while(len > 0 && v[len-1] == -1 && v[len-1] != 0) { len--; v[len] = 0; v[len-1] -= 10; }
    }
    
    bool isNegative() const { return len != 0 && v[len-1] < 0; }
    
    int& operator[](int const& k) { return v[k]; }
    
    //====================================================
    //                       构造函数
    //====================================================
    
    // 初始化为0.
    bign() { memset(this, 0, sizeof(bign)); }
    
    // 从整数初始化.
    bign(ll k)
    {
        memset(this, 0, sizeof(bign));
        while(k != 0) { v[len++] = k % SYS; k /= SYS; }
        Advance();
    }
    
    // 从字符串初始化. 仅十进制. 支持 -0, 0, 正数, 负数. 不支持前导0, 如 00012, -000, -0101.
    bign(const char* f)
    {
        memset(this,0,sizeof(bign));
        if(f[0] == '-')
        {
            f++;
            int l = strlen(f);
            for(int i=l-1; i>=0; i--) v[len++] = -(f[i] - '0');
            Advance();
            if(len == 1 && v[len-1] == 0) len = 0;
        }
        else
        {
            int l = strlen(f);
            for(int i=l-1; i>=0; i--) v[len++] = f[i] - '0';
            if(len == 1 && v[0] == 0) len--;
        }
    }
    
    // 拷贝构造函数.
    bign(bign const& f) { memcpy(this, &f, sizeof(bign)); }
    
    // 拷贝函数.
    bign operator=(bign const& f)
    { 
        memcpy(this, &f, sizeof(bign));
        return *this;
    }
    
    //====================================================
    //                       比较大小
    //====================================================
    
    bool operator==(bign const& f) const
    {
        if(len != f.len) return false;
        for(int i=0; i<len; i++) if(v[i] != f.v[i]) return false;
        return true;
    }
    
    bool operator<(bign const& f) const
    {
        if(isNegative() && !f.isNegative()) return true;
        if(!isNegative() && f.isNegative()) return false;
        if(isNegative() && f.isNegative())
        {
            if(len != f.len) return len > f.len;
            for(int i=len-1; i>=0; i--) if(v[i] != f.v[i]) return v[i] > f.v[i];
            return false;
        }
        
        if(len != f.len) return len < f.len;
        for(int i=len-1; i>=0; i--) if(v[i] != f.v[i]) return v[i] < f.v[i];
        return false;
    }
    
    bool operator>(bign const& f) const { return f < *this; }
    bool operator<=(bign const& f) const { return !(*this > f); }
    bool operator>=(bign const& f) const { return !(*this < f); }
    
    //====================================================
    //                        运算
    //====================================================
    
    bign operator-() const
    {
        bign c = *this;
        for(int i=c.len-1; i>=0; i--) { c[i] = - c[i]; }
        c.Advance();
        c.Strip();
        return c;
    }
    
    bign operator+(bign const& f) const
    {
        bign c;
        c.len = max(len, f.len);
        for(int i=0; i<c.len; i++) c[i] = v[i] + f.v[i];
        c.Advance();
        c.Strip();
        return c;
    }
    
    bign operator-(bign const& f) const { return *this + (-f); }
    
    bign operator*(int const& k) const
    {
        bign c;
        c.len = len;
        for(int i=0; i<len; i++) c.v[i] = v[i] * k;
        c.len += 10; // 这个乘数需要设置成比 log(SYS, max(k)) 大.
        c.Advance();
        c.Strip();
        return c;
    }
    
    bign operator*(bign const& f) const
    {
        if(isNegative() && f.isNegative()) return ((-*this) * (-f));
        if(isNegative()) return - ((-*this) * f);
        if(f.isNegative()) return - (*this * (-f));
        bign c;
        c.len = len + f.len;
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<f.len; j++) c[i+j] += v[i] * f.v[j];
            c.Advance();
        }
        c.Strip();
        return c;
    }
    
    int operator%(int const& k) const
    {
        int res = 0;
        for(int i=len-1; i>=0; i--) (res = res * SYS + v[i]) %= k;
        return res;
    }
    
    //====================================================
    //                       输入输出
    //====================================================
    
    bign Out(const char* c = "\n") const
    {
        if(len == 0 || (len == 1 && v[0] == 0)) { printf("0%s", c); return *this; }
        if(v[len-1] >= 0)
        {
            for(int i=len-1; i>=0; i--) printf("%d", v[i]);
            printf("%s", c);
        }
        else
        {
            printf("-");
            (-*this).Out(c);
        }
        return *this;
    }
    
    bign TestOut(const char* c = "\n", int const& sz = 0) const
    {
        printf("[(%d) ", len);
        if(sz == 0) for(int i=0; i<len; i++) printf("%d ", v[i]);
        else for(int i=01; i<sz; i++) printf("%d ", v[i]);
        printf("]\n");
        Out("");
        printf("%s", c);
        return *this;
    }
    
};

