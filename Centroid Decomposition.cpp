// more efficient: calculate the answer while building the CD tree, check the code below
// https://codeforces.com/contest/161/submission/168221729
// problems: https://codeforces.com/blog/entry/73707

struct centroid_decomposition {
    int n;
    vector<int> sz, par;
    vector<set<int>> g;
    void init(int _n) {
        n = _n;
        sz.resize(n + 1);
        par.resize(n + 1);
        g.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].insert(v);
        g[v].insert(u);
    }
    int find_size(int node, int p = -1) {
        sz[node] = 1;
        for(auto i : g[node]) {
            if(i == p) continue;
            sz[node] += find_size(i, node);
        }
        return sz[node];
    }
    int find_centroid(int node, int r, int p = -1) {
        for(auto i : g[node]) {
            if(i != p && sz[i] * 2 > r) return find_centroid(i, r, node);
        }
        return node;
    }
    void delete_node(int x) {
        for(auto i : g[x]) g[i].erase(x);
    }
    int find_cd_tree(int x) {
        int centroid = find_centroid(x, find_size(x));
        delete_node(centroid);
        for(auto i : g[centroid]) {
            par[find_cd_tree(i)] = centroid;
        }
        return centroid;
    }
};
