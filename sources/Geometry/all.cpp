#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using i64 = long long;
using db = double;
constexpr db eps = 1e-6;

int sgn(db x) {
	return x < -eps ? -1 : x > eps;
}

int sgn(i64 x) {
	return x < 0 ? -1 : x > 0;
}
template<typename T>
struct Point {
	T x, y;

	template<class Y>
	Point(const Point<Y>& cp):x(cp.x), y(cp.y) {}

	Point() : x(0), y(0) {}

	Point(T _x, T _y) : x(_x), y(_y) {}

	friend std::istream& operator >>(std::istream& is, Point& rhs) { return is >> rhs.x >> rhs.y; }

	friend std::ostream& operator <<(std::ostream& os, const Point& rhs) { return os << '(' << rhs.x << ',' << rhs.y << ')'; }

	Point operator -(const Point& rhs) const { return {x - rhs.x, y - rhs.y}; }

	Point& operator -=(const Point& rhs) { return (*this) = (*this) - rhs; }

	Point operator +(const Point& rhs) const { return {x + rhs.x, y + rhs.y}; }

	Point& operator +=(const Point& rhs) { return (*this) = (*this) + rhs; }

	template<class Y>
	Point operator *(const Y& rhs) const { return {x * rhs, y * rhs}; }

	template<class Y>
	Point<db> operator /(const Y& rhs) { return {x / rhs, y / rhs}; }

	friend db abs(const Point& lhs) { return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y); }

	friend i64 abs2(const Point& lhs) { return (lhs.x * lhs.x + lhs.y * lhs.y); }

    Point<db> trunc(db r) {
        return (*this) / abs(*this) * r;
    }

	friend T cross(const Point& lhs, const Point& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

	friend T dot(const Point& lhs, const Point& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	friend db angle(const Point& rhs) { return atan2(rhs.y, rhs.x); }

	Point rotate90() const { return {-y, x}; }

	Point<db> rotate(db deg) { return {x * cos(deg) - y * sin(deg), x * sin(deg) + y * cos(deg)}; }

	bool operator <(const Point& rhs) const { return sgn(x - rhs.x) == 0 ? sgn(y - rhs.y) < 0 : sgn(x - rhs.x) < 0; }

	bool operator ==(const Point& rhs) const { return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0; }

	bool up() const { return sgn(y) == 0 ? sgn(x) >= 0 : sgn(y) > 0; }
};

using Pl = Point<i64>;
using Pd = Point<db>;
template<typename T>
struct Line {
	Point<T> a, v;

	Line(const Point<T>& a, const Point<T>& b) : a(a), v(b - a) {}

	template<class Y>
	Line(const Point<Y>& cp) : a(cp.a), v(cp.v) {}

	Pd point(db t) {
		return a + v * t;
	}

	friend Point<db> intersection(const Line<T> lhs, const Line<T> rhs) {
		db t = (db) cross(rhs.a - lhs.a, rhs.v) / cross(lhs.v, rhs.v);
		return lhs.v * t + Point<db>(lhs.a);
	}

	db dis(const Point<T>& rhs) {
		return std::abs(cross(rhs - a, v)) / v.abs();
	}

	Line rotate(db deg) {
		Line<db> ans(*this);
		ans.v = Rotate(v, deg);
		return ans;
	}
};

using Ld = Line<db>;
using Ll = Line<i64>;

bool isCross(Pd a, Pd b, Pd i, Pd j) {
	return sgn(cross(i - a, j - i)) * sgn(cross(i - b, j - i)) == -1 && sgn(cross(b - i, a - b)) * sgn(cross(b - j, a - b)) == -1;
}

bool onSeg(Pd a, Pd i, Pd j) {
	return sgn(cross(i - a, j - a)) == 0 && sgn(dot(a - i, a - j)) < 0;
}

bool onLeft(Pl p, Ll l) {
	return cross(l.v, p - l.a) > 0;
}

template<typename Point>
std::vector<Point> ConvexHull(std::vector<Point> points) {
    int n = points.size();
    std::sort(points.begin(), points.end());
    std::deque<Point> dq;

    for (auto& point: points) {
        while (dq.size() > 1 && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], point - dq[dq.size() - 2])) <= 0)dq.pop_back();
        dq.push_back(point);
    }

    int k = int(dq.size());
    for (int i = n - 1; i >= 0; i--) {
        while (dq.size() > k && sgn(cross(dq[dq.size() - 1] - dq[dq.size() - 2], points[i] - dq[dq.size() - 2])) <= 0)dq.pop_back();
        dq.push_back(points[i]);
    }

    std::vector<Point> ans(dq.begin(), dq.end());
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

bool onLeft(Pd p, Ld l) {
	return cross(l.v, p - l.a) > 0;
}

template<typename Point>
std::vector<Point> hp(std::vector<Line<Point>>& lines) {
	std::sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
		auto d1 = l1.v;
		auto d2 = l2.v;
		if (d1.up() != d2.up()) {
			return d1.up() == 1;
		}
		return cross(d1, d2) > 0;
	});

	std::deque<Ld> ls;
	std::deque<Pd> ps;
	for (auto l: lines) {
		if (ls.empty()) {
			ls.push_back(l);
			continue;
		}

		while (!ps.empty() && !onLeft(ps.back(), l)) {
			ps.pop_back();
			ls.pop_back();
		}

		while (!ps.empty() && !onLeft(ps[0], l)) {
			ps.pop_front();
			ls.pop_front();
		}

		if (cross(l.v, ls.back().v) == 0) {
			if (dot(l.v, ls.back().v) > 0) {
				if (!onLeft(ls.back().a, l)) {
					assert(ls.size() == 1);
					ls[0] = l;
				}
				continue;
			}
			return {};
		}

		ps.push_back(intersection(ls.back(), l));
		ls.push_back(l);
	}

	while (!ps.empty() && !onLeft(ps.back(), ls[0])) {
		ps.pop_back();
		ls.pop_back();
	}
	if (ls.size() <= 2) {
		return {};
	}
	ps.push_back(intersection(ls[0], ls.back()));

	return {ps.begin(), ps.end()};
}


struct circle {
    Pd c; 
    db r;
    circle():c(0.0,0.0), r(0) {}
    circle (Pd _c, db _r) : c(_c), r(_r) {}
};

const db PI = acos(-1.0);

std::vector<Pd> circle_circle_intersection(const circle a,const circle b) {
    db d = abs(a.c - b.c);
    if(sgn(d - a.r - b.r) > 0 || sgn(d - std::abs(a.r - b.r)) < 0) return {};
    db l = (abs2(a.c - b.c) + a.r * a.r - b.r * b.r) / 2.0 / d;
    db h = std::sqrt(std::max(db(0), a.r * a.r - l * l));
    Pd vl = (b.c - a.c);
    Pd vh = vl.rotate90().trunc(h);
    vl = vl.trunc(l);
    Pd p1 = a.c + vl + vh;
    Pd p2 = a.c + vl - vh;
    return {p1, p2};
}

int main () {

}