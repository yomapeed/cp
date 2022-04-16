struct BinaryTrie {
    vector<array<int, 2>> next;
    vector<ll> cnt;
    static const int B = -1;
    int root, cur;
 
    BinaryTrie() {
        next.push_back({-1, -1});
        cnt.push_back(0);
        root = 0;
        cur = 1;
    }
    void insert(long long x) {
        int tmp = root;
        ++cnt[tmp];
        for(int i=B;i>=0;--i) {
            int t = (x >> i) & 1;
            if(next[tmp][t] == -1) {
                next[tmp][t] = cur++;
                next.push_back({-1, -1});
                cnt.push_back(0);
            }
            tmp = next[tmp][t];
            ++cnt[tmp];
        }
    }
    void erase(long long x) {
        int tmp = root;
        --cnt[tmp];
        for(int i = B; i >=0; --i) {
            tmp = next[tmp][(x >> i) & 1];
            --cnt[tmp];
        }
    }
    long long getmax(long long x) {
        int tmp = root;
        long long ans = 0;
        if(cnt[tmp] == 0) {
            return -1;
        }
        for(int i = B;i >=0 ; --i) {
            int t = (x >> i) & 1;
            if(next[tmp][1 - t] != -1 && cnt[next[tmp][1 - t]] > 0) {
                tmp = next[tmp][1 - t];
                ans += 1LL << i;
            }
            else {
                tmp = next[tmp][t];
            }
        }
        return ans;
    }
    long long getmin(long long x) {
        int tmp = root;
        long long ans = 0;
        if(cnt[tmp] == 0) {
            return -1;
        }
        for(int i= B; i >= 0; --i) {
            int t = (x >> i) & 1;
            if(next[tmp][t] != -1 && cnt[next[tmp][t]] > 0) {
                tmp = next[tmp][t];
            }
            else {
                tmp = next[tmp][1 - t];
                ans += 1LL << i;
            }
        }
        return ans;
    }
    void clear() {
        next.clear();
        cnt.clear();
        root = 0;
        next.push_back({-1, -1});
        cnt.push_back(0);
        cur = 1;
    }
};