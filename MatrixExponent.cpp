// Declaration : matrix mat(size) 
// expo_power(a, k, n) : returns [a]^k 

struct matrix {
    int n ; 
    vector<vector<int> > a;
    matrix(int _n) {
        n = _n ; 
        a.resize(n, vector<int>(n)) ; 
    }
    matrix operator * (const matrix& other) {
        matrix p(n);
        for(int i = 0 ; i < n; ++i) 
            for(int j = 0 ; j < n ; ++j) 
                for(int k = 0 ; k < n ; ++k) 
                    p.a[i][k] += a[i][j] * other.a[j][k] ; 
        return p ; 
    }
};

matrix expo_power(matrix a, int k, int n) {
    matrix res(n); 
    for(int i = 0 ; i < n ; ++i) 
        res.a[i][i] = 1 ; 
    while(k) {
        if(k&1) res = res * a ; 
        a = a * a ;
        k >>= 1 ; 
    }
    return res; 
}
