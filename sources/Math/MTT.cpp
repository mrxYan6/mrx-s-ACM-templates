template<typename T>
T power(T a, long long b, int mod) {
	T ans = 1;
	for (; b; a = 1ll * a * a % mod, b >>= 1) {
		if (b & 1)ans = 1ll * ans * a % mod;
	}
	return ans;
}

int mod;
using Z = std::complex<long double>;
using i64 = long long;
const double pi = std::acos(-1);
std::vector<int> rev;
std::vector<Z> roots{(0, 1), (0, 1)};

int getsz(int x) {
	int sz = 1;
	while (sz < x)sz *= 2;
	return sz;
}

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

template<typename U>
static U norm(U& x, int Mod) {
	if (-Mod <= x && x < Mod) x = static_cast<U>(x);
	else x = static_cast<U>(x % Mod);
	if (x < 0) x += Mod;
	return x;
}

struct Poly : public std::vector<i64> {
	using std::vector<i64>::vector;

	i64 operator [](int idx) const {
		if (idx > size())return 0;
		else return *(begin() + idx);
	}

	i64& operator [](int idx) { return *(begin() + idx); }

	friend Poly operator +(const Poly& a, const Poly& b) {
		Poly res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); i++) {
			res[i] = a[i] + b[i];
			norm(res[i], mod);
		}
		return res;
	}

	friend Poly operator -(const Poly& a, const Poly& b) {
		Poly res(std::max(a.size(), b.size()));
		for (int i = 0; i < int(res.size()); i++) {
			res[i] = a[i] - b[i];
			norm(res[i], mod);
		}
		return res;
	}

	friend Poly operator *(int a, Poly b) {
		for (int i = 0; i < int(b.size()); i++) {
			b[i] *= a;
		}
		return b;
	}

	friend Poly operator *(Poly a, int b) {
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
		return Poly(begin() + k, end());
	}

	Poly& operator >>=(const int k) {
		return (*this) = (*this) >> k;
	}

	Poly& operator <<=(const int k) {
		return (*this) = (*this) << k;
	}

	Poly mulxk(int k) const {
		return *this << k;
	}

	Poly modxk(int k) const {
		k = std::min(k, (int) size());
		return Poly(begin(), begin() + k);
	}

	Poly divxk(int k) const {
		if (size() <= k) {
			return {};
		}
		return Poly(begin() + k, end());
	}

	Poly& operator +=(const Poly& b) {
		return (*this) = (*this) + b;
	}

	Poly& operator -=(const Poly& b) {
		return (*this) = (*this) - b;
	}

	Poly& operator *=(const Poly& b) {
		return (*this) = (*this) * b;
	}


	Poly deriv() const {
		if (empty()) {
			return {};
		}
		Poly res(size() - 1);
		for (int i = 0; i < size() - 1; ++i) {
			res[i] = (i + 1) * (*this)[i + 1] % mod;
		}
		return res;
	}

	Poly integr() const {
		Poly res(size() + 1);
		for (int i = 0; i < size(); ++i) {
			res[i + 1] = (*this)[i] * power(i + 1, mod - 2, mod);
		}
		return res;
	}

	friend Poly operator *(const Poly& x, const Poly& y) {
		if (x.empty() || y.empty())return {};
		Poly a(x), b(y);
		int len = a.size() + b.size() - 1, n = getsz(len);
		vector<Z> f(n), g(n), p(n), q(n);
		for (int i = 0; i < a.size(); i++)
			f[i] = Z(a[i] >> 15, a[i] & 0x7fff);
		for (int i = 0; i < b.size(); i++)
			g[i] = Z(b[i] >> 15, b[i] & 0x7fff);
		dft(f), dft(g);
		for (int i = 0; i < n; ++i) {
			int r = (n - i) & (n - 1);
			p[i] = Z(0.5 * (f[i].real() + f[r].real()), 0.5 * (f[i].imag() - f[r].imag())) * g[i];
			q[i] = Z(0.5 * (f[i].imag() + f[r].imag()), 0.5 * (f[r].real() - f[i].real())) * g[i];
		}
		idft(p), idft(q);
		for (int i = 0; i < n; ++i)p[i] /= n, q[i] /= n;
		a.resize(len);
		for (int i = 0; i < len; i++) {
			long long X, Y, Z, W;
			X = p[i].real() + 0.5, Y = p[i].imag() + 0.5;
			Z = q[i].real() + 0.5, W = q[i].imag() + 0.5;
			a[i] = ((X % mod << 30) + ((Y + Z) % mod << 15) + W) % mod;
		}
		return a;
	}

	Poly inv(int m) const {
		Poly x{(power((*this)[0], mod - 2, mod))};
		int k = 1;
		while (k < m) {
			k <<= 1;
			x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
		}
		return x;
	}
};