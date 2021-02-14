// Declaration: SegTree<int> S(size, "type") 
// type - "sum" , to find range sum
// type - "max" , to find range max 
// type - "min" , to find range min
// type - "gcd" , to find range gcd 
// type - "lcm" , to find range lcm
// type - "xor" , to find range xor

// Building the Segment Tree - S.build(a), a must be a vector
// Point updates - S.update(index, value) ; 
// Range updates - S.updateRange(starting_pos, ending_pos, value, "type");
// type - "add" , adds value from starting_pos to ending_pos
// type - "set" , sets every element to value from starting_pos to ending_pos
// Query - S.query(starting_pos, ending_pos)  ; 

template <typename T> 
class SegTree {
	int n;
	T CNST ;  
	vector<T> tree, lazyAdd, lazySet;
	vector<bool> isSet; 
	int type;
public :
	
	SegTree(int x, string str) {
		n = x ;
		tree.resize(4*n+5) ;
		lazyAdd.resize(4*n+5) ;
		lazySet.resize(4*n+5) ;
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

	T merge(T a, T b) {
		if(type == 0 ) return a + b ; 
		else if(type == 1 ) return min(a,b) ;
		else if(type == 2 ) return max(a,b) ;
		else if(type == 3 ) return __gcd(a,b) ;
		else if(type == 4 ) return (a * b / __gcd(a,b)) ;
		else return a ^ b ; 
	}

	void _build(int node,int start,int end, vector<T> &arr) {
		if(start == end) {
			tree[node] = arr[start] ;
			return ;
		}
		int mid = (start + end) >> 1;
		_build(2*node, start, mid, arr) ;
		_build(2*node+1, mid+1, end, arr) ;
		tree[node] = merge(tree[2*node], tree[2*node+1]);
	}

	void build(vector<T> &arr) {
		_build(1,1,n,arr) ;
	}

	void _update(int node, int start, int end,int idx, T val) {
		if(start == end) {
			tree[node] = val ;
			return ;
		}
		int mid = (start + end) >> 1 ;
	
		if(start <= idx and idx <= mid) _update(2*node, start, mid, idx, val) ;
		else _update(2*node+1, mid+1, end, idx, val) ;
		tree[node] = merge(tree[2*node], tree[2*node+1]);
	}

	void update(int x, T val) {
		_update(1,1,n,x,val) ;
	}

	void reset(int node) {
		lazySet[node] = 0 ; 
		lazyAdd[node] = 0 ; 
		isSet[node] = 0 ; 
	}

	void compose(int par,int child) {
		if(isSet[par]) {
			lazySet[child] = lazySet[par] ;
			lazyAdd[child] = lazyAdd[par] ;
			isSet[child] = true;  
		}
		else lazyAdd[child] += lazyAdd[par]; 
	}

	void applyAgg(int node,int start, int end) {
		if(isSet[node]) tree[node] = (end-start + 1) * lazySet[node]; 
		tree[node] += (end - start + 1) * lazyAdd[node] ;

		if(start != end ) {
			compose(node, 2*node) ;
			compose(node, 2*node + 1) ;
		}  

		reset(node) ;	
	}

	void _updateRange(int node,int start,int end,int l, int r,T val, int t) {

		if(start > end or start > r or end < l ) return ; 

		if(start >= l and end <= r) {
			if(t == 1) lazyAdd[node] += val; 
			else {
				isSet[node] = 1; 
				lazySet[node] = val ;
				lazyAdd[node] = 0 ;
			}
			return ; 
		}

		applyAgg(node,start,end) ;

		int mid = (start + end) >> 1 ;

		_updateRange(2*node, start, mid, l, r, val, t) ;
		_updateRange(2*node + 1, mid+1, end, l, r, val, t) ;

		applyAgg(2*node,start,mid) ;
		applyAgg(2*node+1,mid+1,end) ;

		tree[node] = merge(tree[2*node], tree[2*node+1]) ;
	}

	void updateRange(int l,int r, T val, string str) {
		int t = (str == "add" ? 1 : 2 ) ;
		_updateRange(1,1,n,l,r,val,t) ;
	}

	T _query(int node, int start,int end,int l, int r) {
		if(r < start or l > end ) return CNST;
		applyAgg(node,start,end) ;
		if(l <= start and end <= r) return tree[node] ;
		int mid = (start + end) >> 1 ;
		return merge(_query(2*node,start, mid, l,r), _query(2*node+1,mid+1,end,l,r));
	}

	T query(int l, int r) {
		return _query(1,1,n,l,r) ;
	}
};
