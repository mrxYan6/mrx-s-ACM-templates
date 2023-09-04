
template<typename T>
struct SegmentTree {
    struct Nod {
        T sum;
        int lc, rc;

        Nod() : sum(0), lc(0), rc(0) {}

        friend void apply(Nod &lsh, T v, int l, int r) {
            lsh.sum += (r - l) * v;
        }
    };

    std::vector<Nod> pool;
    int lim_L, lim_R;

    int size() {
        return pool.size();
    }

    int newNode() {
        pool.emplace_back();
        return size() - 1;
    }

    SegmentTree(int max = 1e9 + 10, int n = 1e4) : pool(), lim_L(0), lim_R(max) {
        pool.reserve(n * 16);
        newNode();
    }

    void push_up(int x) {
        pool[x].sum = pool[pool[x].lc].sum + pool[pool[x].rc].sum;
    }

    int update_peer(int p, int x, int v, int l, int r) {
        int cur = newNode();
        pool[cur] = pool[p];
        if(l + 1 == r) {
            apply(pool[cur], v, l, r);
            return cur;
        }

        int mid = (l + r) >> 1;
        if (x < mid) {
            pool[cur].lc = update_peer(pool[cur].lc, x, v, l, mid);
        } else {
            pool[cur].rc = update_peer(pool[cur].rc, x, v, mid, r);
        }

        push_up(cur);
        return cur;
    }

    int update_peer(int p, int x, int v) {
        return update_peer(p, x, v, lim_L, lim_R);
    }

    std::array<int, 3> find_l_kth(int lp, int rp, int k, int l, int r) {
        if (pool[rp].sum - pool[lp].sum < k) return {-1, -1, pool[rp].sum - pool[lp].sum};
        if (l + 1 == r) {
            return {l, k, pool[rp].sum - pool[lp].sum};
        }
        
        int suml = pool[pool[rp].lc].sum - pool[pool[lp].lc].sum;
        int mid = (l + r) >> 1;
        if (suml >= k) {
            return find_l_kth(pool[lp].lc, pool[rp].lc, k, l, mid);
        } else {
            return find_l_kth(pool[lp].rc, pool[rp].rc, k - suml, mid, r);
        }
    }

    std::array<int, 3> find_l_kth(int lp, int rp, int k) {
        return find_l_kth(lp, rp, k, lim_L, lim_R);
    }
};