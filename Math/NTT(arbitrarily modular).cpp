//
// Created by mrx on 2022/8/4.
//
#include <vector>
#include <cassert>
#include <iostream>


using i64 = long long;

template<typename T>
T inverse(T a, T b) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = b / a;
        b -= t * a;
        std::swap(a, b);
        u -= t * v;
        std::swap(u, v);
    }
    assert(b == 1);
    return u;
}

template<typename T>
T power(T a, int b) {
    T ans = 1;
    for (; b; a *= a, b >>= 1) {
        if (b & 1)ans *= a;
    }
    return ans;
}

template<typename T>
T power(T a, int b, int mod) {
    T ans = 1;
    for (; b; a = a * a % mod, b >>= 1) {
        if (b & 1)ans = ans * a % mod;
    }
    return ans;
}

template<int Mod>
class Modular {
public:
    using Type = int;

    template<typename U>
    static Type norm(U &x) {
        Type v;
        if (-Mod <= x && x < Mod) v = static_cast<Type>(x);
        else v = static_cast<Type>(x % Mod);
        if (v < 0) v += Mod;
        return v;
    }

    constexpr Modular() : value() {}

    i64 val() const { return value; }

    Modular inv() const {
        return Modular(inverse(value, Mod));
    }

    template<typename U>
    Modular(const U &x) {
        value = norm(x);
    }

    const Type &operator()() const {
        return value;
    }

    template<typename U>
    explicit operator U() const {
        return static_cast<U>(value);
    }

    Modular &operator+=(const Modular &other) {
        if ((value += other.value) >= Mod) value -= Mod;
        return *this;
    }

    Modular &operator-=(
            const Modular &other) {
        if ((value -= other.value) < 0) value += Mod;
        return *this;
    }

    template<typename U>
    Modular &operator+=(const U &other) { return *this += Modular(other); }

    template<typename U>
    Modular &operator-=(const U &other) { return *this -= Modular(other); }

    Modular &operator++() { return *this += 1; }

    Modular &operator--() { return *this -= 1; }

    Modular operator++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }

    Modular operator--(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }

    Modular operator-() const { return Modular(-value); }

    template<class ISTREAM_TYPE>
    friend ISTREAM_TYPE &operator>>(ISTREAM_TYPE &is, Modular &rhs) {
        i64 v;
        is >> v;
        rhs = Modular(v);
        return is;
    }

    template<class OSTREAM_TYPE>
    friend OSTREAM_TYPE &operator<<(OSTREAM_TYPE &os, const Modular &rhs) {
        return os << rhs.val();
    }

    Modular &operator*=(const Modular &rhs) {
        value = i64(value) * rhs.value % Mod;
        return *this;
    }

    Modular &operator/=(const Modular &other) { return *this *= Modular(inverse(other.value, Mod)); }

    friend const Type &abs(const Modular &x) { return x.value; }

    friend bool operator==(const Modular &lhs, const Modular &rhs) { return lhs.x == rhs.x; }

    friend bool operator<(const Modular &lhs, const Modular &rhs) { return lhs.x < rhs.x; }


    bool operator==(const Modular &rhs) { return *this == rhs.value; }

    template<typename U>
    bool operator==(U rhs) { return *this == Modular(rhs); }

    template<typename U>
    friend bool operator==(U lhs, const Modular &rhs) { return Modular(lhs) == rhs; }

    bool operator!=(const Modular &rhs) { return *this != rhs; }

    template<typename U>
    bool operator!=(U rhs) { return *this != rhs; }

    template<typename U>
    friend bool operator!=(U lhs, const Modular &rhs) { return lhs != rhs; }

    bool operator<(const Modular &rhs) { return this->value < rhs.value; }

    Modular operator+(const Modular &rhs) { return Modular(*this) += rhs; }

    template<typename U>
    Modular operator+(U rhs) { return Modular(*this) += rhs; }

    template<typename U>
    friend Modular operator+(U lhs, const Modular &rhs) { return Modular(lhs) += rhs; }

    Modular operator-(const Modular &rhs) { return Modular(*this) -= rhs; }

    template<typename U>
    Modular operator-(U rhs) { return Modular(*this) -= rhs; }

    template<typename U>
    friend Modular operator-(U lhs, const Modular &rhs) { return Modular(lhs) -= rhs; }

    Modular operator*(const Modular &rhs) { return Modular(*this) *= rhs; }

    template<typename U>
    Modular operator*(U rhs) { return Modular(*this) *= rhs; }

    template<typename U>
    friend Modular operator*(U lhs, const Modular &rhs) { return Modular(lhs) *= rhs; }

    Modular operator/(const Modular &rhs) { return Modular(*this) /= rhs; }

    template<typename U>
    Modular operator/(U rhs) { return Modular(*this) /= rhs; }

    template<typename U>
    friend Modular operator/(U lhs, const Modular &rhs) { return Modular(lhs) /= rhs; }

private:
    Type value;
};

