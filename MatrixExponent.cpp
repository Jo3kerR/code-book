// usage : matrix mat(size) 
// matrix res = mat.expo_power(mat, k)  [res] = [mat] ^ k 

const int mod = 1e9 + 7 ; 

struct matrix {
    int n ; 
    vector<vector<int> > a;
    matrix(int _n) {
        n = _n ; 
        a.resize(n, vector<int>(n)) ; 
    }
    int add(int x, int y) { return (x + y > mod ? x + y - mod : x + y); }
    int mul(int x, int y) { return (long long) x * y % mod; }
    
    matrix operator * (const matrix& other) {
        matrix p(n);
        for(int i = 0 ; i < n; ++i) 
            for(int j = 0 ; j < n ; ++j) 
                for(int k = 0 ; k < n ; ++k) 
                    p.a[i][k] = add(p.a[i][k], mul(a[i][j], other.a[j][k])) ; 
        return p ; 
    }

    matrix expo_power(matrix a, long long k) {
        matrix res(n); 
        for(int i = 0 ; i < n ; ++i) 
            res.a[i][i] = 1 ; // unit matrix
        while(k) {
            if(k&1) res = res * a ; 
            a = a * a ;
            k >>= 1 ; 
        }
        return res; 
    }
};
