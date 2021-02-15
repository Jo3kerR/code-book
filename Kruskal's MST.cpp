struct KRUSKAL{
    int n ;
    KRUSKAL(int _n) : n(_n) {}  
    struct edge{
        int u, v, w;
        edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}  
        const bool operator <(const edge &other) const {
            return w < other.w ; 
        }
    };
    vector<edge> e ; 
    struct DSU{  
        int n;
        vector<int> par, rnk ;
        
        DSU(int _n) {
            n = _n ; 
            par.resize(n) ; 
            rnk.resize(n) ; 
        }
         
        int find_set(int a) {
            return (a == par[a] ? a : par[a] = find_set(par[a])) ; 
        }
         
        void union_set(int a, int b) {
            a = find_set(a) ; 
            b = find_set(b) ; 
            if(a != b) {
                if(rnk[a] < rnk[b]) swap(a, b) ; 
                par[b] = a ; 
                if(rnk[a] == rnk[b]) ++rnk[a] ; 
            }
        }
    };

    void addEdge(int u, int v, int w) {
        e.push_back({u, v, w}) ; 
    }

    int MST() {
        sort(e.begin(), e.end()) ; 
        int ans = 0; 
        DSU D(n+5) ;
        for(auto i : e) {
            if(D.find_set(i.u) != D.find_set(i.v)) {
                ans += i.w ; 
                D.union_set(i.u, i.v) ; 
            }
        }
        return ans ; 
    }
};
