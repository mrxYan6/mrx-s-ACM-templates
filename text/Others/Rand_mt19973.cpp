std::random_device dv;
std::mt19937_64 g(dv());
std::cout << g() << '\n';
std::vector<int> a{12, 23123, 2134, 421, 123, 123};
std::shuffle(a.begin(), a.end(), g);
for (auto x: a)std::cout << x << ' ';