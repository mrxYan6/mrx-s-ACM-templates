
std::vector<Pd> ConvexHull(std::vector<Pd> points) {
	int n = points.size();
	std::sort(points.begin(), points.end());
	std::deque<Pd> dq;

	for (auto& point: points) {
		while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(point);
	}

	int k = int(dq.size());
	for (int i = n - 1; i >= 0; i--) {
		while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
		dq.push_back(points[i]);
	}

	std::vector<Pd> ans(dq.begin(), dq.end());
	return ans;
}



//旋转卡壳,求凸包直径
i64 rotateCalipers(std::vector<Pl>& hull) {
	i64 d = 0;
	int n = hull.size();
	n--;
	if (n == 2)return abs2(hull[0] - hull[1]);
	int j = 2;
	for (int i = 0; i < n; ++i) {
		while (cross(hull[i + 1] - hull[i], hull[j] - hull[i]) < cross(hull[i + 1] - hull[i], hull[j + 1] - hull[i]))j = j < n - 1 ? j + 1 : 0;
		d = std::max({d, abs2(hull[i] - hull[j]), abs2(hull[i + 1] - hull[j])});
	}
	return d;
}