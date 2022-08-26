// https://codeforces.com/contest/732/submission/169723323

#include<bits/stdc++.h>
using namespace std;

const int N = 4e5 + 1;
vector<pair<int, int>> g[N];
int vis[N], tin[N], low[N], timer, comp[N], sz[N], u[N], v[N], bridges[N], processed[N];

void dfs(int node, int p = -1) {
    vis[node] = 1;
    tin[node] = low[node] = ++ timer;
    for(auto [i, e] : g[node]) {
        if(i == p) continue;
        if(vis[i]) {
            low[node] = min(low[node], tin[i]);
        }
        else {
            dfs(i, node);
            low[node] = min(low[node], low[i]);
            if(low[i] > tin[node]) {
                bridges[e] = 1;
            }
        }
    }
} 

void create_comp(int node, int c) {
    vis[node] = 1;
    comp[node] = c;
    sz[c] ++;
    for(auto [i, e] : g[node]) {
        if(vis[i] || bridges[e]) continue;
        create_comp(i, c);
    }
}

void dfs_tree(int node, int p = -1) {
    vis[node] = 1;
    for(auto [i, e] : g[node]) {
        if(i == p) continue;
        if(bridges[e]) {
            if(u[e] != i) swap(u[e], v[e]);
        }
        else if(!processed[e]) {
            if(u[e] != node) swap(u[e], v[e]);
        }
        processed[e] = 1;
        if(!vis[i]) dfs_tree(i, node);
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i];
        g[u[i]].push_back({v[i], i});
        g[v[i]].push_back({u[i], i});
    }
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    memset(vis, 0, sizeof vis);
    int cnt = 1;
    for(int i = 1; i <= n; ++i) {
        if(!vis[i]) {
            create_comp(i, cnt);
            cnt ++;
        }
    }
    int node = 0, ans = 0;
    for(int i = 1; i <= n; ++i) {
        if(sz[comp[i]] > ans) {
            ans = sz[comp[i]];
            node = i;
        }
    }
    cout << ans << '\n';
    memset(vis, 0, sizeof vis);
    dfs_tree(node);
    for(int i = 0; i < m; ++i) {
        cout << u[i] << " " << v[i] << '\n';
    }

    return 0;
}
