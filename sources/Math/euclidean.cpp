using Z = Modint;

std::array<Z, 3> euclidean(int a, int b, int c, int n) {
    Z ac = a / c, bc = b / c;
    int m = (1ll * a * n + b) / c;


    if (a == 0) {
        return {bc * (n + 1), bc * n * (n + 1) / 2, bc * bc * (n + 1)};
    }

    if (a >= c || b >= c) {

        auto [x, y, z] = euclidean(a % c, b % c, c, n);

        return {1ll * n * (n + 1) / 2 * ac + bc * (n + 1) + x, 
        ac * n * (n + 1) * (2 * n + 1) / 6 + bc * n * (n + 1) / 2 + y,
        ac * ac * n * (n + 1) * (n * 2 + 1) / 6 + bc * bc * (n + 1) + bc * ac * n * (n + 1) + z + 2 * bc * x + 2 * ac * y
        };
    }

    auto [x, y, z] = euclidean(c, c - b - 1, a, m - 1);
    auto f = Z(n) * m - x;
    auto g = (Z(m) * n * (n + 1) - x - z) / 2;
    auto h = Z(n) * m * (m + 1) - 2 * y - 2 * x - f;
    return {f, g, h};
}