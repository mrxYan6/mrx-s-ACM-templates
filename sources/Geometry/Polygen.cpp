

template<typename Point>
db Polygen_Square(std::vector<Point>& x) {
	db s = 0;
	for (int i = 1; i < x.size(); ++i) {
		s += cross(x[i - 1], x[i]);
	}
	return std::abs(s) / 2;//s>0:点是逆时针顺序,s<0:点是顺时针顺序
}

//求多边形重心
template<typename Point>
Pd polycenter(std::vector<Point> a) {
	int n = a.size();
	Pd ans(0, 0);
	a[0] = a[n];
	for (int i = 0; i < n; i++)ans = ans + (a[i] + a[i + 1]) * cross(a[i], a[i + 1]);
	return ans / Polygen_Square(a) / 6;
}

//判点在是否在多边形内或边上
template<typename Point>
bool point_in_polygon(Pl p, std::vector<Pl> a) {
	int n = a.size();
	int s = 0;
	for (int i = 0; i < n; i++) {
		auto u = a[i], v = a[(i + 1) % n];
		if (onSeg(p, u, v))return true;
		if (sgn(u.y - v.y) <= 0)std::swap(u, v);
		if (sgn(p.y - u.y) > 0 || sgn(p.y - v.y) <= 0)continue;
		if (sgn(cross(v - p, u - p)) == 1)++s;
	}
	return s & 1;
}