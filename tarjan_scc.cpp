#include <vector>
#include <stack>
#include <functional>


int n;
std::vector<std::vector<int>> G(n, std::vector<int>());
std::vector<bool> inStack(n, false);
std::vector<int> dfn(n, -1), low(n, -1);
std::vector<int> f(n), val(n), wei(n);
std::stack<int> s;
int id = 0, sccCnt = 0;
std::function<void(int)> tarjan = [&](int u) -> void {
    low[u] = dfn[u] = id++;
    s.push(u), inStack[u] = true;
    for (auto v: G[u]) {
        if (dfn[v] == -1) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], low[v]);
        }
    }
    if (dfn[u] == low[u]) {
        while (s.top() != u) {
            auto x = s.top();
            s.pop();
            inStack[x] = false;
            f[x] = sccCnt;
            val[sccCnt] += wei[x];
        }
        s.pop();
        inStack[u] = false;
        f[u] = sccCnt;
        val[sccCnt] += wei[u];
        sccCnt++;
    }
    return;
};