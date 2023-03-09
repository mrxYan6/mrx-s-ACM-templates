{
    vector<ll> dis(n * 2, 0x3f3f3f3f3f3f3f3f);
    vector<pair<int, ll>> G[n * 2];
    auto dij = [&](int start) {
        priority_queue<nod> q;
        dis[start] = 0;
        q.emplace(start, 0);
        while (!q.empty()) {
            auto [u, dist] = q.top();
            q.pop();
            if (dis[u] != dist)continue;
            for (auto [v, w]: G[u]) {
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.emplace(v, dis[v]);
                }
            }
        }
    };
    
}