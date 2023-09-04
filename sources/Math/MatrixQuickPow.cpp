#include <vector>
#include <iostream>
#include <algorithm>
const int mod = 1e9+7;
using ll = long long;
struct matrix {
    std::vector<std::vector<ll>> mat;
    ll n, m;

    matrix(ll a, ll b) {
        n = a, m = b;
        mat.clear();
        mat.resize(n);
        for (auto &x: mat)x.resize(m, 0);
    }

    void clear() {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j)mat[i][j] = 0;
        }
    }

    void E() {
        clear();
        for (ll i = 0; i < std::min(n, m); ++i) {
            mat[i][i] = 1;
        }
    }

    void show() {
        for (auto &x: mat) {
            for (auto y: x)std::cout << y << ' ';
            std::cout << std::endl;
        }
    }

    matrix operator*(const matrix &rhs) {
        matrix ans(n, rhs.m);
        if (m != rhs.n) {
            std::cerr << "Matrix not matching!";
        }
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                for (ll k = 0; k < rhs.m; ++k) {
                    ans.mat[i][k] = (ans.mat[i][k] + mat[i][j] * rhs.mat[j][k] % mod) % mod;
                }
            }
        }
        return ans;
    }

    friend matrix operator^(matrix bas, long long x) {
        matrix ans(bas.n, bas.n);
        ans.E();
        while (x) {
            if (x & 1) {
                ans = ans * bas;
            }
            bas = bas * bas;
            x >>= 1;
        }
        return ans;
    }

};

