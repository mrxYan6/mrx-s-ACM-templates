
using polygen = std::vector<Pd>;

db Polygen_Square(polygen& x) {
	db s = 0;
	for (int i = 1; i < x.size(); ++i) {
		s += cross(x[i - 1], x[i]);
	}
	return std::abs(s) / 2;//s>0:点是逆时针顺序,s<0:点是顺时针顺序
}

//求多边形重心
Pd polycenter(polygen a) {
	int n = a.size();
	Pd ans(0, 0);
	a[0] = a[n];
	for (int i = 0; i < n; i++)ans = ans + (a[i] + a[i + 1]) * cross(a[i], a[i + 1]);
	return ans / Polygen_Square(a) / 6;
}

//判点在是否在多边形内或边上
bool point_in_polygon(Pd p, polygen a) {
	int n = a.size();
	int s = 0;
	a[n + 1] = a[1];
	for (int i = 0; i < n; i++) {
		Pd u = a[i], v = a[(i + 1) % n];
		if (onSeg(p, u, v))return true;
		if (cmp(u.y, v.y) <= 0)std::swap(u, v);
		if (cmp(p.y, u.y) > 0 || cmp(p.y, v.y) <= 0)continue;
		if (sgn(cross(v - p, u - p)) == 1)++s;
	}
	return s & 1;
}