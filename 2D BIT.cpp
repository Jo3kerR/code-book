template<typename T>
struct BIT_2D {

    int X, Y; 
    vector<vector<T>> bit ; 

    BIT_2D(int _X, int _Y) {
        X = _X + 5 ;
        Y = _Y + 5 ;  
        bit.resize(X, vector<int>(Y)) ; 
    }

    void update(int x,int y, T val) {
        for(int i = x ; i <= X ; i += i&-i) {
            for(int j = y ; j <= Y ; j += j&-j) {
                bit[i][j] += val ; 
            }
        }
    }

    T _query(int x,int y) {
        T sum = 0 ; 
        for(int i = x ; i > 0 ; i -= i&-i) {
            for(int j = y ; j > 0 ; j -= j&-j) 
                sum += bit[i][j]; 
        }
        return sum ;
    }

    T query(int x1, int y1, int x2, int y2) {
        return _query(x2, y2) - _query(x1-1, y2) -
            _query(x2, y1-1) + _query(x1-1, y1-1) ; 
    }
};
