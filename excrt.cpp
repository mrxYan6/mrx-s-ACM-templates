using ll = long long;
ll exgcd(ll aa,long long bb,ll &x,ll &y){
	if(bb == 0){
		x = 1,y = 0;
		return aa;
	}
	ll d = exgcd(bb,aa % bb,x,y);
	ll t = x;
	x = y;
	y = t - aa / bb * x;
	return d;
}

long long LCM;

long long EXCRT(int n){
	long long R, c, xi, yi, gcd, t;
	LCM = m[0];
	R = a[0];
	for(int i = 1;i < n;++i){
		gcd = exgcd(LCM, m[i], xi, yi);
		c = a[i] - X;
		if(c % gcd)return -1;
		t = m[i] / gcd;
		xi = c / gcd * xi % t;
		X += LCM * xi;
		LCM = LCM / gcd * m[i];
		X %= LCM;
	}
	X = (X + LCM) % LCM;
	if(X == 0)X = LCM;
	return X;
}