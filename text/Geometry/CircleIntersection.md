# 圆与圆交

## 内容
求出两个圆之间的交点，通过简单的三角函数运算就可以了，为简单的高中数学题

## trick
### 求多大的圆可以覆盖若干个点
二分圆的半径r，然后反向考虑，一个圆覆盖若干个点意味着这些点到圆心的距离小于半径r，那么每个点做一个半径为r的圆，然后求这些圆的交，如果交出来的圆的面积大于0，那么说明这个半径r是可行的，否则不可行。

然而面积并不好求，可以转化为求圆与圆的交点，然后对于这些相交的弧进行区间加法，然后在没个圆上面进行差分和前缀和，就能快速求出一段圆弧和多少其他圆相交，从而求出有多少点可以被覆盖。

上述维护通过反三角函数就可以。

**千万注意只能维护三角函数，不然可能出现精度太高导致的误差然后导致wa**

有一个类似的维护圆上的弧的题:

**[牛客23多校第四场B](https://ac.nowcoder.com/acm/contest/57358/C)**

题意:在半径为 $r_1+r_2$ ，圆心为$P$的圆中任意取一个点 $Q$ ，再以 $Q$ 为圆心做一个半径为 $R$ 的圆，平面上还有若干个带有权值的点，使得圆$Q$包含的点的权值和最大。（权值可能有负数）

这个题转化一下也变成了维护圆弧的权重，但是在圆弧上的点可以使其偏离一小部分，使得其并取不到这个圆的权值，但是依旧取到其他与这个圆相交的圆的权值。
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cassert>

using i64 = long long;
using db = double;
constexpr db eps = 1e-6;
const db pi = acos(-1);
const i64 inf = 1e15;
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

	Point<db> operator *(const db& rhs) const { return {x * rhs, y * rhs}; }

	Point<db> operator /(const db& rhs) const { return {x / rhs, y / rhs}; }

	friend db abs(const Point& lhs) { return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y); }

	friend db abs2(const Point& lhs) { return (lhs.x * lhs.x + lhs.y * lhs.y); }

	friend T cross(const Point& lhs, const Point& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

	friend T dot(const Point& lhs, const Point& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

	friend db angle(const Point& rhs) { return std::atan2(rhs.y, rhs.x); }

	Point rotate90() const { return {-y, x}; }

    Point<db> trunc(db r) const { return (*this) / (abs(*this)) * r; }

    Point<db> rotate(db cos, db sin) { return {x * cos - y * sin, x * sin + y * cos};}

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


struct circle {
    Pd c; 
    db r;
    circle():c(0.0,0.0), r(0) {}
    circle (Pd _c, db _r) : c(_c), r(_r) {}
};

bool not_cross(const circle a,const circle b) {
    db d = abs(a.c - b.c);
    return sgn(d - a.r - b.r) > 0 || sgn(d + a.r - b.r) < 0;
}


void solve() {
    int n;
    Pd p;
    db r1, r2, R;
    std::cin >> n >> r1 >>r2 >> R >> p;
    std::vector<Pd> ps(n);

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> ps[i];
    }

    std::vector<circle> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = circle(ps[i], R);
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        if (sgn(abs(c[i].c - p) - R) <= 0) {
            ans += a[i];
        }
    }
    
    circle atk (p, r1 + r2);
    
    std::vector<std::map<double, i64>> inter(n);


    for (int i = 0; i < n; ++i) {
        i64 cur = std::max(0, a[i]);
        auto get = [&] (db x) {
            while (x >= pi) x-=pi*2;
            while (x < pi) x+=pi*2;
            return x;
        };

        auto ins = [&] (int i, i64 v, db x, db y) {
            db l (get(x)), r (get(y));
            
            if (l < r) {
                inter[i][l] += v;
                inter[i][r] -= v;
            } else {
                cur += v;
                inter[i][r] -= v;
                inter[i][l] += v;
            }
        };
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
                db d = abs(c[i].c - c[j].c);
                if (sgn(d - 2 * R) > 0) continue;
                db k = angle(c[j].c - c[i].c);
                db rad = std::acos(d / 2 / R);
                ins(i, a[j], k - rad, k + rad);
        }

        if (not_cross(atk, c[i]))continue;

        {
                db d = abs(c[i].c - atk.c);
                db  k = angle(atk.c - c[i].c);
                db rad = acos((c[i].r * c[i].r + d * d - atk.r * atk.r) / 2 / R / d);
                cur -= inf;
                ins(i, inf, k - rad, k + rad);
        }

        ans = std::max(ans, cur);
        for (auto [k, v] : inter[i]) {
            cur += v;
            ans = std::max(ans, cur);
        }
    } 

    
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
```

