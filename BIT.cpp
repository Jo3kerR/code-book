// Finds only range sum but can be modified 
// Declaration : BIT<int> B(size) ; 
// Update : B.update(index, value), adds value to index 
// Query : B.query(starting_pos, ending_pos), returns sum from 
// 	   starting_pos to ending_pos

template <typename T> 
struct BIT {
	int n; 
	vector<T> bit;
	
	BIT(int x) {
		n = x; 
		bit.resize(n+5) ;
	}

	void update(int x, T val) {
 	     for(; x <= n; x += x&-x)
        	bit[x] += val;
	}

	T _query(int x) {
    		T sum = 0;
     		for(; x > 0; x -= x&-x)
       			sum += bit[x];
    		return sum;
	}

	T query(int l,int r) {
		return _query(r) - _query(l-1) ;
	}
};
