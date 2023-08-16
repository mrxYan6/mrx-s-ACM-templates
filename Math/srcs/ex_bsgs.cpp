
i64 power(i64 base, i64 fact, i64 mod) {
    i64 ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base % mod;
        base = base * base % mod;
        fact >>= 1;
    }
    return ans;
}

std::array<i64, 3> exgcd(i64 a, i64 b) {
	if (!b) {
		return {a, 1, 0};
	}
	auto [g, x, y] = exgcd(b, a % b);
	return {g, y, x - a / b * y};
}

i64 bsgs(i64 a, i64 b, i64 p) {
    std::unordered_map<i64, i64> mp;
    i64 m = ceil(sqrt(p));
    b %= p;
    for (int i = 1; i <= m; i++) {
        b = a * b % p;
        mp[b] = i;
    }
    i64 tmp = power(a, m, p);
    b = 1;
    for (int i = 1; i <= m; i++) {
        b = b * tmp % p;
        if (mp[b])return (i * m - mp[b] + p) % p;
    }
    return -1;
}

i64 inv(i64 a, i64 b) {
    auto [g, x, y] = exgcd(a, b);
    return (x % b + b) % b;
}

//-1: no solution
i64 ex_bsgs(i64 a, i64 b, i64 p) {
    if (b == 1 || p == 1)return 0;
    i64 g = std::gcd(a, p), k = 0, na = 1;
    while (g > 1) {
        if (b % g != 0)return -1;
        k++, b /= g, p /= g, na = na * (a / g) % p;
        if (na == b)return k;
        g = std::gcd(a, p);
    }
    i64 f = bsgs(a, b * inv(na, p) % p, p);
    if (f == -1)return -1;
    return f + k;
}