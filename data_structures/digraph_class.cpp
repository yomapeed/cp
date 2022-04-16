
/*
    Credits: BForBruteForce, Jadavpur University
*/

/*    
    Directed Graph 
*/

template <typename T>
class graph {
    public:
    struct edge {
        int from;
        int to;
        T cost;
    };

    vector<edge> edges;
    vector<vector<int>> g;
    int n;

    graph(int _n) : n(_n) {
        g.resize(n);
    }

    virtual int add(int from, int to, T cost) = 0;
};

template<typename T>
class digraph : public graph<T>{
    public:
    using graph<T> :: edges;
    using graph<T> :: g;
    using graph<T> :: n;
    
    digraph(int _n) : graph<T>(_n) {
    }
    int add(int from, int to, T cost = 1){
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        g[from].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
    
    digraph<T> reverse() const {
        digraph<T> rev(n);
        for (auto &e : edges) {
            rev.add(e.to, e.from, e.cost);
        }
        return rev;
    }
    
    
    
    vector<int> topoSort(){
        vector<int> toposort;
        vector<bool> visited(n);
        function<void(int)> topoHelp = [&](int a){
            visited[a] = true;
            for(int id : g[a]){
                auto &e = g.edges[id];
                int u = e.to;
                if(!visited[u]){
                    topoHelp(u);
                }
            }
            toposort.pb(a);
        };
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                topoHelp(i);
            }
        }
        reverse(toposort.begin(), toposort.end());
        return toposort;
    }

    vector<int> find_scc(int &cnt) {
        digraph<T> g_rev = this -> reverse();
        vector<int> order;
        vector<bool> was(n, false);
        function<void(int)> dfs1 = [&](int v) {
            was[v] = true;
            for (int id : g[v]) {
                auto &e = edges[id];
                int to = e.to;
                if (!was[to]) {
                    dfs1(to);
                }
            }
            order.push_back(v);
        };
        for (int i = 0; i < n; i++) {
            if (!was[i]) {
                dfs1(i);
            }
        }
        vector<int> c(n, -1);
        function<void(int)> dfs2 = [&](int v) {
            for (int id : g_rev.g[v]) {
                auto &e = g_rev.edges[id];
                int to = e.to;
                if (c[to] == -1) {
                    c[to] = c[v];
                    dfs2(to);
                }
            }
        };
        cnt = 0;
        for (int id = n - 1; id >= 0; id--) {
            int i = order[id];
            if (c[i] != -1) {
                continue;
            }
            c[i] = cnt++;
            dfs2(i);
        }
        return c;
    }
    digraph<T> compressSCC(){
        int cc = 0;
        
        vector<int> comp = this -> find_scc(cc);
        digraph<T> res(cc);
        map<pair<int,int>, bool> done;
        for(auto &e : edges){
            if(comp[e.to] == comp[e.from]){
                continue;
            }
            int x, y;
            y = comp[e.to];
            x = comp[e.from];
            if(done[{x, y}]){
                continue;
            }
            done[{x, y}] = 1;
            res.add(x, y);
        }
        return res;
    }
};
