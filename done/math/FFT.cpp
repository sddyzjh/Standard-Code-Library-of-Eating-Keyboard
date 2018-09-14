#define maxfft 524288+5
const double pi=acos(-1.0);
struct cp{
    double a,b;
    cp operator +(const cp &o)const {return (cp){a+o.a,b+o.b};}
    cp operator -(const cp &o)const {return (cp){a-o.a,b-o.b};}
    cp operator *(const cp &o)const {return (cp){a*o.a-b*o.b,b*o.a+a*o.b};}
    cp operator *(const double &o)const {return (cp){a*o,b*o};}
    cp operator !() const{return (cp){a,-b};}
}w[maxfft];
int pos[maxfft];
void fft_init(int len){
    int j=0;
    while((1<<j)<len)j++;
    j--;
    for(int i=0;i<len;i++)
        pos[i]=pos[i>>1]>>1|((i&1)<<j);
}
void fft(cp *x,int len,int sta){
    for(int i=0;i<len;i++)
        if(i<pos[i])swap(x[i],x[pos[i]]);
    w[0]=(cp){1,0};
    for(unsigned i=2;i<=len;i<<=1){
        cp g=(cp){cos(2*pi/i),sin(2*pi/i)*sta};
        for(int j=i>>1;j>=0;j-=2)w[j]=w[j>>1];
        for(int j=1;j<i>>1;j+=2)w[j]=w[j-1]*g;
        for(int j=0;j<len;j+=i){
            cp *a=x+j,*b=a+(i>>1);
            for(int l=0;l<i>>1;l++){
                cp o=b[l]*w[l];
                b[l]=a[l]-o;
                a[l]=a[l]+o;
            }
        }
    }
    if(sta==-1)for(int i=0;i<len;i++)x[i].a/=len,x[i].b/=len;
}
cp x[maxfft],y[maxfft],z[maxfft];
// a[0..n-1]和b[0..m-1]的卷积存在c中
void FFT(int *a,int n,int *b,int m,ll *c){
    int len=1;
    while(len<(n+m+1)>>1)len<<=1;
    fft_init(len);
    for(int i=n/2;i<len;i++)x[i].a=x[i].b=0;
    for(int i=m/2;i<len;i++)y[i].a=y[i].b=0;
    for(int i=0;i<n;i++)(i&1?x[i>>1].b:x[i>>1].a)=a[i];
    for(int i=0;i<m;i++)(i&1?y[i>>1].b:y[i>>1].a)=b[i];
    fft(x,len,1),fft(y,len,1);
    for(int i=0;i<len/2;i++){
        int j=len-1&len-i;
        z[i]=x[i]*y[i]-(x[i]-!x[j])*(y[i]-!y[j])*(w[i]+(cp){1,0})*0.25;
    }
    for(int i=len/2;i<len;i++){
        int j=len-1&len-i;
        z[i]=x[i]*y[i]-(x[i]-!x[j])*(y[i]-!y[j])*((cp){1,0}-w[i^len>>1])*0.25;
    }
    fft(z,len,-1);
    for(int i=0;i<n+m;i++)
        if(i&1)c[i]=(ll)(z[i>>1].b+0.5);
        else c[i]=(ll)(z[i>>1].a+0.5);
}