const i64 mod1 = 998244353;
const i64 mod2 = 1004535809;
const i64 mod3 = 469762049;

struct Z {
    Modular<998244353> A;
    Modular<1004535809> B;
    Modular<469762049> C;

    Z() {}

    Z(int x) : A(x), B(x), C(x) {}

    Z operator*(const Z &rhs) {
        Z ans(*this);
        ans.A *= rhs.A;
        ans.B *= rhs.B;
        ans.C *= rhs.C;
        return ans;
    }

    Z operator+(const Z &rhs) {
        Z ans(*this);
        ans.A += rhs.A;
        ans.B += rhs.B;
        ans.C += rhs.C;
        return ans;
    }

    Z operator-(const Z &rhs) {
        Z ans(*this);
        ans.A -= rhs.A;
        ans.B -= rhs.B;
        ans.C -= rhs.C;
        return ans;
    }

    Z operator/(const Z &rhs) {
        Z ans(*this);
        ans.A /= rhs.A;
        ans.B /= rhs.B;
        ans.C /= rhs.C;
        return ans;
    }

    Z &operator/=(const Z &rhs) {
        A /= rhs.A;
        B /= rhs.B;
        C /= rhs.C;
        return *this;
    }

    Z &operator*=(const Z &rhs) {
        A *= rhs.A;
        B *= rhs.B;
        C *= rhs.C;
        return *this;
    }

    Z &operator+=(const Z &rhs) {
        A += rhs.A;
        B += rhs.B;
        C += rhs.C;
        return *this;
    }

    Z &operator-=(const Z &rhs) {
        A -= rhs.A;
        B -= rhs.B;
        C -= rhs.C;
        return *this;
    }

    Z inv() const {
        Z ans;
        ans.A = A.inv();
        ans.B = B.inv();
        ans.C = C.inv();
        return ans;
    }
};

Z gete(int k) {
    Z ans;
    ans.A = power(Modular<998244353>(3), (998244352) >> (k + 1));
    ans.B = power(Modular<1004535809>(3), (1004535808) >> (k + 1));
    ans.C = power(Modular<469762049>(3), (469762048) >> (k + 1));
    return ans;
}

long long getint(Z &z, long long P) {
    long long x = (z.B.val() - z.A.val() + mod2) % mod2 * power(mod1, mod2 - 2, mod2) % mod2 * mod1 + z.A.val();
    i64 ans =((z.C.val() - x % mod3 + mod3) % mod3 * power(mod1 * mod2 % mod3, mod3 - 2, mod3) % mod3 * (mod1 * mod2 % P) % P + x)% P;
    return ans;
}

std::vector<int> rev;
std::vector<Z> roots{0, 1};

void dft(std::vector<Z> &a) {
    int n = a.size();

    if (int(rev.size()) != n) {
        rev.resize(n);
        for (int i = 0; i < n; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (rev[i] < i)std::swap(a[i], a[rev[i]]);
    }
    if (int(roots.size() < n)) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
//            Z e = power(Z(3), (mod - 1) >> (k + 1));
            Z e = gete(k);
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = roots[i] * e;
            }
            k++;
        }
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}

void idft(std::vector<Z> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
}

struct Poly {
    std::vector<Z> a;

    Poly() {}

    Poly(const std::vector<Z> &a) : a(a) {}

    Poly(const std::initializer_list<Z> &a) : a(a) {}

    int size() const {
        return a.size();
    }

    void resize(int n) {
        a.resize(n);
    }

    Z operator[](int idx) const {
        if (idx < size()) {
            return a[idx];
        } else {
            return 0;
        }
    }

    Z &operator[](int idx) {
        return a[idx];
    }

    Poly mulxk(int k) const {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }

    Poly modxk(int k) const {
        k = std::min(k, size());
        return Poly(std::vector<Z>(a.begin(), a.begin() + k));
    }

    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(std::vector<Z>(a.begin() + k, a.end()));
    }

    friend Poly operator+(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }

    friend Poly operator-(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }

    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) {
            sz *= 2;
        }
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        Z inv = Z(sz).inv();
        for (int i = 0; i < sz; ++i) {
            a.a[i] = a[i] * b[i] * inv;
        }
        idft(a.a);
        a.resize(tot);
        return a;
    }

    friend Poly operator*(Z a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }

    friend Poly operator*(Poly a, Z b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }

    Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }

    Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }

    Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }


};

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nui64ptr);
    std::cout.tie(nui64ptr);
#endif
    int n, m, p;
    std::cin >> n >> m >> p;
    std::vector<Z> f(n + 1), g(m + 1);
    for (int i = 0; i <= n; ++i) {
        int x;
        std::cin >> x;
        f[i] = Z(x);
    }
    for (int i = 0; i <= m; ++i) {
        int x;
        std::cin >> x;
        g[i] = Z(x);
    }
    Poly F(f), G(g);
    Poly ans = F * G;
    for (int i = 0; i <= n + m; ++i) {
        std::cout << getint(ans[i], p) << ' ';
    }
    return 0;
}