struct Dinic {
    struct edge {
        int u, v;
        long long cap, flow = 0;
        edge(int u, int v, long long cap) : u(u), v(v), cap(cap) {}
    };

    const long long flow_inf = LLONG_MAX;
    vector<edge> edges;
    vector<vector<int>> g;
    vector<int> lvl, ptr;
    queue<int> q;
    int n, src, sink, edge_cnt;

    Dinic(int n, int s, int t) : n(n), src(s), sink(t) {
        g.resize(n + 1);
        lvl.assign(n + 1, -1);
        ptr.resize(n + 1);
        edge_cnt = 0;
    }

    void add_edge(int u, int v, long long cap) {
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        g[u].push_back(edge_cnt ++);
        g[v].push_back(edge_cnt ++);
    }

    bool bfs() {
        lvl[src] = 0;
        q.push(src);
        while(!q.empty()) {
            int  u = q.front();
            q.pop();
            for(auto id : g[u]) {
                if(edges[id].cap - edges[id].flow < 1 || lvl[edges[id].v] != - 1) continue;
                lvl[edges[id].v] = lvl[u] + 1;
                q.push(edges[id].v);
            }
        }
        return lvl[sink] != -1;
    }

    long long dfs(int node, long long pushed) {
        if(!pushed || node == sink) return pushed; 
        for(int& id = ptr[node]; id < (int)g[node].size(); ++id) {
            int edge_id = g[node][id];
            int next = edges[edge_id].v;
            if(lvl[next] != 1 + lvl[node] || edges[edge_id].cap - edges[edge_id].flow < 1) continue;
            long long res = dfs(next, min(pushed, edges[edge_id].cap - edges[edge_id].flow));
            if(res == 0) continue;
            edges[edge_id].flow += res;
            edges[edge_id ^ 1].flow -= res;
            return res;
        }
        return 0;
    }

    long long flow() {
        long long ans = 0;
        while(bfs()) {
            while(long long pushed = dfs(src, flow_inf)) {
                ans += pushed;
            }
            fill(lvl.begin(), lvl.end(), - 1);
            fill(ptr.begin(), ptr.end(), 0);
        }
        return ans;
    }
};
