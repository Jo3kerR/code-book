// https://www.spoj.com/files/src/29970922/
// https://www.spoj.com/files/src/29970298/

// Declaration : PST<int> P(size) ; 
// Building the Segment Tree - P.build(a), 
//			a must be a vector and 1-indexed
// Update : P.update(k, index, val), update the value 
//			at index to val in the kth version
// Query : P.query(k, a, b), find the range sum [a,b] 
//			in the kth version
// Create a copy of kth version : P.newVersion(k) 

template<typename T>
struct PST { 
    struct node{
        T val ; 
        node *left, *right ;
        node(node* l, node* r, T v) : left(l), right(r), val(v) {} 
    };
     
    int n;
    node* root;  
    vector<node*> version; // stores the root node of each version
     
    PST(int _n) { 
        n = _n ; 
        root = new node(NULL, NULL, 0); 
        version.push_back(root) ;
    } 

    // 0 based indexing
    node* getVersion(int k) { return version[k]; }

    void newVersion(int k) {
        node* new_node = new node(getVersion(k)->left, getVersion(k)->right, getVersion(k)->val) ; 
        version.push_back(new_node) ; 
    }

    void _build(node* n, int start, int end, vector<T> &a) {
        if(start == end ) {
            n->val = a[start]; 
            return ; 
        }
        int mid = (start+end)/2 ;
        n->left = new node(NULL, NULL, 0); 
        n->right = new node(NULL, NULL, 0); 
        _build(n->left, start, mid, a); 
        _build(n->right, mid+1, end, a); 
        n->val = n->left->val + n->right->val ; 
    }
    
    void _update(node* n, int start, int end, int idx, T v) {
        if(idx > end or idx < start or start > end) return ; 
        if(start == end) {
            n->val = v; 
            return ; 
        }
        int mid = (start + end)/2 ;
        if(idx <= mid) {
            node* new_node = new node(n->left->left, n->left->right, 0); 
            n->left = new_node; 
            _update(n->left, start, mid, idx, v) ;
        }
        else {  
            node* new_node = new node(n->right->left, n->right->right, 0); 
            n->right = new_node; 
            _update(n->right, mid+1, end, idx, v); 
        }
        n->val = n->left->val + n->right->val ; 
    }
    
    T _query(node* n,int start, int end, int l, int r) {
        if(start > end or start > r or end < l) return 0 ; 
        if(start >= l and end <= r) return n->val ; 
        int mid = (start + end) / 2 ;
        return _query(n->left, start, mid, l, r) + _query(n->right, mid+1, end, l, r); 
    }

    void build(vector<T> &a) { _build(root, 1, n, a) ; }
    void update(int k, int idx, T val) { _update(getVersion(k), 1, n, idx, val); } 
    T query(int k, int l, int r) { return _query(getVersion(k), 1, n, l, r) ; }
};
