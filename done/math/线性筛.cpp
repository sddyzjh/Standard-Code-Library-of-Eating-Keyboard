/*
	is=0是质数
	phi欧拉函数 
	mu莫比乌斯函数 
	minp最小质因子 
	mina最小质因子次数 
	d约数个数 
*/
int prime[N];
int size;
bool is[N];
int phi[N];
int mu[N];
int minp[N];
int mina[N];
int d[N];
void getprime(int list){
	mu[1] = 1;
	phi[1] = 1;
	is[1] = 1;
	rep(i,2,list){
		if(!is[i]){
			// 新的质数
			prime[++size] = i;
			phi[i] = i-1;
			mu[i] = -1;
			minp[i] = i;
			mina[i] = 1;
			d[i] = 2;
		}
		rep(j,1,size){
			// 用已有的质数去筛合数
			if(i*prime[j]>list)
				break;
			// 标记合数
			is[i * prime[j]] = 1;
			minp[i*prime[j]] = prime[j];
			if(i % prime[j] == 0){
				// i是质数的倍数
				// 这个质数的次数大于1
				mu[i*prime[j]] = 0;
				// 次数++
				phi[i*prime[j]] = phi[i] * prime[j];
				// 次数++
				mina[i*prime[j]] = mina[i]+1;
				d[i*prime[j]] = d[i]/(mina[i]+1)*(mina[i]+2);
				break;
			}else{
				// 添加一个新的质因子
				phi[i*prime[j]] = phi[i] * (prime[j] - 1);
				mu[i*prime[j]] = -mu[i];
				mina[i*prime[j]] = 1;
				d[i*prime[j]] = d[i]*d[prime[j]];
			}
		}
	}
}