#include<bits/stdc++.h>
#define pi 3.141592653589793238
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define MOD 1000000007
#define INF 999999999999999999 
#define pb push_back
#define ff first
#define ss second
 
#define mt make_tuple
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
 
 
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int N = 1e6 + 1;
ll pos[N];
ll nxt[N][20];
ll go(ll idx, ll k){

    for(int i = 20; i >= 0; i--){
        if(k > (1 << i)){
            idx = nxt[idx][i];
            k -= (1 << i);
        }
    }
    idx = nxt[idx][0];
    return idx;
}
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    fast;
    ll T = 1, i, j;

    //cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        vector<ll> v(n);
        for(i = 0; i < n; i++){
            cin >> v[i];
        }
        for(i = 1; i < N; i++){
            pos[i] = n;
        }
        for(i = 0; i < 20 ;i++){
            nxt[n][i] = n;
        }
        for(i = n - 1; i >= 0; i--){
            if(i == n - 1){
                nxt[i][0] = n;
            }
            else{
                nxt[i][0] = min(nxt[i + 1][0], pos[v[i]]);
            }
            pos[v[i]] = i;
        }
        
        for(i = 1; i < 20; i++){
            for(j = 0; j < n; j++){
                nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
            }
        }
        ll q;
        cin >> q;
        while(q--){
            ll l, r;
            cin >> l >> r;
            l--, r--;
            ll ans = -1;
            ll lo = 1, hi = r - l + 1;
            while(lo <= hi){
                ll mid = (lo + hi) / 2;
                ll x = go(l, mid);
                //cout << mid << " " << x << endl;
                if(x > r){
                    hi = mid - 1;
                    ans = mid;
                }
                else{
                    lo = mid + 1;
                }
            }   
            cout << ans << "\n";
        }
    }
    return 0;
}
/*
10
5 1 5 5 4 1 4 4 2 4 
1
1 10
*/
