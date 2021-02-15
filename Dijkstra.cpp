const int mxN = 2e5 + 5; 
long long d[mxN] ; 

void dijkstra(int s, int n) {

    for(int i = 1 ; i <= n ; ++i) d[i] = 1e18 ;
    d[s] = 0 ; 

    set<pair<int,int>> S ; 
    S.insert({0, s}); 

    while(!S.empty()) {
        int u = S.begin()->second ; 
        S.erase(S.begin()) ;
        for(auto i : g[u]) {
            int v = i.first;
            long long w = i.second ; 
            if(d[v] > d[u] + w) {
                S.erase({d[v], v}) ; 
                d[v] = d[u] + w ; 
                S.insert({d[v], v}) ;
            }
        }
    }

}
