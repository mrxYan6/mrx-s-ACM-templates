template <int alphabet_size>
struct AhoCorasick {
    struct node {
        int len, cnt;
        int fail;
        std::array<int,alphabet_size> next;

        node() : len(), fail(0), cnt(0) {
            next.fill(0);
        }

    };  
    std::vector<node> t;

    int New() {
        t.emplace_back();
        return t.size() - 1;
    }

    AhoCorasick() {
        New();
        t[0].fail = 0;
        t[0].len = -1;
        t[0].cnt = 0;
        t[0].next.fill(1);
        New();
    }

    void insert (const std::vector<int> & s) {
        int now = 1;
        for (auto c : s){
            if (!t[now].next[c]) {
                t[now].next[c] = New();
                t[t[now].next[c]].len = t[now].len + 1;
            }
            now = t[now].next[c];
            t[now].cnt++;
        }
    }

    void insert (const std::string &s, char offset = 'a') {
        std::vector<int> v(s.size());
        for (int i = 0; i < s.size(); ++i) {
            v[i] = s[i] - offset;
        }
        insert(v);
    }

    void build() {
        std::queue<int> q;

        q.emplace(1);
        while(!q.empty()) {
            auto x = q.front();
            q.pop();

            for (int i = 0; i < alphabet_size; ++i) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].fail].next[i];
                } else {
                    t[t[x].next[i]].fail = t[t[x].fail].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }

    int query_end(const std::vector<int> b) {
        int x = 1;
        for (auto c : b) {
            x = t[x].next[c];
        }
        return x;
    }

    int query_end(const std::string s, char offset = 'a') {
        std::vector<int> b(s.size());
        for (int i = 0; i < s.size(); ++i) {
            b[i] = s[i] - offset;
        }
        return query_end(b);
    }

    int next(int p, int x) {
        return t[p].next[x];
    }

    int next(int p, char x, char offset = 'a') {
        return next(p, x - offset);
    }

    int fail(int p) {
        return t[p].fail;
    }

    int len(int p) {
        return t[p].len;
    }

    int size() {
        return t.size();
    }
};
