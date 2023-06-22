const int modulo = 1077563119;
int chromatic(vvi &g) {
    int n = g.size();
    vi gmsk(n, 0);
    for(int i = 0; i < n; ++i)
        for(int x : g[i])
            gmsk[i] |= 1 << x;
    vi ind(1 << n), s(1 << n);
    for(int i = 0; i < (1 << n); ++i)
        s[i] = ((n - __builtin_popcount(i)) & 1 ? -1 : 1);
    ind[0] = 1;
    for(int i = 1; i < (1 << n); ++i) {
        int ctz = __builtin_ctz(i);
        ind[i] = ind[i - (1 << ctz)] + ind[(i - (1 << ctz)) & ~gmsk[ctz]];
        if(ind[i] >= modulo) ind[i] -= modulo;
    }
    for(int k = 1; k < n; ++k) {
        ll sm = 0;
        for(int i = 0; i < (1 << n); ++i) {
            ll cur = (s[i] * (ll) ind[i]) % modulo;
            s[i] = cur;
            sm += cur;
        }
        if(sm % modulo != 0) return k;
    }
    return n;
}
// field tested: committeeassignment
