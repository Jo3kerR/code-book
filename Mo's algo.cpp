const int BLOCK_SIZE = 300;

struct Query {
    int l, r, idx;
    bool operator<(Query &other) const {
        if (l / BLOCK_SIZE != other.l / BLOCK_SIZE) return make_pair(l, r) < make_pair(other.l, other.r);
        return (l / BLOCK_SIZE & 1) ? (r < other.r) : (r > other.r);
    }
};

void remove(int idx) {

}

void add(int idx) {

}

int get_answer() {

}  

vector<int> mo_s_algorithm(vector<Query> &queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}
