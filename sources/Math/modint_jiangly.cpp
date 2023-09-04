
using i64 = long long;

template<class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    MInt() : x{} {}
    MInt(i64 x) : x{norm(x % P)} {}

    int norm(int x) const {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    int val() const {
        return x;
    }
    explicit operator int() const {
        return x;
    }
    MInt operator-() const {
        MInt res;
        res.x = norm(P - x);
        return res;
    }
    MInt inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % P;
        return *this;
    }
    MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};

const int P = 998244353;
using Z = MInt<P>;
