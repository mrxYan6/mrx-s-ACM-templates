//z[0] = 0
auto z_algorithm = [&] (const std::string& s) {
	int n = s.length();
	std::vector<int> z(n, 0);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r && z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			z[i] = std::max(0, r - i + 1);
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
				++z[i];
			}
			if (i + z[i] - 1 > r) {
				l = i;
				r = i + z[i] - 1;
			}
		}
	}
	return z;
};

//如果要求b的所有后缀对于a的LCP只需要求 a + "*" + b 的 Z algorithm 就行。

auto get_lcp = [&] (const std::string& text, const std::string& pattern) {
	std::string cur = pattern + "*" + text;
	int n = text.length(), m = pattern.length();
	auto z = z_algorithm(cur);
	return std::vector(z.begin() + m + 1, z.end());
};