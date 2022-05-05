// add a,a + d,a + 2d,...,a + (j - i)d over range [i,j] 
// https://codeforces.com/contest/1661/submission/153189277

struct Node {
	int sum, A, D;
	Node() {
		sum = A = D = 0;
	}
	void reset() {
		A = D = 0;
	}
};
const int N = 2e5 + 5 ;
Node tree[4*N];
int a[N], n, q;
void build(int node = 1 , int start = 1, int end = n) {
	if(start == end) {
		tree[node].sum = a[start] ; 
		return ; 
	}
	int mid = (start + end) / 2 ;
	build(2*node, start, mid) ;
	build(2*node + 1, mid+1, end) ;
	tree[node].sum = tree[2*node].sum + tree[2*node+1].sum ;
}
void prop(int node,int start, int end) {
	int mid = (start + end) / 2; 
	if(tree[node].A) {
		int s = (end-start+1) ;
		tree[node].sum += s * (2 * tree[node].A + (s-1) * tree[node].D)/2 ;
		if(start != end) {
			tree[2*node].A += tree[node].A;
			tree[2*node+1].A += tree[node].A + (mid+1-start) * tree[node].D ; 
			tree[2*node].D += tree[node].D;
			tree[2*node+1].D += tree[node].D ; 
		}
		tree[node].reset() ;
	}
}

void update(int l, int r, int node, int start, int end, int first_term, int cmn_diff) {
    prop(node,start,end) ;
    if(start > end or start > r or end < l) return ;  
    int mid = (start + end) / 2; 
    if(start >= l and end <= r) {
        int s = (end - start + 1) ; 
        tree[node].sum += s * (2 * (first_term + (start-l) * cmn_diff) + (s-1)) / 2 ;
        if(start != end ) {
            tree[2*node].A += (first_term + (start-l) * cmn_diff);
            tree[2*node].D += cmn_diff ; 
            tree[2*node+1].A += (first_term + (mid + 1-l) * cmn_diff); 
            tree[2*node+1].D += cmn_diff ; 
        }
        return ; 
    }
    update(l,r,2*node,start,mid, first_term, cmn_diff);
    update(l,r,2*node+1,mid+1,end, first_term, cmn_diff); 
    tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
}
 
int query(int l,int r,int node=1,int start=1, int end=n) {
	prop(node,start,end) ;
	if(start > end or start > r or end < l) return 0 ;
	if(start >= l and end <= r ) return tree[node].sum ;
	int mid = (start + end)/2 ;
	return query(l,r,2*node,start,mid) + query(l,r,2*node+1,mid+1,end); 
}
