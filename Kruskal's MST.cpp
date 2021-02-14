const int N = 1e5 + 5 ; 
int par[N], rnk[N] ; 
 
struct edge{
    int u, v, w; 
    const bool operator <(const edge &other) const {
        return w < other.w ; 
    }
};
 
int find_set(int a) {
    return (a == par[a] ? a : par[a] = find_set(par[a])) ; 
}
 
void union_set(int a, int b) {
    a = find_set(a) ; 
    b = find_set(b) ; 
    if(a != b) {
        if(rnk[a] < rnk[b]) swap(a, b) ; 
        par[b] = a ; 
        if(rnk[a] == rnk[b]) ++rnk[a] ; 
    }
}

int KruskalMST(vector<edge> &e) {
	sort(e.begin(), e.end()) ; 
	int ans = 0; 
	for(auto i : e) {
		if(find_set(i.u) != find_set(i.v)) {
			ans += i.w ; 
			union_set(i.u, i.v) ; 
		}
	}
	return ans ; 
}
