struct DSU{  
        int n;
        vector<int> par, rnk ;
        
        DSU(int _n) {
            n = _n ; 
            par.resize(n + 5) ; 
            rnk.resize(n + 5) ;
            for(int i = 1 ; i <= n ; ++i) par[i] = i ; 
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
