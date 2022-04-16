struct SegTree {
    struct node {
        ll mx = 0, lazy = 0;
        void apply(int l, int r, ll x = 0) {
            mx += x;
            lazy += x;
        }
    };
    node unite(const node &a, const node &b) const {
        node res;
        res.mx = max(a.mx, b.mx);
		return res;
    }
    inline void pull(int a, int b) { tree[a] = unite(tree[a + 1], tree[b]); }
    inline void push(int x, int l, int r) {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        if(tree[x].lazy){
            tree[x + 1].apply(l, y, tree[x].lazy);
            tree[z].apply(y + 1, r, tree[x].lazy);
            tree[x].lazy = 0;
        }
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
    node get(int x, int l, int r, int llx, int rrx) {
        if (llx <= l && r <= rrx) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        node res{};
        if (rrx <= y) {
            res = get(x + 1, l, y, llx, rrx);
        } else {
            if (llx > y) {
                res = get(z, y + 1, r, llx, rrx);
            } else {
                res = unite(get(x + 1, l, y, llx, rrx), get(z, y + 1, r, llx, rrx));
            }
        }
        pull(x, z);
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
    ll query_val;
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
    int find_last_knowingly(int x, int l, int r) {
        if (l == r) {
            return l;
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[z])) {
            res = find_last_knowingly(z, y + 1, r);
        } else {
            res = find_last_knowingly(x + 1, l, y);
        }
        pull(x, z);
        return res;
    }

    int find_last(int x, int l, int r, int llx, int rrx) {
        if (llx <= l && r <= rrx) {
            if (!f(tree[x])) {
                return -1;
            }
            return find_last_knowingly(x, l, r);
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res = -1;
        if (rrx > y) {
            res = find_last(z, y + 1, r, llx, rrx);
        }
        if (llx <= y && res == -1) {
            res = find_last(x + 1, l, y, llx, rrx);
        }
        
        pull(x, z);
        return res;
    }
    
    node get(int llx, int rrx) {
        assert(0 <= llx && llx <= rrx && rrx <= n - 1);
        return get(0, 0, n - 1, llx, rrx);
    }
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(0, 0, n - 1, p, p);
    }
    int find_first(int llx, int rrx) {
        assert(0 <= llx && llx <= rrx && rrx <= n - 1);
        return find_first(0, 0, n - 1, llx, rrx);
    }
    int find_last(int llx, int rrx) {
        assert(0 <= llx && llx <= rrx && rrx <= n - 1);
        return find_last(0, 0, n - 1, llx, rrx);
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