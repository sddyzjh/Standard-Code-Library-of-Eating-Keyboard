typedef vector<int> vi;
const int K=200005,mod=998244353,G=3;
int n,k,a[K],h[K];
inline void swap(int &x,int &y){int t=x;x=y;y=t;}
inline void add(int &x,int y){
    y=(y%mod+mod)%mod;
    (x+=y)%=mod;
}
inline int pow(int x,int y){
    int ret=1;
    for(;y;x=1LL*x*x%mod,y>>=1)
        if(y&1) ret=1LL*ret*x%mod;
    return ret;
}
namespace NTT{/*{{{*/
    int n,invn,bit,rev[K*4],A[K*4],B[K*4],W[K*4][2];
    void build(){
        int bas=pow(G,mod-2);
        for(int i=0;i<=18;i++){
            W[1<<i][0]=pow(G,(mod-1)/(1<<i));
            W[1<<i][1]=pow(bas,(mod-1)/(1<<i));
        }
    }
    void init(int na,int nb,vi &a,vi &b,int fn=0){
        if(!fn) fn=na+nb;
        for(n=1,bit=0;n<fn;n<<=1,bit++);
        invn=pow(n,mod-2);
        for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
        for(int i=0;i<n;i++) A[i]=B[i]=0;
        for(int i=0;i<na;i++) A[i]=a[i];
        for(int i=0;i<nb;i++) B[i]=b[i];
    }
    void ntt(int *a,int f){
        for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
        int w_n,w,u,v;
        for(int i=2;i<=n;i<<=1){
            w_n=W[i][f==-1];
            for(int j=0;j<n;j+=i){
                w=1;    
                for(int k=0;k<i/2;k++){
                    u=a[j+k]; v=1LL*a[j+i/2+k]*w%mod;
                    a[j+k]=(u+v)%mod;
                    a[j+i/2+k]=(u+mod-v)%mod;
                    w=1LL*w*w_n%mod;
                }
            }
        }
        if(f==1) return;
        for(int i=0;i<n;i++) a[i]=1LL*a[i]*invn%mod;
    }
    void calc(){
        ntt(A,1);
        ntt(B,1);
        for(int i=0;i<n;i++) A[i]=1LL*A[i]*B[i]%mod;
        ntt(A,-1);
    }
    void calchh(){
        ntt(A,1);
        ntt(B,1);
        for(int i=0;i<n;i++) A[i]=(2LL*B[i]%mod+mod-1LL*A[i]*B[i]%mod*B[i]%mod)%mod;
        ntt(A,-1);
    }
}
vi mop,b,c,T;
vi operator - (vi A,vi B){
    int n=A.size(),m=B.size(),fn=max(n,m);
    A.resize(fn);
    for(int i=0;i<m;i++) add(A[i],-B[i]);
    return A;
}
vi operator * (int a,vi A){
    int n=A.size();
    a=(a+mod)%mod;
    for(int i=0;i<n;i++) A[i]=1LL*a*A[i]%mod;
    return A;
}
vi operator * (vi &A,vi B){
    int n=A.size(),m=B.size();
    NTT::init(n,m,A,B);
    NTT::calc();
    A.resize(n+m-1);
    for(int i=0;i<n+m-1;i++) A[i]=NTT::A[i];
    return A;
}
vi inverse(vi A){
    int n=A.size();
    if(n==1){
        A[0]=pow(A[0],mod-2);
        return A;
    }
    vi B=A;
    B.resize((n+1)/2);
    B=inverse(B);

    int m=B.size();
    NTT::init(n,m,A,B,n+m-1+m-1);
    NTT::calchh();
    B.resize(NTT::n);
    for(int i=0;i<NTT::n;i++) B[i]=NTT::A[i];

    //B=(2*B)-((A*B)*B);
    B.resize(n);
    return B;
}
vi operator / (vi A,vi B){
    int n=A.size()-1,m=B.size()-1;
    vi C;
    if(n<m){
        C.resize(1); C[0]=0;
        return C;
    }
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());
    B.resize(n-m+1);
    C=A*inverse(B);
    C.resize(n-m+1);    
    reverse(C.begin(),C.end());
    return C;
}
void module(vi &A,vi B){
    int n=A.size()-1,m=B.size()-1;
    if(n<m) return;
    vi D=A/B;
    A=A-(B*D);
    A.resize(m);
}
void ksm(int y){
    for(;y;y>>=1){
        if(y&1){
            c=c*b;
            module(c,mop);
        }
        b=b*b;
        module(b,mop);
    }
}
int main(){
    NTT::build();
    scanf("%d%d",&n,&k); n++;
    for(int i=1;i<=k;i++) scanf("%d",&h[i]),h[i]%=mod;
    for(int i=1;i<=k;i++) scanf("%d",&a[i]),a[i]%=mod;
    if(n<=k){printf("%d\n",h[n]);return 0;}
    mop.resize(k+1);
    mop[k]=1;
    for(int i=1;i<=k;i++) mop[k-i]=(mod-a[i])%mod;
    b.resize(2); b[1]=1; 
    c.resize(1); c[0]=1;
    ksm(n-1);
    int ans=0;
    c.resize(k);
    for(int i=0;i<k;i++)
        add(ans,1LL*c[i]*h[i+1]%mod);
    printf("%d\n",ans);
    return 0;
}