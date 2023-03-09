#include <bits/stdc++.h>
const long long INF = 1e18;

template<typename T>
struct SegmentTree {
    struct Nod {
        T l, r;
        T val, tag;//tag和变量
        Nod *ls;
        Nod *rs;

        Nod(int l, int r) : l(l), r(r), val(INF), tag(INF), ls(nullptr), rs(nullptr) {}

        //根据需要改变
        inline void change(T v) {
            if (tag == INF)tag = v;
            else tag += v;
            val += (r - l + 1) * v;
        }

        //pushdown
        inline void push_down() {
            if (tag != INF) {
                ls->change(tag);
                rs->change(tag);
                tag = INF;
            }
        }

        //根据需要改变
        friend Nod merge(const Nod &lhs, const Nod &rhs) {
            Nod ans(0, 0);
            ans.val = lhs.val + rhs.val;
            return ans;
        }

        inline void push_up() {
            auto tmp = merge(*ls, *rs);
            val = tmp.val;
        }

        inline void clear() {
            if (ls != nullptr) {
                ls->clear();
            }
            if (rs != nullptr) {
                rs->clear();
            }
            delete this;
        }
    };

    Nod *root;

    SegmentTree(const std::vector<T> &base) {
        std::function<Nod *(int, int)> build = [&](int l, int r) -> Nod * {
            Nod *cur = new Nod(l, r);
            if (l == r) {
                cur->val = base[l];
            } else {
                int m = (l + r) >> 1;
                cur->ls = build(l, m);
                cur->rs = build(m + 1, r);
                cur->push_up();
            }
            return cur;
        };
        root = build(1, (int) base.size() - 1);
    }

    void modify(int l, int r, const T &val) {
        std::function<void(Nod *, int, int, const T &)> _modify = [&](Nod *rt, int L, int R, const T &_val) -> void {
            if (L <= rt->l && rt->r <= R) {
                rt->change(_val);
                return;
            }
            int m = (rt->l + rt->r) >> 1;
            rt->push_down();
            if (R <= m) {
                _modify(rt->ls, L, R, _val);
            } else if (L > m) {
                _modify(rt->rs, L, R, _val);
            } else {
                _modify(rt->ls, L, R, _val);
                _modify(rt->rs, L, R, _val);
            }
            rt->push_up();
        };
        _modify(root, l, r, val);
    }

    Nod qry(int l, int r) {
        std::function<Nod(Nod *, int, int)> query = [&](Nod *rt, int L, int R) {
            if (L <= rt->l && rt->r <= R) {
                return *rt;
            }
            int m = (rt->l + rt->r) >> 1;
            rt->push_down();
            Nod res(0, 0);
            if (R <= m) {
                res = query(rt->ls, L, R);
            } else if (L > m) {
                res = query(rt->rs, L, R);
            } else {
                res = merge(query(rt->ls, L, R), query(rt->rs, L, R));
            }
            rt->push_up();
            return res;
        };
        return query(root, l, r);
    }

    ~SegmentTree() {
        root->clear();
    }
};