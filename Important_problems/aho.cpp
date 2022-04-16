
const int N = 2e5 + 1, alp =128;
struct aho{
     
    vector<ll> sl, de, ol;
    ll sz = 0;
    vector<vector<ll>> To;
    aho(ll n){
        sz = 0;
        sl = vector<ll>(n);
        de = vector<ll>(n);
        ol = vector<ll>(n );
        To = vector<vector<ll>>(n, vector<ll>(alp));
    }
    void add(string& s){
        ll u = 0;
        for(char  c: s){
            
            if(To[u][c]){
 
            }
            else{
                To[u][c] = ++sz;
            }
            u = To[u][c];
        }
        ol[u] = u;
 

    }
    void aho_corasick(){
        queue<ll> q;
        q.push(0);
        while(!q.empty()){
            ll v = q.front(); q.pop();
            ll u = sl[v];
            for(int i = 0; i < alp; i++){
                if(To[v][i]){
                    ll x = To[v][i];
                    de[x] = de[v] + 1;
                    sl[x] = v ? To[sl[v]][i] : 0;
                    if(!ol[x]){
                        ol[x] = ol[sl[x]];
                    }
                    q.push(x);
                }
                else{
                    To[v][i] = To[u][i];
                }
            }
        }
    }
};
