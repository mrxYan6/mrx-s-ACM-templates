{
	std::vector<Z> sum(n + 10), pre(n + 10), suf(n + 10);
	std::vector<Z> fact(n + 10),ifact(n + 10);

	fact[0] = 1;
	for (int i = 1; i < n + 10; ++i) {
		fact[i] = fact[i - 1] * i;
	}

	ifact[n + 9] = fact[n + 9].inv();
	for (int i = n + 9; i ; --i) {
		ifact[i - 1] = ifact[i] * i;
	}

	auto SumPow_ok = [&sum,&pre,&ifact,&suf](i64 x, int k) {
		
		std::vector<Z> pow;
		std::vector<int> minp, primes;
		auto sieve=[&](int n, int k) {
			pow.resize(n + 1);
			minp.resize(n + 1);
			for (int i = 2; i <= n; ++i) {
				if (!minp[i]) {
					minp[i] = i;
					pow[i] = power(Z(i), k);
				}
				for (auto p: primes) {
					if (p * i > n) break;
					minp[i * p] = p;
					pow[i * p] = pow[i] * pow[p];
					if (minp[i] == p) break;
				}
			}
		};

		for (int i = 1; i <= k + 2; ++i) {
			// sum[i] = sum[i - 1] + power(Z(i), k);//POWER 可以改为线性筛，这样就保证整个算法在O(n^2)内结束。
			sum[i] = sum[i - 1] + pow[i];
		}
		k += 2;
		if (x <= k) return sum[x];

		pre[0] = 1;
		for(int i = 1; i <= k; ++i){
			pre[i] = pre[i - 1] * (x - i);
		}
		suf[k + 1] = 1;
		for(int i = k; i; --i) {
			suf[i] = suf[i + 1] * (x - i);
		}
		Z ans = 0;
		for (int i = 1;i <= k; ++i) {
			Z U = pre[i - 1] * suf[i + 1];
			Z D = ifact[i - 1] * ifact[k - i];
			ans += sum[i] * (U * (k - i & 1 ? -D : D));
		}
		return ans;
	};


	auto SumPow = [&sum,&pre,&ifact,&suf](i64 x, int k) {
		
		std::vector<Z> pow;
		std::vector<int> minp, primes;
		auto sieve=[&](int n, int k) {
			pow.resize(n + 1);
			minp.resize(n + 1);
			for (int i = 2; i <= n; ++i) {
				if (!minp[i]) {
					minp[i] = i;
					pow[i] = power(Z(i), k);
				}
				for (auto p: primes) {
					if (p * i > n) break;
					minp[i * p] = p;
					pow[i * p] = pow[i] * pow[p];
					if (minp[i] == p) break;
				}
			}
		};

		for (int i = 1; i <= k + 2; ++i) {
			// sum[i] = sum[i - 1] + power(Z(i), k);//POWER 可以改为线性筛，这样就保证整个算法在O(n^2)内结束。
			sum[i] = sum[i - 1] + pow[i];
		}
		k += 2;
		if (x <= k) return sum[x];

		pre[0] = 1;
		for(int i = 1; i <= k; ++i){
			pre[i] = pre[i - 1] * (x - i);
		}
		suf[k + 1] = 1;
		for(int i = k; i; --i) {
			suf[i] = suf[i + 1] * (x - i);
		}
		Z ans = 0;
		for (int i = 1;i <= k; ++i) {
			Z U = pre[i - 1] * suf[i + 1];
			Z D = ifact[i - 1] * ifact[k - i];
			ans += sum[i] * (U * (k - i & 1 ? -D : D));
		}
		return ans;
	};
}