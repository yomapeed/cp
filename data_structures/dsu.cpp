class dsu {
  public:
    vector<int> parent, size, rnk;
    dsu(int n) {
        parent.assign(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
        size.assign(n, 1);
        rnk.assign(n, 0);
    }
    int findset(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = findset(parent[v]);
    }
    void merge(int a, int b) {
        a = findset(a);
        b = findset(b);
        if (a != b) {
            if (rnk[a] < rnk[b])
                swap(a, b);
            parent[b] = a;
            if (rnk[a] == rnk[b])
                rnk[a]++;
            size[a] += size[b];
        }
    }
    int size_containing(int a) { return size[findset(a)]; }
};
