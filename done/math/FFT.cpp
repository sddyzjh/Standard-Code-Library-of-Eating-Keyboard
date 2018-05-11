const db PI = 3.14159265358979323846;
struct Complex{
	db x,y;
	Complex(db _x = 0.0, db _y = 0.0){
		x = _x, y = _y;
	}
	Complex operator -(const Complex &b)const{
		return Complex(x-b.x, y-b.y);
	}
	Complex operator +(const Complex &b)const{
		return Complex(x+b.x, y+b.y);
	}
	Complex operator *(const Complex &b)const{
		return Complex(x*b.x-y*b.y, x*b.y+y*b.x);
	}
};
void change(Complex y[], int len){
	int i, j, k;
	for(int i = 1,j = len>>1;i < len-1; ++i){
		if(i<j)swap(y[i],y[j]);
		k = len>>1;
		while(j >= k){
			j -= k;
			k >>= 1;
		}
		if(j < k)j += k;
	}
}
void fft(Complex y[], int len, int on){
	change(y, len);
	for(int h = 2;h <= len;h <<= 1){
		Complex wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
		for(int j = 0;j < len;j += h){
			Complex w(1,0);
			for(int k = j;k < j+h/2; ++k){
				Complex u = y[k];
				Complex t = w*y[k+h/2];
				y[k] = u+t;
				y[k+h/2] = u-t;
				w = w*wn;
			}
		}
	}
	if(on == -1)
		for(int i = 0;i < len; ++i)
			y[i].x /= len;
}
Complex x1[N], x2[N];
int x3[N];
void convolution(int a[], int l1, int b[], int l2){
	int len = 1;
	while(len < l1*2 || len < l2*2)len <<= 1;
	rep(i,0,l1-1)
		x1[i] = Complex(a[i], 0);
	rep(i,l1,len-1)
		x1[i] = Complex(0, 0);
	rep(i,0,l2-1)
		x2[i] = Complex(b[i], 0);
	rep(i,l2,len-1)
		x2[i] = Complex(0, 0);
	fft(x1,len,1);
	fft(x2,len,1);
	rep(i,0,len-1)
		x1[i] = x1[i]*x2[i];
	fft(x1,len,-1);
	rep(i,0,len-1)
		x3[i] = (int)(x1[i].x+0.5);
}
