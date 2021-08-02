// Remove lazy when not needed

// Declaration: SegTree<int> S(size, "type") 
// type - "sum" , to find range sum
// type - "max" , to find range max 
// type - "min" , to find range min
// type - "gcd" , to find range gcd 
// type - "lcm" , to find range lcm
// type - "xor" , to find range xor

// Building the Segment Tree - S.build(a), a must be a vector and 1-indexed
// Point updates - S.update(index, value) ; 
// Range updates - S.updateRange(starting_pos, ending_pos, value, "type");
// type - "add" , adds value to each element from starting_pos to ending_pos
// type - "set" , sets every element to value from starting_pos to ending_pos
// Query - S.query(starting_pos, ending_pos)  ; 

template <typename T> 
struct SegTree {
    int n, type;
    T CNST ;  
    vector<T> tree, lazy; 
    vector<bool> isSet; 
    SegTree(int x, string str) {
        n = x ;
        tree.resize(4*n+5) ;
        lazy.resize(4*n+5) ;
        isSet.resize(4*n+5) ; 
        if(str == "sum") type = 0 ; 
        else if(str == "min") type = 1 ;
        else if(str == "max") type = 2 ;
        else if(str == "gcd") type = 3 ; 
        else if(str == "lcm") type = 4 ;
        else if(str == "xor") type = 5 ;
        if(type == 0 or type == 3 or type == 5) CNST = 0 ; 
        if(type == 2 ) CNST = numeric_limits<T>::min() ; 
        if(type == 1 ) CNST = numeric_limits<T>::max() ;
        if(type == 4 ) CNST = 1 ; 
    }
    inline T merge(T a, T b) {
        if(type == 0 ) return a + b ; 
        if(type == 1 ) return min(a,b) ;
        if(type == 2 ) return max(a,b) ;
        if(type == 3 ) return __gcd(a,b) ;
        if(type == 4 ) return (a * 1LL * b / __gcd(a,b)) ;
        return a ^ b ; 
    }
    void _build(int v, int s, int e, vector<T> &a) {
        if(s == e) {tree[v] = a[s];return;}
        _build(v<<1, s, s+e>>1, a) ;
        _build(v<<1|1, (s+e>>1)+1, e, a) ;
        tree[v] = merge(tree[v<<1], tree[v<<1|1]);
    }
    void _update(int v, int s, int e,int i, T w) {
        if(s == e) {tree[v] = w; return;}
        if(s <= i and i <= (s+e>>1)) _update(v<<1, s, s+e>>1, i, w) ;
        else _update(v<<1|1, (s+e>>1)+1, e, i, w) ;
        tree[v] = merge(tree[v<<1], tree[v<<1|1]);
    }
    inline void update(int x, T val) {_update(1,1,n,x,val);}
    inline void build(vector<T> &a) {_build(1,1,n,a);}
    inline void push(int v) {
        if(isSet[v]) {
            tree[v<<1] = tree[v<<1|1] = tree[v] ; 
            isSet[v<<1] = isSet[v<<1|1] = true ; 
            isSet[v] = false; lazy[v] = 0 ; 
        }
        else {
            tree[v<<1] += lazy[v], lazy[v<<1] += lazy[v] ; 
            tree[v<<1|1] += lazy[v], lazy[v<<1|1] += lazy[v] ;
            lazy[v] = 0 ; 
        }
    }
    void _updateRange(int v, int s, int e,int l, int r, T w,bool t) {
        if(l > r) return ; 
        if(s == l && e == r) {
            if(t == 0) tree[v] += w, lazy[v] += w; 
            else tree[v] = w, isSet[v] = true ;
        }
        else {
            push(v) ; 
            int m = s+e >> 1  ;
            _updateRange(v<<1, s, m, l, min(r, m), w, t) ; 
            _updateRange(v<<1|1, m+1, e, max(l, m+1), r, w, t); 
            tree[v] = merge(tree[v<<1], tree[v<<1|1]) ; 
        }
    }
    inline void updateRange(int l,int r, T w, string str = "add") {
        bool t = (str == "add" ? 0 : 1) ;
        _updateRange(1,1,n,l,r,w,t) ;
    }
    T _query(int v, int s, int e,int l, int r) {
        if(l > r) return CNST ; 
        if(l <= s && e <= r) return tree[v] ; 
        push(v) ; 
        int m = s+e >> 1;
        return merge(_query(v<<1,s,m,l,min(r,m)),_query(v<<1|1,m+1,e,max(l,m+1),r)) ; 
    }
    inline T query(int l, int r) {return _query(1,1,n,l,r);}
};
