#include <bits/stdc++.h>
using namespace std;
#define  LL long long
const LL N = 222;
const LL inf = 0x3f3f3f3f3f3f3f3f;
LL n;
LL val[N][N];
LL lx[N],ly[N];
LL linky[N];
LL pre[N];
bool vis[N];
bool visx[N],visy[N];
LL slack[N];
 
void bfs(LL k){
    LL px, py = 0,yy = 0, d;
    memset(pre, 0, sizeof(LL) * (n+2));
    memset(slack, inf, sizeof(LL) * (n+2));
    linky[py]=k;
    do{
        px = linky[py],d = inf, vis[py] = 1;
        for(LL i = 1; i <= n; i++)
            if(!vis[i]){
                if(slack[i] > lx[px] + ly[i] - val[px][i])
                    slack[i] = lx[px] + ly[i] -val[px][i], pre[i]=py;
                if(slack[i]<d) d=slack[i],yy=i;
            }
        for(LL i = 0; i <= n; i++)
            if(vis[i]) lx[linky[i]] -= d, ly[i] += d;
            else slack[i] -= d;
        py = yy;
    }while(linky[py]);
    while(py) linky[py] = linky[pre[py]] , py=pre[py];
}
LL KM(){
    memset(lx, 0, sizeof(LL)*(n+2));
    memset(ly, 0, sizeof(LL)*(n+2));
    memset(linky, 0, sizeof(LL)*(n+2));
    for(LL i = 1; i <= n; i++)
        memset(vis, 0, sizeof(bool)*(n+2)), bfs(i);
    LL ans = 0;
    for(LL i = 1; i <= n; ++i)
        ans += lx[i] + ly[i];
    return ans;
}
int main()
{
    LL T;
    scanf("%lld",&T);
    LL cas=0;
    while(T--){
        scanf("%lld",&n);
        for(LL i=1;i<=n;i++)
            for(LL j=1;j<=n;j++)
                scanf("%lld",&val[i][j]),val[i][j]=-val[i][j];
        printf("Case #%lld: %lld\n",++cas,-KM());
    }
    return 0;
}

