const int N = 1e6 + 1;
bool prime[N];
ll spf[N];
void Sieve(){
    memset(prime, 1, sizeof(prime));
    memset(spf, -1, sizeof(spf));
    for(ll i = 2; i < N; i++){
        if(!prime[i]) continue;
        spf[i] = i;
        for(ll j = i * i; j < N; j += i){
            if(spf[j] == -1){
                spf[j] = i;
            }
            prime[j] = false;
        }
    }
}