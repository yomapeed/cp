const int N = 1e5 + 1;
ll fac[N], invfac[N];
ll power(ll x, ll y, ll p){
    ll res = 1;
    x = x % p;
    while (y > 0){
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
ll modi(ll a, ll m){
    return power(a, m - 2, m);
}
ll nCr(ll n, ll r, ll p){
    if (r == 0)
        return 1;
    return (fac[n] * invfac[r] % p *
        invfac[n - r] % p) % p;
}
void PreCalc(int _n, int _mod){
    fac[0] = 1;
    invfac[0] = 1;
    for(int i = 1; i <= _n; i++){
        fac[i] = (i * fac[i - 1]) % _mod;
        invfac[i] = modi(fac[i], _mod);
    }
}