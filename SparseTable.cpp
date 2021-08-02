// Usage : 
// SparseTable<int> S(size, "type", array) 
// array should be 0-indexed 
// S.query(L, R) : returns the query for [L, R]

template <typename T> 
struct SparseTable {
    int n, type, K; 
    vector<vector<T>> st ;
    vector<int> lg ;  
    SparseTable(int _n, string str, vector<T> &a) {
        n = _n ;
        K = 25 ; 
        if(str == "sum") type = 0 ; 
        else if(str == "min") type = 1 ;
        else if(str == "max") type = 2 ;
        else if(str == "gcd") type = 3 ;
        st.resize(n+1, vector<T>(K+1)) ; 
        lg.resize(n+1) ;
        for(int i = 0 ; i < n ; ++i) st[i][0] = a[i] ; 
        for(int j = 1 ; j <= K ; ++j) {
            for(int i = 0 ; i + (1<<j) <= n ; ++i) {
                st[i][j] = merge(st[i][j-1], st[i+(1<<(j-1))][j-1]) ; 
            }
        }
        lg[0] = 1 ;
        for(int i = 2 ; i <= n ; ++i) lg[i] = lg[i/2] + 1 ; 
    }
    inline T merge(T a, T b) {
        if(type == 0 ) return a + b ; 
        if(type == 1 ) return min(a,b) ;
        if(type == 2 ) return max(a,b) ;
        return __gcd(a,b) ;
    }
    T query(int l, int r) {
        if(type) {
            int j = lg[r-l+1] ; 
            return merge(st[l][j], st[r-(1<<j)+1][j]) ; 
        }
        T ans = 0 ; 
        for(int j = K ; j >= 0 ; --j) {
            if((1 << j) <= r - l + 1) {
                ans += st[l][j] ; 
                l += 1 << j ; 
            }
        }
        return ans ; 
    }
};
