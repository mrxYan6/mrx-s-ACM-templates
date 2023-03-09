#include <vector>
#include <queue>

using i64 = long long;

struct NetworkFlow {
    struct edge {
        int u, v;
        i64 cap, flow;

        edge(int _u, int _v, i64 _cap, i64 _flow) : u(_u), v(_v), cap(_cap), flow(_flow) {}
    };

    std::vector<edge> E;
    std::vector<std::vector<int>> G;
    int S, T;
    std::vector<int> dep, cur, vis;

    NetworkFlow(int n) {
        G.resize(n, std::vector<int>());
        dep.resize(n), cur.resize(n), vis.resize(n);
        E.clear();
    }

    void addEdge(int u, int v, int cap, int cap_) {
        G[u].push_back((int) E.size());
        E.emplace_back(u, v, cap, 0);
        G[v].push_back((int) E.size());
        E.emplace_back(v, u, cap_, 0);
    }

    bool bfs() {
        std::fill(vis.begin(), vis.end(), 0);
        std::queue<int> q;
        q.push(S);
        vis[S] = 1;
        dep[S] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto edgeID: G[now]) {
                auto &e = E[edgeID];
                if (!vis[e.v] && e.cap > e.flow) {
                    vis[e.v] = 1;
                    dep[e.v] = dep[e.u] + 1;
                    q.push(e.v);
                }
            }
        }
        return vis[T];
    }

    i64 dfs(int x, i64 flow) {
        if (flow == 0 || x == T) {
            return flow;
        }
        i64 now = 0, f;
        for (auto &w = cur[x]; w < G[x].size(); ++w) {
            edge &e = E[G[x][w]];
            if (dep[e.v] == dep[x] + 1 && (f = dfs(e.v, std::min(flow, e.cap - e.flow))) > 0) {
                e.flow += f;
                E[G[x][w] ^ 1].flow -= f;
                now += f;
                flow -= f;
                if (flow == 0)break;
            }
        }
        return now;
    }

    i64 dinic(int s, int t) {
        S = s, T = t;
        i64 flow = 0;
        while (bfs()) {
            std::fill(cur.begin(), cur.end(), 0);
            flow += dfs(S, 0x3f3f3f3f3f3f3f3f);
        }
        return flow;
    }
};
