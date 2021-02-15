#include<bits/stdc++.h>
using namespace std ;

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

signed main() {

    ios::sync_with_stdio(0) ; 
    cin.tie(0) ; 

    DSU d(10) ;     

    return 0 ; 

}
