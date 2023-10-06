
template <typename T> struct Line {
    static bool Q;
    mutable T k, m, p;
    bool operator<(const Line &o) const { return Q ? p < o.p : k < o.k; }
};

template <> bool Line<i64>::Q = false;
template <typename T> struct Lines : std::multiset<Line<T>> {
    using ms = std::multiset<Line<T>>;
    static constexpr T inf = std::numeric_limits<T>::max();
    static T div(T a, T b) {
        if constexpr (std::is_integral_v<T>) {
            return a / b - ((a ^ b) < 0 and a % b);
        } else {
            return a / b;
        }
    }
    bool isect(auto x, auto y) {
        if (y == ms::end()) {
            return x->p = inf, false;
        }
        if (x->k == y->k) {
            x->p = x->m > y->m ? inf : -inf;
        } else {
            x->p = div(y->m - x->m, x->k - y->k);
        }
        return x->p >= y->p;
    }
    void add(T k, T m) {
        Line<T>::Q = false;
        auto z = ms::insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) {
            z = ms::erase(z);
        }
        if (x != ms::begin() and isect(--x, y)) {
            isect(x, y = ms::erase(y));
        }
        while ((y = x) != ms::begin() and (--x)->p >= y->p) {
            isect(x, ms::erase(y));
        }
    }
    T max(T x) {
        Line<T>::Q = true;
        auto l = ms::lower_bound({0, 0, x});
        return l->k * x + l->m;
    }
};