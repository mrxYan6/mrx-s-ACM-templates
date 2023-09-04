//0-1trie 维护异或最小值

#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <queue>
#include <array>
#include <bitset>
#include <string>

using i64 = long long;

struct trie {
    std::vector<std::array<int, 2>> nxt;
    std::vector<int> end, times;
    std::vector<int> dp;

    trie() {
        nxt.reserve(1000000);
        end.reserve(1000000);
        times.reserve(1000000);
        dp.reserve(1000000);
        dp.push_back(0);
        nxt.push_back(std::array<int, 2>{});
        end.push_back(0);
        times.push_back(0);
    }

    int NEW() {
        end.push_back(0);
        nxt.push_back(std::array<int, 2>{});
        times.push_back(0);
        dp.push_back(0);
        return end.size() - 1;
    }

    void update(int rt, int dep) {
        if (nxt[rt][0] == 0 && nxt[rt][1] == 0) {
            dp[rt] = 0;
        } else if (nxt[rt][0] == 0) {
            dp[rt] = dp[nxt[rt][1]] ^ (times[nxt[rt][1]] == 1 ? 1 << dep : 0);
        } else if (nxt[rt][1] == 0) {
            dp[rt] = dp[nxt[rt][0]];
        } else {
            if (times[nxt[rt][0]] == 1 && times[nxt[rt][1]] == 1) {
                dp[rt] = dp[nxt[rt][0]] ^ dp[nxt[rt][1]] ^ (1 << dep);
            } else {
                int res = 0x7fffffff;
                if (times[nxt[rt][0]] >= 2) {
                    res = std::min(res, dp[nxt[rt][0]]);
                } 
                if (times[nxt[rt][1]] >= 2){
                    res = std::min(res, dp[nxt[rt][1]]);
                }
                dp[rt] = res;
            }
        }
    }

    void insert(int rt, int idx, const std::string &s) {
        if (idx == s.length()) {
            times[rt]++;
            dp[rt] = 0;
            return;
        }
        int c = s[idx] - '0';
        if (nxt[rt][c] == 0) {
            nxt[rt][c] = NEW();
        }
        times[rt] -= times[nxt[rt][c]];
        insert(nxt[rt][c], idx + 1, s);
        update(rt, 30 - idx);
        times[rt] += times[nxt[rt][c]];
    }

    void erase(int rt, int idx, const std::string &s) {
        if (idx == s.length()) {
            times[rt]--;
            return;
        }

        int c = s[idx] - '0';
        if (nxt[rt][c] != 0) {
            times[rt] -= times[nxt[rt][c]];
            erase(nxt[rt][c], idx + 1, s);
            if (times[nxt[rt][c]] == 0) {
                nxt[rt][c] = 0;
            }
            update(rt, 30 - idx);
            times[rt] += times[nxt[rt][c]];
        }
    }

    int query(int rt){
        return dp[rt];
    }
};
