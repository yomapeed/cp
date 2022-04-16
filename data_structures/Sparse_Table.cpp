struct SparseTable{
    struct node{
        
        void apply(ll val, ll idx){
            
        }
    };
    node unite(node &a, node &b){
        node res;
        
        return res;
    }
    int n, b;
    vector<ll> v;
    vector<int> logy;
    vector<vector<node>> t;
    void build(){
        for(int i = 0; i < n; i++){
            t[i][0].apply(v[i], i); 
        }
        for(int i = 2; i <= n; i++){
            logy[i] = 1 + logy[i >> 1];
        }
        for(int i = 1; i < b; i++){
            for(int j = 0; j + (1 << i) <= n; j++){
                t[j][i] = unite(t[j][i - 1], t[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    node query(int l, int r){
        if(l > r){
            node res;
            
            return res;
        }
        int len = (r - l + 1);
        int lg = logy[len];
        return unite(t[l][lg], t[r - (1 << lg) + 1][lg]);
    }
    SparseTable(int _n, const vector<ll> &vt){
        n = _n;
        v = vt;
        int lg = 1;
        int cnt = 1;
        while(lg <= n){
            lg *= 2;
            cnt++;
        }
        logy.resize(_n + 1);
        b = cnt;
        t = vector<vector<node>>(n, vector<node>(b));
        build();
    }   
};