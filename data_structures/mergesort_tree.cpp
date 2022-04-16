struct SegTree {
    struct node {
        vector<int> t;
        void apply(int l, int r, ll x = 0) {
            t = vector<int>(1, x);
        }
    };
    void unite(const node &a, const node &b, node &res) {
        merge(a.t.begin(), a.t.end(), b.t.begin(), b.t.end(), back_inserter(res.t));
    }
    inline void pull(int a, int b) { unite(tree[a + 1], tree[b], tree[a]); }
    inline void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        // if(tree[x].val != -1){
        //     tree[x + 1].apply(l, y, tree[x].val);
        //     tree[z].apply(y + 1, r, tree[x].val);
        //     tree[x].val = -1;
        // }
    }

    vector<node> tree;
    vector<ll> vx;
    int n;

    void build(int x, int l, int r) {
        if (l == r) {
            tree[x].apply(l, r, vx[l]);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pull(x, z);
    }
    ll get(int x, int l, int r, int llx, int rrx, ll val) {
        if (llx <= l && r <= rrx) {
            //return tree[x];
            auto it = lower_bound(tree[x].t.begin(), tree[x].t.end(), val);
            if(it == tree[x].t.begin()){
                return 0;
            }
            it--;
            
            return *it;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        // push(x, l, r);
        ll res = 0;
        if (rrx <= y) {
            res = get(x + 1, l, y, llx, rrx, val);
        } else {
            if (llx > y) {
                res = get(z, y + 1, r, llx, rrx, val);
            } else {
                res = max(get(x + 1, l, y, llx, rrx, val), get(z, y + 1, r, llx, rrx, val));
            }
        }
        // pull(x, z);
        return res;
    }
    template <typename... M>
	void modify(int x, int l, int r, int llx, int rrx, const M &... v) {
        if (llx <= l && r <= rrx) {
            tree[x].apply(l, r, v...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (llx <= y) {
            modify(x + 1, l, y, llx, rrx, v...);
        }
        if (rrx > y) {
            modify(z, y + 1, r, llx, rrx, v...);
        }
        pull(x, z);
    }
    bool f(node& x){
        return true;
    }
    int find_first_knowingly(int x, int l, int r) {
        if (l == r) {
            return l;
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[x + 1])) {
            res = find_first_knowingly(x + 1, l, y);
        } else {
            res = find_first_knowingly(z, y + 1, r);
        }
        pull(x, z);
        return res;
    }

    int find_first(int x, int l, int r, int llx, int rrx) {
        if (llx <= l && r <= rrx) {
            if (!f(tree[x])) {
                return -1;
            }
            return find_first_knowingly(x, l, r);
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res = -1;
        if (llx <= y) {
            res = find_first(x + 1, l, y, llx, rrx);
        }
        if (rrx > y && res == -1) {
            res = find_first(z, y + 1, r, llx, rrx);
        }
        pull(x, z);
        return res;
    }

    
    ll get(int llx, int rrx, ll val) {
        assert(0 <= llx && llx <= rrx && rrx <= n - 1);
        return get(0, 0, n - 1, llx, rrx, val);
    }
    
    int find_first(int llx, int rrx) {
        assert(0 <= llx && llx <= rrx && rrx <= n - 1);
        return find_first(0, 0, n - 1, llx, rrx);
    }
    template <typename... M> 
	void modify(int llx, int rrx, const M &... v) {
        assert(0 <= llx && llx <= rrx && rrx <= n - 1);
        modify(0, 0, n - 1, llx, rrx, v...);
    }
    template <typename M = ll> 
	SegTree(int _n, vector<M> v = {}) : n(_n) {
        tree.resize(2 * n - 1);
        vx = v;
        if(vx.empty()){
            vx.resize(n);
        }
        build(0, 0, n - 1);
    }
};