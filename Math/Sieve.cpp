std::vector<int> minp, phi, primes;

void sieve(int n) {
    minp.resize(n + 1);
    phi.resize(n + 1);
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (auto p: primes) {
            if (p * i > n)break;
            minp[i * p] = p;
            if (p == minp[i]) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}