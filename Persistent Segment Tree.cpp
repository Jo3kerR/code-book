// Declaration : node* root = new node(NULL, NULL, 0) ;
 
struct node{
	int val ; 
	node *left, *right ;
	node(node* l, node* r, int v) : left(l), right(r), val(v) {} 
};
 
const int N = 2e5 + 5; 
int a[N]; 
vector<node*> version; // stores the root node of each version
 
void build(node* n, int start, int end) {
	if(start == end ) {
		n->val = a[start]; 
		return ; 
	}
	int mid = (start+end)/2 ;
	n->left = new node(NULL, NULL, 0); 
	n->right = new node(NULL, NULL, 0); 
	build(n->left, start, mid); 
	build(n->right, mid+1, end); 
	n->val = n->left->val + n->right->val ; 
}
 
void update(node* n, int start, int end, int idx, int v) {
	if(idx > end or idx < start or start > end) return ; 
	if(start == end) {
		n->val = v; 
		return ; 
	}
	int mid = (start + end)/2 ;
	if(idx <= mid) {
		node* new_node = new node(n->left->left, n->left->right, 0); 
		n->left = new_node; 
		update(n->left, start, mid, idx, v) ;
	}
	else {	
		node* new_node = new node(n->right->left, n->right->right, 0); 
		n->right = new_node; 
		update(n->right, mid+1, end, idx, v); 
	}
	n->val = n->left->val + n->right->val ; 
}
 
int query(node* n,int start, int end, int l, int r) {
	if(start > end or start > r or end < l) return 0 ; 
	if(start >= l and end <= r) return n->val ; 
	int mid = (start + end) / 2 ;
	return query(n->left, start, mid, l, r) + query(n->right, mid+1, end, l, r); 
}
 
