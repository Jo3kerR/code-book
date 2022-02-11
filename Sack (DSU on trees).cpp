// https://codeforces.com/contest/1009/problem/F
// https://codeforces.com/blog/entry/44351

#include<bits/stdc++.h>
using namespace std;
using ll = long long ;

const int N = 1e6 + 1;
vector<int> g[N];
int sz[N], d[N], ans[N], cnt[N];

void pre(int node, int par = 0) {
    sz[node] = 1;
    for(auto i : g[node]) {
        if(i != par) {
            d[i] = d[node] + 1 ;
            pre(i, node) ;
            sz[node] += sz[i];
        }
    }
}

vector<int> *v[N] ; // contains the nodes of each subtree, storing them thorugh pointers so
multiset<pair<int,int>> s;

void dfs(int node, int par = -1, bool keep = 0) {
    int mx = -1, big_child = -1;
    for(auto i : g[node]) {
        if(i != par && mx < sz[i]) {
            mx = sz[i];
            big_child = i;
        }
    }
    for(auto i : g[node]) {
        if(i != par && i != big_child) {
            dfs(i, node);
        }
    }
    if(big_child != -1) {
        dfs(big_child, node, 1) ;
        v[node] = v[big_child] ; // O(1), v[node] points to the vector pointed by v[big child]
    }
    else {
        v[node] = new vector<int>(); // create new vector
    }
    v[node] -> push_back(node);
    
    // update (something) of current node
    if(cnt[d[node]]) {
        s.erase(s.find({cnt[d[node]], - d[node]}));
    }
    cnt[d[node]] ++ ;
    s.insert({cnt[d[node]], - d[node]});
    
    // update (something) from subtree of all children except big child
    for(auto i : g[node]) {
        if(i != par && i != big_child) {
            for(auto x : *v[i]) {
                if(cnt[d[x]]) s.erase(s.find({cnt[d[x]], - d[x]}));
                cnt[d[x]] ++ ;
                s.insert({cnt[d[x]], - d[x]});
                v[node] -> push_back(x);
            }
        }
    }
  
    // calc ans
    ans[node] = - s.rbegin() -> second - d[node] ;

    if(!keep) {
        for(auto x : *v[node]) {
            // delete (something) from subtree of current node because cnt[] is global
            s.erase(s.find({cnt[d[x]], - d[x]}));
            cnt[d[x]] -- ;
            if(cnt[d[x]]) s.insert({cnt[d[x]], - d[x]});
        }
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0) ;

    int n; cin >> n ;
    for(int i = 1 ; i < n ; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    pre(1);
    dfs(1);
    cout << endl ;
    for(int i = 1; i <= n ; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}

