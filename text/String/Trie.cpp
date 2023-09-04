#include <vector>
#include <array>
#include <string>

struct trie {
    std::vector<std::array<int, 26>> nxt;
    std::vector<int> end, times;

    trie() {
        nxt.reserve(1000000);
        end.reserve(1000000);
        times.reserve(1000000);
        nxt.push_back(std::array<int, 26>{});
        end.push_back(0);
        times.push_back(0);
    }

    int NEW() {
        end.push_back(0);
        nxt.push_back(std::array<int, 26>{});
        times.push_back(0);
        return end.size() - 1;
    }

    void insert (const std::string &s) {
        int cur = 0;
        for (auto c : s) {
            int &nxt_cur = nxt[cur][c - 'a'];
            if (nxt_cur == 0) {
                nxt_cur = NEW();
            }
            cur = nxt_cur;
        }
        // std::cout << s << "::RT" << cur << '\n';
        end[cur]++;
    }

    int find(const std::string s) {
        int cur = 0;
        for (auto c : s) {
            int &nxt_cur = nxt[cur][c - 'a'];
            if (nxt_cur == 0) {
                return 0;
            }
            cur = nxt_cur;
        }
        return end[cur] != 0;
    }
};
