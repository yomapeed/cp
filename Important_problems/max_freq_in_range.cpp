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
const int block = 700;
const int N = 3e5 + 1;
ll freq[N], counter[N];
bool compare(tuple<ll,ll,ll> a, tuple<ll,ll,ll> b){
    ll l1 = get<0>(a);
    ll r1 = get<1>(a);
    ll l2 = get<0>(b);
    ll r2 = get<1>(b);
    if(l1 / block < l2 / block){
        return true;
    }
    if(l1 / block > l2 / block){
        return false;
    }
    ll v1, v2;
    v1 = l1 / block;
    return (v1 & 1) ? (r2 < r1) : (r1 < r2);
}


int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    fast;
    ll T = 1, i, j;
    
    //cin >> T;
    while (T--) {
        ll n, mm, q;
        cin >> n >> mm;
        
        vector<ll> v(n);
        for(i = 0; i < n; i++){
            cin >> v[i];
        }
        
        cin >> q;
        vector<tuple<ll,ll,ll>> queries(q);
        for(i = 0; i < q; i++){
            ll l, r;
            cin >> l >> r;
            queries[i] = {l - 1, r - 1, i};
        }
        sort(queries.begin(), queries.end(), compare);
        vector<ll> ans(q);
        ll tans = 0;
        counter[0] = n;
        ll curl = 0, curr = -1;
        ll ansq = 0;
        for(auto u : queries){
            ll l, r, idx;
            tie(l, r, idx) = u;
            while(curl > l){
                curl--;
                ll c = freq[v[curl]];
                counter[c]--;
                freq[v[curl]]++;
                counter[freq[v[curl]]]++;
                tans = max(tans, freq[v[curl]]);     
            }
            while(curr < r){
                curr++;
                ll c = freq[v[curr]];
                counter[c]--;
                freq[v[curr]]++;
                counter[freq[v[curr]]]++;
                tans = max(tans, freq[v[curr]]);
            }
            while(curl < l){
                ll c = freq[v[curl]];
                counter[c]--;
                freq[v[curl]]--;
                counter[freq[v[curl]]]++;
                curl++;
                while(counter[tans] == 0){
                    tans--;
                }
            }
            while(curr > r){
                ll c = freq[v[curr]];
                counter[c]--;
                freq[v[curr]]--;
                counter[freq[v[curr]]]++;
                curr--;
                while(counter[tans] == 0){
                    tans--;
                }
            }
            ll len = (r - l + 1);
            ll maxi = tans;
            // if(maxi <= (len + 1) / 2){
            //     ans[idx] = 1;
            //     continue;
            // }
            // ll left = len - maxi;
            // ll need = maxi - 1;
            // ans[idx] = 1 + (len - left - left - 1);
            if(maxi * 3 >= 2 * len){
                ans [idx] = 1;
            }
            else if(maxi * 3 < len){
                ans[idx] = 0;
            }
            else{
                counter[tans]--;
                ll tt = tans;
                while(counter[tt] == 0 && tt * 3 >= len){
                    tt--;
                }
                if(tt * 3 >= len){
                    ans[idx] = 1;
                }
                counter[tans]++;
            }
        }
        for(i = 0; i < q; i++){
            if(ans[i]){
                cout << "YES\n";
            }
            else{
                cout << "NO\n";
            }
        }
    }
    return 0;
} 