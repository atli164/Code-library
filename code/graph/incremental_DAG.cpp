// G.F. Italiano. Amortized efficiency of a path retrieval data structure.
// Theoretical Computer Science, 48(2–3):273–281, 1986.
struct incremental_DAG {
    int n;
    vvi par;
    vector<vvi> ch;
    incremental_DAG(int _n) : n(_n), par(n, vi(n, -1)), ch(n, vvi()) { }
    bool reachable(int s, int t) {
        return s == t || par[s][t] >= 0;
    }
    bool add_edge(int s, int t) {
        if(reachable(t, s)) return false;
        if(reachable(s, t)) return false;
        rep(i,0,n) if(reachable(i, s) && !reachable(i, t)) meld(p, t, s, t);
        return true;
    }
    void meld(int r, int s, int u, int v) {
        par[r][v] = u;
        ch[r][u].pb(v);
        for(int x : ch[s][v]) {
            if(!reachable(r, x)) meld(r, s, v, x);
        }
    }
};