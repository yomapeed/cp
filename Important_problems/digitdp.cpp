#include<bits/stdc++.h>
#define pi 3.141592653589793238
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define MOD 1000000007
#define INF 999999999999999999 
#define pb push_back
#define ff first
#define ss second
 
#define mt make_tuple
#define printclock cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n";
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
 
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll B) { return (unsigned ll)rng() % B;}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ll dp[20][16][210][2][3][2], mod, msk;
vector<int> dig; 
vector<int> getDig(ll n){
    vector<int> v;
    while(n){
        v.pb(n % 10);
        n /= 10;
    }
    return v;
}
ll f(ll idx, ll mask, ll smod, int tight, int good, int z){
    if(idx == -1){
        // cout << smod << " $ " << mask << " " << msk << endl;
        if(good > 1 && z){
            return 1;
        }
        if(good > 1 && smod == 0 && ((mask & msk) == msk)){
            return 1;
        } 
        return 0;
    }
    if(dp[idx][mask][smod][tight][good][z] != -1){
        return dp[idx][mask][smod][tight][good][z];
    }
    ll res = 0;
    int k = (tight) ? dig[idx] : 9;
    for(int i = 0; i <= k; i++){
        int newTight = (dig[idx] == i) ? tight : 0;
        ll cmask = mask;
        if(i % 2 == 0 && i){
            cmask |= 1;
        }
        if(i % 3 == 0 && i){
            cmask |= 2;
        }
        if(i % 5 == 0 && i){
            cmask |= 4;
        }
        if(i % 7 == 0 && i){
            cmask |= 8;
        }
        int nz = z;
        if(i == 0 && good){
            cmask |= 15;
            nz = 1;
        }
    
        int ngood = good + i;
        ngood = min(ngood, 2);
        ll nmod = (smod + (i * i * i * i)) % mod;
        res += f(idx - 1, cmask, nmod, newTight, ngood, nz);
    }
    if(!tight){
        dp[idx][mask][smod][tight][good][z] = res;
    }
    return res;
}
ll F(ll id){
    memset(dp, -1, sizeof(dp));
    return f(id, 0, 0, 1, 0, 0);
}
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    fast;
    ll _T = 1;
    ll pans = 0;
    cin >> _T;
    // ll iter = 1;
    while (_T--) {
        ll n;
        cin >> n;
        // n = iter++;
        dig = getDig(n);
        ll sz = dig.size();
        vector<ll> p = {2, 3 ,5, 7};
        ll ans = 0;
        for(int i = 1; i < 16; i++){
            ll pr = 1, cnt = 0;
            for(int j = 0; j < 4; j++){
                if(i & (1 << j)){
                    pr *= p[j];
                    cnt++;
                }
            }
            msk = i;
            mod = pr;
            if(cnt & 1){
                ans += F(sz - 1);
            }
            else{
                ans -= F(sz - 1);
            }
            // cout << ans << "$$\n";
            // break;
        }
        // cout << ans << "\n";
        // if(ans > pans){
        //     // cout << n << endl;
        // }
        // cout << n << " $ " << ans << endl;
        // pans = ans;
        cout << ans << "\n";
    }
    return 0;
}
ITERATIVE
dp[n][0][0] = 1;
dp[n][1][0] = 1;

for(int i = n-1; i >=0 ; i--) {
for(int tight = 0; tight < 2 ; tight++) {
    for(int sum = 0; sum < 200 ; sum++) {
        if(tight) {
            for(int d = 0; d <= ss[i] - '0' ; d++) {
                dp[i][1][sum] += (d == ss[i]-'0') ? dp[i+1][1][sum-d] : dp[i+1][0][sum-d];
            }
        }
        else {
            for(int d = 0; d < 10 ; d++) {
                dp[i][0][sum] += dp[i+1][0][sum-d];
            }
        }
    }
}
}
