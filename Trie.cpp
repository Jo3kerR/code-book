struct Trie{
    struct node {
        int cnt = 0 ;
        node* child[2] ; 
    }; 
    node* getNewNode() {
        node* t = new node() ;
        for(int i = 0 ; i < 2 ; ++i) t->child[i] = NULL ; 
        return t; 
    }
    
    node* root ;
    Trie() {
        root = getNewNode(); 
    }
 
    void add(string &s) {
        node* ex = root ; 
        for(auto i : s) {
            if(root->child[i-'('] == NULL) {
                root->child[i-'('] = getNewNode() ;
            }
            root = root->child[i-'('] ;
        }
        root -> cnt ++ ; 
        root = ex; 
    }

    int dfs(string &s) {
        complete the function 
    }
};
