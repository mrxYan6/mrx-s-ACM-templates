#include <bits/stdc++.h>

constexpr int P = 998244353;

constexpr int inv2 = (P + 1) / 2;

int norm (int x) {
    return x < 0 ? x + P : x >= P ? x - P : x;
}

std::vector<int> fwt(std::vector<int> a, int flag, int type) {
    int n = a.size();
    for (int k = 1; k * 2 <= n; k *= 2) {
        for (int i = 0; i < n; i += k * 2) {
            for (int j = 0; j < k; ++j) {
                int x = a[i + j], y = a[i + j + k];
                if (type == 1) {
                    // or
                    a[i + j + k] = norm(a[i + j + k] + x * flag);
                } else if (type == 2) {
                    // and
                    a[i + j] = norm(a[i + j] + y * flag);
                } else {
                    // or
                    if (flag == 1) {
                        a[i + j] = norm(x + y);
                        a[i + j + k] = norm(x - y);
                    } else {
                        a[i + j] = 1LL * norm(x + y) * inv2 % P;
                        a[i + j + k] = 1LL * norm(x - y) * inv2 % P;
                    }
                }
            }
        }
    }
    return a;
}