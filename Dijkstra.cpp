const int mxN = 2e5 + 5; 
int d[mxN] ; 

int dijkstra(int s, int t, int n) {

    for(int i = 1 ; i <= n ; ++i) d[i] = numeric_limits<int>::max() ;
    priority_queue<pair<int,int>> pq ; 
    d[s] = 0 ; 
    pq.push({0, s}) ; 

    while(!pq.empty()) {
        int u = pq.top().second ; 
        pq.pop() ;

        for(auto i : g[u]) {
            int v = i.first, w = i.second ; 
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w ; 
                pq.push({-d[v], v}) ; 
            }
        }
    } 
    
    return d[t] ; 
}
