
template<typename T>
T qpow(T a,T b,T mod){
	T ans = 1;
	while(b){
		if(b & 1) ans = a * ans % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}