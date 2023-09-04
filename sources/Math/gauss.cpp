
#include <bitset>

struct xorGauss{
	std::bitset<300>  Equal[600];
	int equ,m;
	bool gauss() {
		int row = 1, col = 1;
		for (; row <= equ && col <= m; ++col) {
			int nxt;
			for (nxt = row; nxt < equ; nxt++)if (Equal[nxt][col])break;
			if (Equal[nxt][col]) {
				swap(Equal[nxt], Equal[row]);
				for (int r = 1; r <= equ; ++r) {
					if (row == r)continue;
					if (Equal[r][col]) Equal[r] ^= Equal[row];
				}
				row++;
			}
		}
		for (; row <= equ; ++row)
			if (Equal[row][0]) {
				return 0;
			}
		return 1;
	}
};

const double eps = 1E-9;
#include <vector>
struct mathGauss{
	std::vector<std::vector<double>> mat;
	int n,m;
	mathGauss(int n,int m):n(n),m(m){
		mat.resize(n);
		for(auto &x:mat){
			x.resize(m);
		}
	}
	void gauss() {
		for (int row = 0; row < n; ++row) {
			int nxt;
			for (nxt = row; nxt < n - 1; nxt++)if (std::abs(mat[nxt][row]) > eps)break;
			if (std::abs(mat[nxt][row]) < eps)continue;
			std::swap(mat[nxt], mat[row]);
			for (int r = 0; r < n; ++r) {
				if (row == r)continue;
				for (int j = m - 1; j >= row; --j)mat[r][j] -= mat[r][row] / mat[row][row] * mat[row][j];
			}
		}
	}
};