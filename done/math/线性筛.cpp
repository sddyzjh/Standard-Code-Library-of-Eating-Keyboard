/*
	is是不是质数
	phi欧拉函数 
	mu莫比乌斯函数 
	minp最小质因子 
	mina最小质因子次数 
	d约数个数 
*/
int prime[N];
int size;
int is[N];
int phi[N];
int mu[N];
int minp[N];
int mina[N];
int d[N];
void getprime(int list){
	SET(is,1);
	mu[1] = 1;
	phi[1] = 1;
	is[1] = 0;
	rep(i,2,list){
		if(is[i]){
			prime[++size] = i;
			phi[i] = i-1;
			mu[i] = -1;
			minp[i] = i;
			mina[i] = 1;
			d[i] = 2;
		}
		rep(j,1,size){
			if(i*prime[j]>list)
				break;
			is[i * prime[j]] = 0;
			minp[i*prime[j]] = prime[j];
			if(i % prime[j] == 0){
				mu[i*prime[j]] = 0;
				phi[i*prime[j]] = phi[i] * prime[j];
				mina[i*prime[j]] = mina[i]+1;
				d[i*prime[j]] = d[i]/(mina[i]+1)*(mina[i]+2);
				break;
			}else{
				phi[i*prime[j]] = phi[i] * (prime[j] - 1);
				mu[i*prime[j]] = -mu[i];
				mina[i*prime[j]] = 1;
				d[i*prime[j]] = d[i]*d[prime[j]];
			}
		}
	}
}