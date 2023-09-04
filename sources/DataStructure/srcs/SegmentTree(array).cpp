#include <bits/stdc++.h>

using i64 = long long;
const i64 INF = 1e18;

struct SegmentTree {
    struct Nod {
        int l, r;
        i64 sum, tag1, tag2;//tag1为加，tag2为改变

        Nod(int l = 0, int r = 0) : l(l), r(r), sum(0), tag1(0), tag2(INF) {}

        inline void apply(i64 v1, i64 v2) {
            if (v2 != INF) {
                tag2 = v2;
                sum = v2;
                tag1 = 0;
            }
            if (v1 != 0) {
                tag1 += v1;
                sum += v1;
            }
        }

    };

    //根据需要改变
    friend Nod merge(const Nod &lhs, const Nod &rhs) {
        Nod ans;
        ans.l = lhs.l, ans.r = rhs.r;
        ans.tag1 = 0, ans.tag2 = INF;
        ans.sum = std::max(lhs.sum, rhs.sum);
        return ans;
    }

    std::vector<Nod> tree;
    int n;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define T tree[rt]
#define LS tree[rt<<1]
#define RS tree[rt<<1|1]

    inline void push_up(int rt) {
        T = merge(LS, RS);
    }

    inline void push_down(int rt) {
        if (T.tag1 != 0 || T.tag2 != INF) {
            LS.apply(T.tag1, T.tag2);
            RS.apply(T.tag1, T.tag2);
            T.tag1 = 0, T.tag2 = INF;
        }
    }

    template<typename M>
    void build(int l, int r, int rt, const std::vector<M> &base) {
        T.l = l, T.r = r, T.tag1 = 0, T.tag2 = INF;
        if (l == r) {
            T.apply(0, base[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(lson, base);
        build(rson, base);
        push_up(rt);
    }

    template<typename... M>
    void _modify(int L, int R, int rt, const M &... v) {
        if (L <= T.l && T.r <= R) {
            if (T.l != T.r)push_down(rt);
            T.apply(v...);
            return;
        }
        int m = (T.l + T.r) >> 1;
        push_down(rt);
        if (L <= m)_modify(L, R, rt << 1, v...);
        if (R > m)_modify(L, R, rt << 1 | 1, v...);
        push_up(rt);
    }

    Nod qry(int L, int R, int rt) {
        if (L <= T.l && T.r <= R) {
            return T;
        }
        int m = (T.l + T.r) >> 1;
        Nod res;
        push_down(rt);
        if (R <= m)res = qry(L, R, rt << 1);
        else if (L > m)res = qry(L, R, rt << 1 | 1);
        else res = merge(qry(L, R, rt << 1), qry(L, R, rt << 1 | 1));
        push_up(rt);
        return res;
    }

#undef lson
#undef rson
#undef T
#undef LS
#undef RS

    template<class Type>
    SegmentTree(const std::vector<Type> &a) {
        n = a.size();
        n--;
        tree.resize((n << 2) + 1);
        build(1, n, 1, a);
    }

    template<typename... M>
    void modify(int L, int R, const M &...v) {
        assert(0 < L && L <= R && R <= n);
        _modify(L, R, 1, v...);
    }

    Nod query(int L, int R) {
        assert(0 < L && L <= R && R <= n);
        return qry(L, R, 1);
    }

    Nod query(int pos) {
        assert(pos > 0 && pos <= n);
        return qry(pos, pos, 1);
    }
};