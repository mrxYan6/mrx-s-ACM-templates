using ll  = long long;
long long exgcd(long long a,long long b,long long &x,long long &y){
	if(b == 0){
		x = 1,y = 0;
		return a;
	}
	ll d = exgcd(b,a % b,x,y);
	ll t = x;
	x = y;
	y = t - a / b * x;
	return d;
}

std::array<i64, 3> exgcd(i64 a, i64 b) {
	if (!b) {
		return {a, 1, 0};
	}
	auto [g, x, y] = exgcd(b, a % b);
	return {g, y, x - a / b * y};
}