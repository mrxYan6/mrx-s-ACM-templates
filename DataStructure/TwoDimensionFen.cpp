//
// Created by mrx on 2023/3/21.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;

struct fen_2 {
    std::vector<std::vector<i64>> fen;
    int n, m;
    
    fen_2(int n, int m) : n(n), m(m) {
        fen.resize(n + 1, std::vector<i64>(m + 1));
    }
    
    void add(int x, int y, i64 k) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                fen[i][j] += k;
            }
        }
    }
    
    i64 qry(int x, int y) {
        i64 res = 0;
        for (int i = x; i; i -= i & -i) {
            for (int j = y; j; j -= j & -j) {
                res += fen[i][j];
            }
        }
        return res;
    }
    
    i64 rangeQuery(int a, int b, int c, int d) {
        return qry(c, d) - qry(c, b - 1) - qry(a - 1, d) + qry(a - 1, b - 1);
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    fen_2 a1(n, m), a2(n, m), a3(n, m), a4(n, m);
    int opt;
    while (std::cin >> opt) {
        if (opt == 1) {
            int x1, y1, x2, y2;
            i64 k;
            std::cin >> x1 >> y1 >> x2 >> y2 >> k;
            auto rangeAdd = [&](int x, int y, i64 k) {
                a1.add(x, y, k);
                a2.add(x, y, k * (x - 1));
                a3.add(x, y, k * (y - 1));
                a4.add(x, y, k * (x - 1) * (y - 1));
            };
            rangeAdd(x1, y1, k);
            rangeAdd(x1, y2 + 1, -k);
            rangeAdd(x2 + 1, y1, -k);
            rangeAdd(x2 + 1, y2 + 1, k);
        } else {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            auto rangeQry = [&](int x, int y) {
                return a1.qry(x, y) * x * y - y * a2.qry(x, y) - x * a3.qry(x, y) + a4.qry(x, y);
            };
            std::cout << rangeQry(x2, y2) - rangeQry(x2, y1 - 1) - rangeQry(x1 - 1, y2) + rangeQry(x1 - 1, y1 - 1) << '\n';
        }
    }
    
    return 0;
}