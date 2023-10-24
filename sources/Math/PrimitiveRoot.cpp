#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> primes, minp,phi;
void sieve(int n) {
    minp.resize(n), phi.resize(n);
    phi[1] = 1;
    for (int i = 2; i < n; ++i) {
        if (minp[i] == 0) {
            phi[i] = i - 1;
            minp[i] = i;
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (i * p >= n) break;
            minp[i * p] = p;
            if (minp[i] == p) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}

// 1, 2, 4, p^k, 2p^k
bool have(int p) {
    if (p == 1 || p == 2 || p == 4) return true;
    if (p % 2 == 0) p /= 2;
    for (auto P : primes)  {
        if (P == 2) continue;
        if (p < P) break;
        if (p % P == 0) {
            while (p % P == 0) p /= P;
            return p == 1;
        }
    }
    return false;
}

i64 power(i64 a, i64 b, i64 mod) {
    i64 res = 1;
    for (;b; b >>= 1, a = a * a % mod) {
        if (b & 1) res = res * a % mod;
    }
    return res;
}

int getg(int x) {
    auto divide = [&] (int n) {
        std::vector<int> res;
        for (auto p : primes) {
            if (1LL * p * p > n) break;
            if (n % p == 0) {
                res.push_back(p);
                while (n % p == 0) n /= p;
            }
        }
        if (n > 1) res.push_back(n);
        return res;
    };

    auto fac = divide(phi[x]);
    for (int i = 1; i < x; ++i) {
        bool ok = power(i, phi[x], x) == 1;
        for (auto p : fac) {
            // std::cout << i << " " << p << " " << power(i, (phi[x]) / p, x) << "\n";
            if (power(i, (phi[x]) / p, x) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return i;
    }

    return 0;
}

std::vector<int> getAllRoot(int n) {
    std::vector<int> ans;
    if (have(n)) {
        auto g = getg(n);
        int cur = g;
        for (int i = 1; i <= phi[n]; ++i) {
            if (std::gcd(i, phi[n]) == 1) {
                ans.push_back(cur);
            }
            cur = 1LL * cur * g % n;
        }
        std::sort(ans.begin(), ans.end());
    } 
    return ans;
}
