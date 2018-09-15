inline ll mul(ll a,ll b){
	ll d=(ll)floor(a*(double)b/M+0.5);
	ll ret=a*b-d*M;
	if(ret<0)ret+=M;
	return ret;
}