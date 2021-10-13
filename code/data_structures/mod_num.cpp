template <ll p> struct mod_p {
    ll val;
    mod_p() : val(0) { }
    mod_p(ll _val) : val(_val) { }
    mod_p<p> operator +(const mod_p<p>& o) const {
        ll c = val + o.val;
        return mod_p<p>(c >= p ? c - p : c);
    }
    mod_p<p> operator -(const mod_p<p>& o) const {
        ll c = val + o.val;
        return mod_p<p>(c < 0 ? c + p : c);
    }
    mod_p<p> operator *(const mod_p<p>& o) const {
        __int128 c = ((__int128) val) * o.val % p;
        return mod_p<p>(c >= p ? c - p : c);
    }
    mod_p<p>& operator +=(const mod_p<p>& o) {
        val += o.val;
        if(val >= p) val -= p;
        return *this;
    }
    mod_p<p>& operator -=(const mod_p<p>& o) {
        val -= o.val;
        if(val < 0) val += p;
        return *this;
    }
    mod_p<p>& operator *=(const mod_p<p>& o) {
        val = ((__int128) val) * o.val % p;
        if(val < 0) val += p;
        return *this;
    }
    mod_p<p> operator -() const {
        return mod_p<p>(val ? p - val : 0);
    }
    mod_p<p> pow(ll k) const {
        mod_p<p> x = *this, y = 1;
        while(k) {
            if(k & 1) y *= x;
            x *= x;
            k >>= 1;
        }
        return y;
    }
    mod_p<p> operator /(const mod_p<p>& o) const {
        return *this * o.pow(p - 2);
    }
    mod_p<p>& operator /=(const mod_p<p>& o) {
        return *this *= o.pow(p - 2);
    }
    friend bool operator ==(const mod_p<p>& l, const mod_p<p>& r) {
        return l.val == r.val;
    }
    friend bool operator !=(const mod_p<p>& l, const mod_p<p>& r) {
        return l.val != r.val;
    }
    ll legendre() const {
        if(val == 0) return 0;
        if(p == 2) return 1;
        return pow((p - 1) / 2) == 1 ? 1 : -1;
    }
    mod_p<p> sqrt() const {
        if(val == 0) return 0;
        if(p == 2) return 1;
        assert(legendre() == 1);
        ll s = 0, q = p - 1;
        mod_p<p> z(2);
        while(~q & 1) s++, q >>= 1;
        if(s == 1) return pow((p + 1) / 4);
        while(z.legendre() != -1) z += 1;
        mod_p<p> c = z.pow(q), r = pow((q + 1) / 2), t = pow(q);
        ll m = s;
        while(t != 1) {
            ll i = 1;
            mod_p<p> ts = t * t;
            while(ts != 1) {
                i++;
                ts *= ts;
            }
            mod_p<p> b = c.pow(1LL << (m - i - 1));
            r *= b; t *= b; t *= b; c = b * b; m = i;
        }
        return r;
    }
    mod_p<p> log(mod_p<p> b, mod_p<p> x) {
        assert(b != 0);
        ll n = sqrt(p) + 1;
        mod_p<p> an = a.pow(n), cur = b;
        unordered_map<mod_p<p>,int> vals;
        for(int i = 0; i <= n; ++i) {
            vals[cur] = i;
            cur *= a;
        }
        cur = 1;
        for(int i = 1; i <= n; ++i) {
            cur *= an;
            if(vals.count(cur)) {
                mod_p<p> ans(n);
                ans *= i;
                ans -= vals[cur];
                return ans;
            }
        }
        assert(false);
    }
};
