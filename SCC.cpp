// Declaration : SCC s(size) ; 
// s.scc() : returns the number of connected components
// the component numbers are stored in s.comp[] 

struct SCC{
    int n;
    vector<vector<int>> g, gr; 
    vector<int> order, comp ; 
    vector<bool> vis; 
    SCC(int _n) {
        n = _n ; 
        g.resize(n+5) ; gr.resize(n+5) ; 
        comp = vector<int>(n+5, -1); vis.resize(n+5) ; 
    }
    void addEdge(int u, int v) {
        g[u].push_back(v) ; 
        gr[v].push_back(u) ; 
    }
    void dfs1(int node) {
        vis[node] = 1 ;
        for(auto i : g[node]) if(!vis[i]) dfs1(i) ; 
        order.push_back(node) ;  
    }
    void dfs2(int node, int c) {
        comp[node] = c ;
        for(auto i : gr[node]) if(comp[i] == -1) dfs2(i, c) ; 
    }
    int scc() {
        for(int i = 1 ; i <= n ; ++i) if(!vis[i]) dfs1(i) ; 
        int cnt = 1 ; 
        for(int i = 0 ; i < n ; ++i) {
            int v = order[n-i-1] ; 
            if(comp[v] == -1) dfs2(v, cnt++) ; 
        }
        return cnt-1;    
    }
};
