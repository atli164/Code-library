template<typename T>
struct segtree {
    vector<T> v, d; int l, n;
    T id = 0;
    T f(T a, T b) { return a + b; }
    T g(T a, T x, int k) { return a + x * k; }
    void apply(int i, T x, int k) {
        v[i] = g(v[i], x, k);
        if(i < n) d[i] = f(d[i], x);
    }
    segtree(int _n) : n(_n) {
        l = 32 -  __builtin_clz(n);
        v = vector<T>(2 * n, id);
        d = vector<T>(n, id);
    }
    void swim(int i) {
        int k = 2;
        for(i += n; i > 1; k <<= 1) {
            i >>= 1;
            v[i] = g(f(v[i << 1], v[i << 1 | 1]), d[i], k);
        }
    }
    void sink(int i) {
        int s = l, k = 1 << (l - 1);
        for(i += n; s > 0; --s, k >>= 1) {
            int j = i >> s;
            apply(j << 1, d[j], k);
            apply(j << 1 | 1, d[j], k);
            d[j] = id;
        }
    }
    void update(int i, T x) {
        sink(i);
        for(v[i += n] = x; i >>= 1; )
            v[i] = f(v[i << 1], v[i << 1 | 1]);
        swim(i);
    }
    void range_update(int l, int r, T x) {
        sink(l); sink(r);
        int k = 1, l0 = l, r0 = r;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if(l & 1) apply(l++, x, k);
            if(r & 1) apply(--r, x, k);
        }
        swim(l0); swim(r0);
    }
    T query(int l, int r) {
        sink(l); sink(r);
        T resl = id, resr = id;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resl = f(resl, v[l++]);
            if(r & 1) resr = f(v[--r], resr);
        }
        return f(resl, resr);
    }
};
