/// 最小覆盖圆.

/// n: 点数.
/// a: 输入点的数组.

//////////////////////////////////////////////////////////////////////////

const db eps = 1e-12;
const db eps2 = 1e-8;

/// 过三点的圆的圆心.
point CC(point const& a,point const& b,point const& c)  
{ 
    point ret;   
    db a1 = b.x-a.x, b1 = b.y-a.y, c1 = (a1*a1+b1*b1)*0.5;  
    db a2 = c.x-a.x, b2 = c.y-a.y, c2 = (a2*a2+b2*b2)*0.5;  
    db d = a1*b2 - a2*b1;
    if(abs(d)<eps) return (b+c)*0.5; 
    ret.x=a.x+(c1*b2-c2*b1)/d;  
    ret.y=a.y+(a1*c2-a2*c1)/d;  
    return ret;   
}

int n;
point a[1005000];

struct Resault{ db x,y,r; };
Resault MCC()
{
    if(n==0) return {0, 0, 0};
    if(n==1) return {a[0].x, a[0].y, 0};
    if(n==2) return {(a[0]+a[1]).x*0.5, (a[0]+a[1]).y*0.5, dist(a[0],a[1])*0.5}; 
    
    for(int i=0;i<n;i++) swap(a[i], a[rand()%n]); // 随机交换.
    
    point O; db R = 0.0;
    for(int i=2; i<n; i++) if(O(a[i]).len() >= R+eps2)
    {
        O=a[i];
        R=0.0;
        
        for(int j=0; j<i; j++) if(O(a[j]).len() >= R+eps2)
        {
            O=(a[i] + a[j]) * 0.5;
            R=a[i](a[j]).len() * 0.5;
            
            for(int k=0; k<j; k++) if(O(a[k]).len() >= R+eps2)
            {
                O = CC(a[i], a[j], a[k]);
                R = O(a[i]).len();
            }
        }
    }

    return {O.x, O.y, R};
}
