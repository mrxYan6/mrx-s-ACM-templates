auto prefix_algorithm = [&] (const std::string& s) {
    int n = s.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
};

auto get_occurrences = [&] (const std::string& text, const std::string& pattern) {
    std::string cur = pattern + "*" + text;
    int n = text.length(), m = pattern.length();
    std::vector<int> v;
    auto lps = prefix_algorithm(cur);
    for (int i = m + 1; i < n + m + 1; ++i) {
        if (lps[i] == m) {
            v.push_back(i - m);
        }
    }
    return v;
};