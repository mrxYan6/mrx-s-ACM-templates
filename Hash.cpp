#include <random>

using i64 = long long;

struct Hash {
    static constexpr int P1 = 1000000829;
    static constexpr int P2 = 1000000579;
    i64 x, y;

    Hash(i64 x, i64 y) : x(x % P1), y(y % P2) {}

    Hash(i64 x = 0) : x(x % P1), y(x % P2) {}

    Hash& operator +=(const Hash& rhs) {
        x = (x + rhs.x) % P1, y = (y + rhs.y) % P2;
        return *this;
    }

    Hash& operator -=(const Hash& rhs) {
        x = (x - rhs.x + P1) % P1, y = (y - rhs.y + P2) % P2;
        return *this;
    }

    Hash& operator *=(const Hash& rhs) {
        x = x * rhs.x % P1, y = y * rhs.y % P2;
        return *this;
    }

    friend Hash operator +(const Hash& lhs, const Hash& rhs) {
        Hash res = lhs;
        return res += rhs;
    }

    friend Hash operator -(const Hash& lhs, const Hash& rhs) {
        Hash res = lhs;
        return res -= rhs;
    }

    friend Hash operator *(const Hash& lhs, const Hash& rhs) {
        Hash res = lhs;
        return res *= rhs;
    }

    friend bool operator ==(const Hash& lhs, const Hash& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator <(const Hash& lhs, const Hash& rhs) {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

std::random_device dv;
std::mt19937_64 rng(dv());

i64 base = rng() % 19260 + 817 + 114514;