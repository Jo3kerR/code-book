const int N = 1e5 + 5 ; 
int par[N], rnk[N] ; 
 
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
