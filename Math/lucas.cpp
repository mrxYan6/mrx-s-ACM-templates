#include <iostream>
#include <vector>
#include <functional>


using i64 = long long;

i64 power(i64 a, i64 b, i64 p) {
	i64 ans = 1;
	for (; b; b >>= 1, a = a * a % p)if (b & 1)ans = ans * a % p;
	return ans;
}

i64 sol(int n, int m, int p) {
	std::vector<int> fact(p + 1), inv(p + 1);
	fact[0] = 1, inv[0] = 1;
	for (int i = 1; i < p; ++i) {
		fact[i] = 1ll * fact[i - 1] * i % p;
		inv[i] = power(fact[i], p - 2, p);
	}
	auto C = [&](int i, int j) {
		return i < j ? 0ll : 1ll * fact[i] * inv[j] % p * inv[i - j] % p;
	};
	std::function<i64(int, int, int)> lucas = [&](int i, int j, int p) -> i64 {
		return j == 0 ? 1ll : 1ll * C(i % p, j % p) * lucas(i / p, j / p, p) % p;
	};
	return lucas(n, m, p);
}
