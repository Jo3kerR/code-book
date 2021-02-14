// update(x, y, val) : adds val to (x, y) 
// to query on the rectangle (x1,y1) (x1, y2) (x2, y1) (x2, y2) 
// x1 <= x2, y1 <= y2 
// query(x2, y2) - query(x1, y2) - query(x2, y1) + query(x1, y1)

const int N = 1e3 + 5;
int n, BIT[N][N];

void update(int x,int y,int val) {
	for(; x <= n ; x += x&-x) {
		int Y = y ; 
		for(; y <= n ; y += y&-y) {
			BIT[x][y] += val ; 
		}
		y = Y ; 
	}
}

int query(int x,int y) {
	int sum = 0 ; 
	for(; x > 0 ; x -= x&-x) {
		int Y = y ; 
		for(; y > 0 ; y -= y&-y) sum += BIT[x][y]; 
		y = Y ; 
	}
	return sum ;
}
