
struct comb{

    int mxN, M; 
    vector<int> fact, ifact; 

    int mul(int a, int b) { return a * 1ll * b % M ; }

    int power(int a, int n) {
        if(n == 0) return 1 ; 
        int p = power(a, n/2) % M ; 
        p = p * p % M ; 
        return n & 1 ? p * a % M : p ; 
    }

    int invMod(int a) {
        return power(a,M-2) % M ;
    }

    void pre() {
        fact[0] = 1 ;
        for(int i = 1;i< mxN;++i) 
            fact[i] = mul(i, fact[i-1]) ; 

        ifact[mxN-1] = invMod(fact[mxN-1]) ; 
        
        for(int i = mxN-1 ; i>0 ;--i) 
            ifact[i-1] = mul(i, ifact[i]) ;
    }

    comb(int _mxN, int _M) {
        mxN = _mxN ; 
        M = _M ; 
        fact.resize(mxN+5) ; 
        ifact.resize(mxN+5) ;
        pre() ;  
    }


    int nCr(int n, int r) {
        if (n < r || r < 0 || n < 0) return 0;
        int res = mul(ifact[r], ifact[n-r]) ;
        res = mul(res, fact[n]) ;
        return res ;
    }
};
