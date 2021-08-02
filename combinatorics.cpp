struct nCr{
    int mxN, M; 
    vector<int> fact, ifact; 
    inline int mul(int a, int b) {return a *1LL* b % M ;}
    int power(int a, int n) {
        if(n == 0) return 1 ; 
        int p = power(a, n/2) % M ; 
        p = mul(p, p) ;  
        return n & 1 ? mul(p, a) : p ; 
    }
    int invMod(int a) {return power(a,M-2);}
    void pre() {
        fact[0] = 1 ;
        for(int i = 1;i< mxN;++i) fact[i] = mul(i, fact[i-1]) ;
        ifact[mxN-1] = invMod(fact[mxN-1]) ; 
        for(int i = mxN-1 ; i>0 ;--i) ifact[i-1] = mul(ifact[i], i) ;
    }
    nCr(int _mxN, int _M) {
        mxN = _mxN + 1; 
        M = _M ; 
        fact.resize(mxN) ; 
        ifact.resize(mxN) ;
        pre() ;  
    }
    int C(int n, int r) {
        if (n < r || r < 0 || n < 0) return 0;
        return mul(fact[n], mul(ifact[r], ifact[n-r])) ;
    }
};
