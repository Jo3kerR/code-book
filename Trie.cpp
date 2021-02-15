struct Trie{
	struct node {
		int cnt = 0 ;
		node* child[26] ; 
	};
 
	node* getNewNode() {
		node* t = new node() ;
		for(int i = 0 ; i < 26 ; ++i) t->child[i] = NULL ; 
		return t; 
	}
 
	node* root ; 
 
	void add(string &s) {
		node* ex = root ; 
		for(auto i : s) {
			if(root->child[i-'a'] == NULL) {
				root->child[i-'a'] = getNewNode() ;
			}
			root->cnt ++ ; 
			root = root->child[i-'a'] ;
		}
		root = ex; 
	}

	void dfs(node* r) {
		complete the function
	}
};
