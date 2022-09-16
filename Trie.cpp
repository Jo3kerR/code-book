struct Trie{
    struct node {
        int cnt ;
        node* child[2] ;
        node() {
            cnt = 0 ;
            for(int i = 0 ; i < 2 ; ++i) child[i] = NULL ;
        } 
    }; 
    
    node* root ;
    Trie() {
        root = new node(); 
    }
 
    void add(string &s) {
        node* ex = root ; 
        for(auto i : s) {
            if(root->child[i-'0'] == NULL) {
                root->child[i-'0'] = new node();
            }
            root = root->child[i-'0'] ;
        }
        root -> cnt ++ ; 
        root = ex; 
    }

    int dfs(string &s) {
        conmplete 
    }
    
    void dealloc(node *temp) {
        if(temp == NULL) return ;
        for(int i = 0 ; i < 2; ++i) {
            dealloc(temp -> child[i]) ;
        }
        delete temp ;
    }
};
