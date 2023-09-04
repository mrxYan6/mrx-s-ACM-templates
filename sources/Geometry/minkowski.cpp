template <typename Point>
std::vector<Point> minkowski(std::vector<Point> hullA, std::vector<Point> hullB) {
    int n = hullA.size(), m = hullB.size();
    n--, m--;
    std::vector<Point> sega(n), segb(m);
    for (int i = 1; i <= n; ++i) sega[i - 1] = hullA[i] - hullA[i - 1];
    for (int i = 1; i <= m; ++i) segb[i - 1] = hullB[i] - hullB[i - 1];
    std::vector<Point> ans(n + m);
    ans[0] = hullA[0] + hullB[0];
    for (int i = 1, j = 0, k = 0; i < n + m; ++i) {
        ans[i] = ans[i - 1];
        if (j < n  && (k == m || sgn(cross(sega[j], segb[k])) >= 0)) ans[i] += sega[j++];
        else ans[i] += segb[k++];
    }
    return ConvexHull(ans);
}
