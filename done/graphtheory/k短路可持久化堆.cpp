/*
	s到t的k短路
*/
typedef long long LL ;
typedef pair < int , int > pii ;
typedef pair < LL , int > pli ;
typedef unsigned long long ULL ;

#define clr( a , x ) memset ( a , x , sizeof a )
#define st first
#define ed second

const int MAXN = 10005 ;
const int BLOCK = 22 ;
const LL INF = 1e18 ;

namespace Leftist_Tree {
    struct Node {
        int l , r , x , h ;
        LL val ;
    } T[MAXN * 200] ;
    int Root[MAXN] ;
    int node_num ;
    int newnode ( const Node& o ) {
        T[node_num] = o ;
        return node_num ++ ;
    }
    void init () {
        node_num = 1 ;
        T[0].l = T[0].r = T[0].x = T[0].h = 0 ;
        T[0].val = INF ;
    }
    int merge ( int x , int y ) {
        if ( !x ) return y ;
        if ( T[x].val > T[y].val ) swap ( x , y ) ;
        int o = newnode ( T[x] ) ;
        T[o].r = merge ( T[o].r , y ) ;
        if ( T[T[o].l].h < T[T[o].r].h ) swap ( T[o].l , T[o].r ) ;
        T[o].h = T[T[o].r].h + 1 ;
        return o ;
    }
    void insert ( int& x , LL val , int v ) {
        int o = newnode ( T[0] ) ;
        T[o].val = val , T[o].x = v ;
        x = merge ( x , o ) ;
    }
    void show ( int o ) {
        printf ( "%d %lld %lld %lld\n" , o , T[o].val , T[T[o].l].val , T[T[o].r].val ) ;
        if ( T[o].l ) show ( T[o].l ) ;
        if ( T[o].r ) show ( T[o].r ) ;
    }
}

using namespace Leftist_Tree ;
vector < pii > G[MAXN] , E[MAXN] ;
int vis[MAXN] ;
int in[MAXN] , p[MAXN] ;
LL d[MAXN] ;
int s , t ;
int n , m , k ;

void addedge ( int u , int v , int c ) {
    G[u].push_back ( pii ( v , c ) ) ;
    E[v].push_back ( pii ( u , c ) ) ;
}

void dij () {
    priority_queue < pli > q ;
    d[t] = 0 ;
    q.push ( pli ( 0 , t ) ) ;
    while ( !q.empty () ) {
        int u = q.top ().ed ;
        q.pop () ;
        if ( vis[u] ) continue ;
        vis[u] = 1 ;
        for ( int i = 0 ; i < E[u].size () ; ++ i ) {
            int v = E[u][i].st ;
            if ( d[v] > d[u] + E[u][i].ed ) {
                p[v] = u ;
                d[v] = d[u] + E[u][i].ed ;
                q.push ( pli ( -d[v] , v ) ) ;
            }
        }
    }
}

void dfs ( int u ) {
    if ( vis[u] ) return ;
    vis[u] = 1 ;
    if ( p[u] ) Root[u] = Root[p[u]] ;
    int flag = 1 ;
    for ( int i = 0 ; i < G[u].size () ; ++ i ) {
        int v = G[u][i].st ;
        if ( d[v] == INF ) continue ;
        if ( p[u] == v && d[u] == G[u][i].ed + d[v] && flag ) {
            flag = 0 ;
            continue ;
        }
        LL val = d[v] - d[u] + G[u][i].ed ;
        insert ( Root[u] , val , v ) ;
    }
    for ( int i = 0 ; i < E[u].size () ; ++ i ) {
        if ( p[E[u][i].st] == u ) dfs ( E[u][i].st ) ;
    }
}

void solve () {
    for ( int i = 1 ; i <= n ; ++ i ) {
        G[i].clear () ;
        E[i].clear () ;
        d[i] = INF ;
        vis[i] = 0 ;
        p[i] = 0 ;
    }
    for ( int i = 0 ; i < m ; ++ i ) {
        int u , v , c ;
        scanf ( "%d%d%d" , &u , &v , &c ) ;
        addedge ( u , v , c ) ;
    }
    scanf ( "%d%d%d" , &s , &t , &k ) ;
    dij () ;
    if ( d[s] == INF ) {
        printf ( "-1\n" ) ;
        return ;
    }
    if ( s != t ) -- k ;
    if ( !k ) {
        printf ( "%lld\n" , d[s] ) ;
        return ;
    }
    for ( int i = 1 ; i <= n ; ++ i ) {
        vis[i] = 0 ;
    }
    init () ;
    Root[t] = 0 ;
    dfs ( t ) ;
    priority_queue < pli , vector < pli > , greater < pli > > q ;
    if ( Root[s] ) q.push ( pli ( d[s] + T[Root[s]].val , Root[s] ) ) ;
    while ( k -- ) {
        if ( q.empty () ) {
            printf ( "-1\n" ) ;
            return ;
        }
        pli u = q.top () ;
        q.pop () ;
        if ( !k ) {
            printf ( "%lld\n" , u.st ) ;
            return ;
        }
        int x = T[u.ed].l , y = T[u.ed].r , v = T[u.ed].x ;
        if ( Root[v] ) q.push ( pli ( u.st + T[Root[v]].val , Root[v] ) ) ;
        if ( x ) q.push ( pli ( u.st + T[x].val - T[u.ed].val , x ) ) ;
        if ( y ) q.push ( pli ( u.st + T[y].val - T[u.ed].val , y ) ) ;
    }
}

int main () {
    while ( ~scanf ( "%d%d" , &n , &m ) ) solve () ;
    return 0 ;
}
