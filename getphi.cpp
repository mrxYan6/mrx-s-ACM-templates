long long phi(long long x){
	long long res = x, m;
	m = sqrt(x);
	for(long long i = 2;i <= m;++i){
		if(x % i == 0){
			x /= i;
			res -= res / i;
			while(x % i == 0)x /= i;
		}
	}
	if(x > 1)res -= res / x;
	return res; 
}