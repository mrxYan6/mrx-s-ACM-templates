#include <complex>
#include <vector>


using i64 = long long;
using Z = std::complex<long double>;
const double pi = std::acos(-1);
std::vector<int> rev;
std::vector<Z> roots{(0, 1), (0, 1)};

void dft(std::vector<Z>& a) {
	int n = a.size();

	if (int(rev.size()) != n) {
		rev.resize(n);
		for (int i = 0; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
		}
	}

	for (int i = 0; i < n; ++i) {
		if (rev[i] < i)std::swap(a[i], a[rev[i]]);
	}
	if (int(roots.size() < n)) {
		int k = __builtin_ctz(roots.size());
		roots.resize(n);
		while ((1 << k) < n) {
			Z e(cos(acos(-1) / (1 << k)), sin(acos(-1) / (1 << k)));
			for (int i = 1 << (k - 1); i < (1 << k); i++) {
				roots[i << 1] = roots[i];
				roots[i << 1 | 1] = roots[i] * e;
			}
			k++;
		}
	}

	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
			for (int j = 0; j < k; j++) {
				Z u = a[i + j];
				Z v = a[i + j + k] * roots[k + j];
				a[i + j] = u + v;
				a[i + j + k] = u - v;
			}
		}
	}
}

void idft(std::vector<Z>& a) {
	int n = a.size();
	std::reverse(a.begin() + 1, a.end());
	dft(a);
}

struct Poly : public std::vector<i64> {
	using std::vector<i64>::vector;

	Poly() {}

	Poly(const std::vector<i64>& a) : std::vector<i64>(a) {}

	Poly(const std::initializer_list<i64>& a) : std::vector<i64>(a) {}

	i64 operator [](int idx) const {
		if (idx > size())return 0;
		else return *(begin() + idx);
	}

	i64& operator [](int idx) { return *(begin() + idx); }

	friend Poly operator +(const Poly& a, const Poly& b) {
		Poly res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); i++) {
			res[i] = a[i] + b[i];
		}
		return res;
	}

	friend Poly operator -(const Poly& a, const Poly& b) {
		Poly res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); i++) {
			res[i] = a[i] - b[i];
		}
		return res;
	}

	friend Poly operator *(const Poly& a, const Poly& b) {
		if (a.size() == 0 || b.size() == 0) {
			return Poly();
		}
		int sz = 1, tot = a.size() + b.size() - 1;
		while (sz < tot) {
			sz *= 2;
		}
		std::vector<Z> f(sz);
		for (int i = 0; i < a.size(); ++i)f[i].real(a[i]);
		for (int i = 0; i < b.size(); ++i)f[i].imag(b[i]);
		dft(f);
		for (int i = 0; i < sz; ++i) {
			f[i] = f[i] * f[i];
			f[i] /= sz, f[i] /= 2;
		}
		idft(f);
		Poly ans(tot);
		for (int i = 0; i < tot; ++i)ans[i] = f[i].imag() + 0.5;
		return ans;
	}

	friend Poly operator *(i64 a, Poly b) {
		for (int i = 0; i < int(b.size()); i++) {
			b[i] *= a;
		}
		return b;
	}

	friend Poly operator *(Poly a, i64 b) {
		for (int i = 0; i < int(a.size()); i++) {
			a[i] *= b;
		}
		return a;
	}

	Poly operator <<(const int k) const {
		auto b = *this;
		b.insert(b.begin(), k, 0);
		return b;
	}

	Poly operator >>(const int k) const {
		if (size() <= k) {
			return {};
		}
		return {begin() + k, end()};
	}

	Poly& operator >>=(const int k) { return (*this) = (*this) >> k; }

	Poly& operator <<=(const int k) { return (*this) = (*this) << k; }

	Poly modxk(int k) const {
		k = std::min(k, (int) size());
		return {begin(), begin() + k};
	}

	Poly& operator +=(const Poly& b) { return (*this) = (*this) + b; }

	Poly& operator -=(const Poly& b) { return (*this) = (*this) - b; }

	Poly& operator *=(const Poly& b) { return (*this) = (*this) * b; }
};