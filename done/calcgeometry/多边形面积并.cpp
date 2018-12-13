#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
typedef long long ll;
const double inf=1e200;
const double eps=1e-12;
const double pi=4*atan(1.0);
int dcmp(double x){ return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
    double x,y;
    point(double a=0,double b=0):x(a),y(b){}
};
point operator +(point A,point B) { return point(A.x+B.x,A.y+B.y);}
point operator -(point A,point B) { return point(A.x-B.x,A.y-B.y);}
point operator *(point A,double p){ return point(A.x*p,A.y*p);}
point operator /(point A,double p){ return point(A.x/p,A.y/p);}
bool operator ==(const point& a,const point& b){
    return fabs(a.x-b.x)<eps&&fabs(a.y-b.y)<eps;
}
double dot(point A,point B){ return A.x*B.x+A.y*B.y;}
double det(point A,point B){ return A.x*B.y-A.y*B.x;}
double det(point O,point A,point B){ return det(A-O,B-O);}
double length(point A){ return sqrt(dot(A,A));}
double area(vector<point>p){
    double ans=0; int sz=p.size();
    for(int i=1;i<sz-1;i++) ans+=det(p[i]-p[0],p[i+1]-p[0]);
    return ans/2.0;
}
double seg(point O,point A,point B){
    if(dcmp(B.x-A.x)==0) return (O.y-A.y)/(B.y-A.y);
    return (O.x-A.x)/(B.x-A.x);
}
vector<point>pp[110];
pair<double,int>s[110*60];
double polyunion(vector<point>*p,int N){
    double res=0;
    for(int i=0;i<N;i++){
        int sz=p[i].size();
        for(int j=0;j<sz;j++){
            int m=0;
            s[m++]=mp(0,0);
            s[m++]=mp(1,0);
            point a=p[i][j],b=p[i][(j+1)%sz];
            for(int k=0;k<N;k++){
                if(i!=k){
                    int sz2=p[k].size();
                    for(int ii=0;ii<sz2;ii++){
                        point c=p[k][ii],d=p[k][(ii+1)%sz2];
                        int c1=dcmp(det(b-a,c-a));
                        int c2=dcmp(det(b-a,d-a));
                        if(c1==0&&c2==0){
                            if(dcmp(dot(b-a,d-c))){
                                s[m++]=mp(seg(c,a,b),1);
                                s[m++]=mp(seg(c,a,b),-1);
                            }
                        }
                        else{
                            double s1=det(d-c,a-c);
                            double s2=det(d-c,b-c);
                            if(c1>=0&&c2<0) s[m++]=mp(s1/(s1-s2),1);
                            else if(c1<0&&c2>=0) s[m++]=mp(s1/(s1-s2),-1);
                        }
                    }
                }    
            }
            sort(s,s+m);
            double pre=min(max(s[0].first,0.0),1.0),now,sum=0;
            int cov=s[0].second;
            for(int j=1;j<m;j++){
                now=min(max(s[j].first,0.0),1.0);
                if(!cov) sum+=now-pre;
                cov+=s[j].second;
                pre=now;
            }
            res+=det(a,b)*sum;
        }
    }
    return res/2;
}
int main()
{
    int N,M,i,j; point tp;
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&M);
        for(j=0;j<M;j++){
            scanf("%lf%lf",&tp.x,&tp.y);
            pp[i].push_back(tp);
        }
    }
    double t1=0,t2=polyunion(pp,N);
    for(i=0;i<N;i++) t1+=area(pp[i]);
    printf("%.7lf %.7lf\n",-t1,-t2);
    return 0;
}
