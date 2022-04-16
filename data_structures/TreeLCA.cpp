struct Treelca{
    int n, k, timer = 0;
    vector<vector<int>> adj;
    vector<int> dp, tin, tout, depth;
    vector<vector<int>> parent;
    void add(int a, int b){
        adj[a].pb(b);
    }
    void dfs(int a, int par){
        assert(a >= 1 && a <= n);
        tin[a] = ++timer;
        dp[a] = 1;
        for(auto u : adj[a]){
            assert(u != par);
            if(u != par){
                assert(u >= 1 && u <= n);
                depth[u] = depth[a] + 1;
                parent[u][0] = a; 
                dfs(u, a);
                dp[a] += dp[u];
            }
        }
        tout[a] = ++timer;
    }
    bool good(int a, int b){
        if(tin[a] <= tin[b] && tout[a] >= tout[b]){
            return true;
        }
        return false;
    }
    int lca(int a, int b){
        if(a == b){
            return a;
        }
        if(good(a, b)){
            return a;
        }
        if(good(b, a)){
            return b;
        }
        for(int i = k - 1; i >= 0; i--){
            if(!good(parent[a][i], b)){
                a = parent[a][i];
            }
        }
        return parent[a][0];
    }
    int go(int a, int dist){
        if(dist == 0){
            return a;
        }
        for(int i = 19; i >= 0; i--){
            if(dist > (1 << i)){
                dist -= (1 << i);
                a = parent[a][i];
            }
        }
        return parent[a][0];
    }
    void build(){
        for(int i = 0; i < k; i++){
            parent[1][i] = 1;
        }
        dfs(1, -1);
        for(int i = 1 ;i < k; i++){
            for(int j = 1; j <= n; j++){
                parent[j][i] = parent[parent[j][i - 1]][i - 1];
            }  
        }
    }
    
    Treelca(int x){
        n = x;
        k = 20;
        adj.resize(n + 1);
        dp.resize(n + 1);
        depth.resize(n + 1);
        tin.resize(n + 1);
        tout.resize(n + 1);
        parent = vector<vector<int>>(n + 1, vector<int>(k));
    }
};