struct Bitset {
    int n;
    std::vector<u64> a;

    Bitset(int n, int v = 0) :n(n), a((n + 63) / 64, u64(-v)) {}

    Bitset() {}

    int operator[](int x) const {
        if (x < 0 || x >= n) {
            return 0;
        }
        int id = x >> 6;
        return a[id] >> (x - (id << 6)) & 1;
    }
    void set(int x, int v) {
        if (x < 0 || x >= n) {
            return;
        }
        int id = x >> 6;
        if ((a[id] >> (x - (id << 6)) & 1) != v) {
            a[id] ^= 1ULL << (x - (id << 6));
        }
    }
    void norm() {
        if (n == 0) {
            return;
        }
        int shift = 63 - (n - 1) % 64;
        a.back() = a.back() << shift >> shift;
    }
    Bitset &operator&=(const Bitset& rhs) & {
        int m = std::min(a.size(), rhs.a.size());
        for (int i = 0; i < m; i++) {
            a[i] &= rhs.a[i];
        }
        norm();
        return *this;
    }
    Bitset &operator|=(const Bitset& rhs) & {
        int m = std::min(a.size(), rhs.a.size());
        for (int i = 0; i < m; i++) {
            a[i] |= rhs.a[i];
        }
        norm();
        return *this;
    }
    Bitset &operator^=(const Bitset& rhs) & {
        int m = std::min(a.size(), rhs.a.size());
        for (int i = 0; i < m; i++) {
            a[i] ^= rhs.a[i];
        }
        norm();
        return *this;
    }
    Bitset &operator<<=(int k) & {
        int m = a.size();
        for (int i = m - 1; i >= 0; i--) {
            int l = i * 64 - k;
            int r = l + 63;
            if (r < 0) {
                a[i] = 0;
            } else if (l % 64 == 0) {
                a[i] = a[l / 64];
            } else {
                int shift = r % 64;
                u64 v = 0;
                if (l > 0) {
                    v += a[l / 64] >> (shift + 1);
                }
                v += a[r / 64] << (63 - shift);
                a[i] = v;
            }
        }
        norm();
        return *this;
    }
    Bitset &operator>>=(int k) & {
        int m = a.size();
        for (int i = 0; i < m; i++) {
            int l = i * 64 + k;
            int r = l + 63;
            if (l >= m * 64) {
                a[i] = 0;
            } else if (l % 64 == 0) {
                a[i] = a[l / 64];
            } else {
                int shift = r % 64;
                u64 v = 0;
                v += a[l / 64] >> (shift + 1);
                if (r / 64 < m) {
                    v += a[r / 64] << (63 - shift);
                }
                a[i] = v;
            }
        }
        norm();
        return *this;
    }
    Bitset operator&(const Bitset& rhs) const{
        auto tmp = *this;
        return tmp &= rhs;
    }
    Bitset operator|(const Bitset& rhs) {
        auto tmp = *this;
        return tmp |= rhs;
    }
    Bitset operator^(const Bitset& rhs) {
        auto tmp = *this;
        return tmp ^= rhs;
    }
    Bitset operator<<(int k) {
        auto tmp = *this;
        return tmp <<= k;
    }
    Bitset operator>>(int k) {
        auto tmp = *this;
        return tmp >>= k;
    }
    int findFirst() const {
        int m = a.size();
        for (int i = 0; i < m; i++) {
            if (a[i] != 0) {
                for (int j = 0; j < 64; j++) {
                    if (a[i] >> j & 1) {
                        return i * 64 + j;
                    }
                }
            }
        }
        return n;
    }
    int findLast() const {
        int m = a.size();
        for (int i = m - 1; i >= 0; i--) {
            if (a[i] != 0) {
                for (int j = 63; j >= 0; j--) {
                    if (a[i] >> j & 1) {
                        return i * 64 + j;
                    }
                }
            }
        }
        return -1;
    }
    int count() const {
        int ans = 0;
        for (auto x : a) {
            ans += __builtin_popcountll(x);
        }
        return ans;
    }
    friend std::ostream &operator<<(std::ostream &os, const Bitset &g) {
        std::string s;
        for (int i = g.n - 1; i >= 0; i--) {
            s.push_back(g[i] + '0');
        }
        return os << s;
    }
};