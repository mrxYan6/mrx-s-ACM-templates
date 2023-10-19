
template<typename T, int N>
struct LinearBasis{
    std::array<T, N + 1> p, d;
    int cnt, n;

    LinearBasis() : p(), d(), cnt(0), n(N) {}

    bool ins(T x) {
        for(int i = n; i >= 0; --i) {
            if (x >> i) {
                if(!d[i]) {
                    d[i] = x;
                    return true;
                }
                x ^= d[i];
            }
        }
        return false;
    }

    void rebuild() {
        for (int i = n; i >= 0; --i) {
            for(int j = i - 1; j >= 0; --j) {
                if((d[i] >> j) & 1) {
                    d[i] ^= d[j];
                }
            }
        }
        for (int i = 0; i <= n; ++i) {
            if (d[i]) {
                p.push_back(d[i]);
            }
        }
    }

    T qry_max(){
        T ret = 0;
        for (int i = n;i >= 0;i--) {
            if ((ret ^ d[i]) > ret) {
                ret ^= d[i];
            }
        }
        return ret;
    }

    T qry_min(){
        for (int i = 0; i <= n; i++)
            if (d[i])
                return d[i];
        return 0;
    }


    T qry_kth(T k){
        T ret = 0;
        if (k >= (1ll << cnt)) return -1;
        for(int i = 0; i < p.size(); ++i){
            if((k >> i) & 1)ret ^= p[i];
        }
        return ret;
    }
};


//支持区间查询用法: perf[r].max(l)
template <typename T, int N>
struct LinearBasis{
    std::array<T, N + 1> base;
    std::array<T, N + 1> time;

    LinearBasis() :base(), time(){}

    void insert(int x, int t) {
        
        for (int i = N; i >= 0; --i) {
            if (x >> i & 1) {
                if (base[i] == 0) {
                    base[i] = x;
                    time[i] = t;
                    break;
                } else {
                    if (t > time[i]) {
                        std::swap(base[i], x);
                        std::swap(t, time[i]);
                    }
                    x ^= base[i];
                }
            }
        }
    }

    int max(int l) {
        int res = 0;
        for (int i = N; i >= 0; --i) {
            if (time[i] >= l) {
                res = std::max(res, res ^ base[i]);
            }
        }
        return res;
    }
};
