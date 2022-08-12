// https://codeforces.com/contest/1416/submission/167595430
// https://codeforces.com/contest/1706/submission/167958460

// basically each edge becomes a node connecting the two nodes in the original tree
// requires path compression

const int N = 1e5 + 1;
const int M = 2e5 + 1;
const int K = 22;
vector<int> g[N + M];
int par[N + M], mx[N + M], vis[N + M], dp[N + M][K], d[N + M];

int get_par(int x) {
    return (x == par[x] ? x : par[x] = get_par(par[x]));
}

void dfs(int node, int p = 0) {
    mx[node] = max(mx[node], node);
    vis[node] = 1;
    dp[node][0] = p;
    for(int i = 1; i < K; ++i) {
        dp[node][i] = dp[dp[node][i - 1]][i - 1];
    }
    for(auto i : g[node]) {
        if(i == p) continue;
        d[i] = d[node] + 1;
        mx[node] = max(mx[node], mx[i]);
        if(!vis[i]) dfs(i, node);
    }
}

int LCA(int u, int v) {
    if(d[u] < d[v]) swap(u, v);
    int lg = K - 1;
    while(lg >= 0) {
        if(dp[u][lg] && d[dp[u][lg]] >= d[v]) u = dp[u][lg];
        -- lg;
    }
    if(u == v) return u;
    lg = K - 1;
    while(lg >= 0) {
        if(dp[u][lg] != dp[v][lg]) {
            u = dp[u][lg];
            v = dp[v][lg];
        }
        -- lg;
    }
    return dp[u][0];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T --) {
        int n, m, q;
        cin >> n >> m >> q;
        for(int i = 0; i <= n + m; ++i) {
            g[i].clear(), par[i] = i;
            mx[i] = 0;
            vis[i] = 0;
            d[i] = 0;
            for(int j = 0; j < K; ++j) dp[i][j] = 0;
        }
        int e = n;
        for(int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            u = get_par(u);
            v = get_par(v);
            ++ e;
            if(u == v) continue;
            g[e].push_back(u);
            g[e].push_back(v);
            par[u] = e;
            par[v] = e;
        }
        for(int i = e; i; --i) if(!vis[i]) dfs(i);
        vector<int> v(n + 1);
        for(int i = 1; i < n; ++i) {
            v[i + 1] = mx[LCA(i, i + 1)];
        }
    }

    return 0;
}
