const int N = 2e5 + 1;
int MAXI = 0;
map<ll,ll> mp, rmp;
struct node{
     ll count;
     node *l, *r;
     node(ll a = 0,node* b= 0, node* c= 0){
          count = a, l = b, r = c;
     }
     node* update(ll, ll, ll, ll);
     
};
 
node* nil() {
  node *x = new node();
  x -> r = x -> l = x;
  return x;
}
 
node* node :: update(ll l, ll r, ll idx, ll val){
    
     if(idx < l || idx > r){
          return this;
     }
     if(l == r){
          return new node(val, nil(), nil());
     }
     
     ll m = (l + r) / 2;
     node* left, *right;
     left = this->l ->update(l, m, idx, val);
     right = this->r ->update(m + 1, r, idx, val);
     return new node((left->count) + (right->count), left, right);     
}
ll query(node* a, ll tl, ll tr, ll l, ll r){
    if(tl == l && tr == r){
        return a->count;
    }
    if(l > r){
        return 0;
    }
    ll tm = (tl + tr) / 2;
    ll left, right;
    left = query(a->l, tl, tm, l, min(r, tm));
    right = query(a->r, tm + 1, tr, max(l, tm + 1), r);
    return left + right;
}
node *root[N];
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    fast;
    ll T = 1, i, j;
    
    //cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        map<ll,ll> last;
        for(i =0 ; i < n; i++){
            ll x;
            cin >> x;
            if(!i){
                root[0] = nil();
                root[0] = root[0] -> update(1, n, i + 1, 1);
            }
            else{
                root[i] = root[i - 1] -> update(1, n, i + 1, 1);
                if(last[x] != 0){
                    root[i] = root[i] -> update(1 ,n, last[x], 0);
                }
            }
            last[x] = i + 1;
        }
        ll q;
        
        cin >> q;
        while(q--){
            ll l, r;
            
            cin >> l >> r;
            ll ans = query(root[r - 1], 1, n, l, r);
            cout << ans << endl;
        }        
    }
    return 0;
}