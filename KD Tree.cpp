struct kd_tree {
    int k;
    struct node {
        vector<int> point;
        node *left, *right;
        node(vector<int> _point) {
            for(auto i : _point) {
                point.push_back(i);
            }
            left = right = NULL;
        }
    };
    node *root;
    multiset<pair<long long, vector<int>>> KNN;
    kd_tree(int _k) : k(_k) { root = NULL;}
    void insert(vector<int> _point) {
        if(root == NULL) {
            root = new node(_point);
            return;
        }
        int d = 0;
        node* ptr = root;
        while(1) {
            if(ptr -> point[d] > _point[d]) {
                if(ptr -> left == NULL) {
                    ptr -> left = new node(_point);
                    return;
                }
                ptr = ptr -> left;
            }
            else {
                if(ptr -> right == NULL) {
                    ptr -> right = new node(_point);
                    return;
                }
                ptr = ptr -> right;
            }
            ++ d;
            d %= k;
        }
    }
    long long get_distance(vector<int> &a, vector<int> &b) {
        long long ans = 0;
        for(int i = 0; i < k; ++i) ans += (a[i] - b[i]) * (a[i] - b[i]);
        return ans;
    }
    void print(vector<int> &a) {
        cout << "(";
        for(int i = 0; i < k; ++i) {
            cout << a[i];
            if(i < k - 1) cout << ", ";
        }
        cout << ")";
    }
    void find_KNN(vector<int> &_point, node* ptr, int K, int d = 0) {
        if(ptr == NULL) return;
        d %= k;
        if((int)KNN.size() < K) KNN.insert({get_distance(ptr -> point, _point), ptr -> point});
        else if(get_distance(ptr -> point, _point) < KNN.rbegin() -> first) {
            KNN.erase(prev(KNN.end()));
            KNN.insert({get_distance(ptr -> point, _point), ptr -> point});
        }
        int dir = -1;
        if(ptr -> point[d] > _point[d]) {
            find_KNN(_point, ptr -> left, K, d + 1);
            dir = 0;
        }
        else {
            find_KNN(_point, ptr -> right, K, d + 1);
            dir = 1;
        }
        if((int)KNN.size() < K || abs(ptr -> point[d] - _point[d]) * abs(ptr -> point[d] - _point[d]) <= KNN.rbegin() -> first) {
            if(dir) find_KNN(_point, ptr -> left, K, d + 1);
            else find_KNN(_point, ptr -> right, K, d + 1);
        }
    }
    vector<vector<int>> get_KNN(vector<int> _point, int K) {
        find_KNN(_point, root, K);
        vector<vector<int>> ans;
        for(auto i : KNN) ans.push_back(i.second);
        return ans;
    }
};
