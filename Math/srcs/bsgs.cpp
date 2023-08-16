using i64 = long long;

i64 power(i64 a, i64 b, i64 p) {
	i64 ans = 1;
	for (; b; a = a * a % p, b >>= 1)if (b & 1)ans = ans * a % p;
	return ans;
}

// p 为质数， version1 : 先处理 a ^ i,然后找 b * a ^ (- j * m) 的值
i64 bsgs(i64 a, i64 b, i64 p) {
	std::map<i64, i64> hash;
	i64 m = std::sqrt(p) + 0.5;
	i64 t = 1;
	for (int i = 0; i <= m; ++i) {
		if (!hash.count(t)) hash[t] = i;
		t = a * t % p;
	}
	i64 inv = power(power(a, m, p), p - 2, p), cur = b;
	for (int i = 0; i <= m; ++i) {
		if (hash.count(cur)) return i * m + hash[cur];
		cur = cur * inv % p;
	}
	return -1;
}
// p 不一定是质数， version2 : 先处理 b * a ^ i,然后找a ^ (j * m) 的值
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