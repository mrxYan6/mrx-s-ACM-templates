#include <vector>
#include <iostream>

using i64 = long long;

struct hashtable {
	const int max_size = 19260817;
	int size;

	std::vector<int> nxt, head;
	std::vector<i64> val, key;

	hashtable() : size(0), head(max_size, -1) {}

	void add(int x, i64 v) {
		key.push_back(v);
		val.push_back(0);
		nxt.push_back(head[x]);
		head[x] = int(key.size()) - 1;
	}

	bool find(int x) {
		for (int i = head[x]; ~i; i = nxt[i])if (key[i] == x)return true;
		return false;
	}

	i64& operator [](const i64& x) {
		for (int i = head[x % max_size]; ~i; i = nxt[i])if (key[i] == x)return val[i];
		add(int(x % max_size), x);
		return val.back();
	}
};

int main(){
    int x = 1;
    std::cout << x << '\n';
}