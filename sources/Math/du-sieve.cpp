#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
#include <unordered_map>

using i64 = long long;

std::vector<int> primes, minp, phi, mu;
std::vector<i64> sum_phi, sum_mu;

void sieve (int n) {
    minp.resize(n);
    phi.resize(n);
    mu.resize(n);
    sum_phi.resize(n + 1);
    sum_mu.resize(n + 1);
    phi[1] = 1;
    mu[1] = 1;

    for (int i = 2; i < n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            phi[i] = i - 1;
            mu[i] = -1;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p * i > n) break;
            minp[i * p] = p;
            if (minp[i] == p) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        sum_phi[i] = sum_phi[i - 1] + phi[i];
        sum_mu[i] = sum_mu[i - 1] + mu[i];
    }
}

i64 f_g_sum(int n) {
    return (i64)n * (n + 1) / 2;
}

i64 g_sum(int n) {
    return n;
}

i64 GetSum(int n) {
    i64 ans = f_g_sum(n);
    for(i64 l = 2, r; l <= n; l = r + 1) {
        r = (n / (n / l)); 
        ans -= (g_sum(r) - g_sum(l - 1)) * GetSum(n / l);
    } 
    return ans; 
}

i64 GetPhi (unsigned int x) {
    //phi * 1 = id
    if (x < N) return sum_phi[x];
    if (Phi.count(x)) return Phi[x];

    i64 ans = 1ll * x * (x + 1) / 2;
    for (unsigned int l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= (r - l + 1) * GetPhi(x / l);
    }
    return Phi[x] = ans;
};

i64 GetMu (unsigned int x) {
    //mu * 1 = sigma
    if (x < N) return sum_mu[x];
    if (Mu.count(x)) return Mu[x];

    i64 ans = 1;
    for (unsigned int l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans -= (r - l + 1) * GetMu(x / l);
    }
    return Mu[x] = ans;
};
