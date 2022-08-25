// https://cses.fi/problemset/task/1693/

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
vector<int> g[N];
int in[N], out[N];

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        in[v] ++;
        out[u] ++;
    }
    vector<int> a, b;
    if(out[1] != in[1] + 1) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    if(in[n] != out[n] + 1) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    for(int i = 2; i < n; ++i) {
        if(in[i] != out[i]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    a.push_back(1);
    while(!a.empty()) {
        int x = a.back();
        if(g[x].empty()) {
            b.push_back(a.back());
            a.pop_back();
        }
        else{
            a.push_back(g[x].back());
            g[x].pop_back();
        }
    }
    for(int i = 1; i <= n; ++i) {
        if(!g[i].empty()) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    while(!a.empty()) b.push_back(a.back()), a.pop_back();
    for(int i = (int)b.size() - 1; i >= 0; --i) cout << b[i] << " ";
    cout << '\n';

    return 0;
}
