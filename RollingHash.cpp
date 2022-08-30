struct RollingHash {
    int n;
    int pr, mod;
    vector<int> h, p;
    RollingHash(int pr, int mod, int n) : pr(pr), mod(mod), n(n) {
        h.resize(n + 1);
        p.resize(n + 1);
    }
    int add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
    int sub(int a, int b) {return a >= b ? a - b : a - b + mod;}
    int mul(int a, int b) {return a * 1ll * b % mod;}
    int power(int a, int n) {
        if(n == 0) return 1;
        int p = power(a, n / 2);
        p = mul(p, p);
        return n & 1 ? mul(p, a) : p;
    }
    void init(string &s) {
        int cur = 1;
        p[0] = 1;
        for(int i = 1; i <= n; ++i) {
            h[i] = add(h[i - 1], mul(p[i - 1], s[i - 1] - 'a' + 1));
            p[i] = mul(pr, p[i - 1]);
        }
    }
    int ssHash(int l, int r) {
        return mul(sub(h[r], h[l - 1]), p[n - l + 1]); 
    }
};
