using i64 = long long;

std::array<i64, 3> exgcd(i64 a, i64 b) {
	if (!b) {
		return {a, 1, 0};
	}
	auto [g, x, y] = exgcd(b, a % b);
	return {g, y, x - a / b * y};
}

auto EXCRT = [] (int n, const std::vector<int>& b, const std::vector<int>& m) {
	i64 xi, yi, gcd, c;
	i64 LCM = m[0], x0 = b[0];
	for (int i = 1; i < n; ++i) {
		auto [gcd, xi, yi] = exgcd(LCM, m[i]);
		c = b[i] - x0;
		if (c % gcd) return -1ll;
		i64 t = m[i] / gcd;
		xi = (xi * (c / gcd) % t + t) % t;
		x0 += xi * LCM;
		LCM *= m[i] / gcd;
		x0 %= LCM;
	}
	x0 = (x0 + LCM) % LCM;
	if(x0 == 0) x0 = LCM;
	return x0;
}; 