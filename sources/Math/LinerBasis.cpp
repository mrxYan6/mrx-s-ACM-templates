
template<typename T>
struct LinearBasis{
    std::vector<T> p, d;
    int cnt, n;

    LinearBasis(int n) : n(n) d(n + 1) {
        cnt = 0;
    }

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