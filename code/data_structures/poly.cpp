template <typename T> struct poly {
    vector<T> coeff;
    poly() : coeff(1, T(0)) { }
    poly(const vector<T> &c) : coeff(c) {
        normalize();
    }
    void normalize() {
        while(coeff.size() > 0 && coeff.back() == T(0))
            coeff.pop_back();
    }
    poly<T> shift(int i) const {
        vector<T> newcoeff(coeff.size() + i, T(0));
        for(int j = i; j < newcoeff.size(); ++j)
            newcoeff[j] = coeff[j - i];
        return poly(newcoeff);
    }
    poly<T> operator +(const poly& p) const {
        poly<T> res = *this;
        res += p;
        return res;
    }
    poly<T>& operator +=(const poly& p) {
        while(coeff.size() < p.coeff.size())
            coeff.push_back(T(0));
        for(int i = 0; i < p.coeff.size(); ++i)
            coeff[i] += p.coeff[i];
        normalize();
        return *this;
    }
    poly<T> operator -(const poly& p) const {
        poly<T> res = *this;
        res -= p;
        return res;
    }
    poly<T>& operator -=(const poly& p) {
        while(coeff.size() < p.coeff.size())
            coeff.push_back(T(0));
        for(int i = 0; i < p.coeff.size(); ++i)
            coeff[i] -= p.coeff[i];
        normalize();
        return *this;
    }
    poly<T> operator *(const poly& p) const {
        vector<T> res(coeff.size() + p.coeff.size(), T(0));
        for(int i = 0; i < coeff.size(); ++i)
            for(int j = 0; j < p.coeff.size(); ++j)
                res[i + j] += coeff[i] * p.coeff[j];
        return poly(res);
    }
    poly<T>& operator *=(const poly& p) {
        return *this = *this * p;
    }
    poly<T> operator *(const T& c) const {
        poly<T> res = *this;
        res *= c;
        return res;
    }
    poly<T>& operator *=(const T& c) {
        for(int i = 0; i < coeff.size(); ++i)
            coeff[i] *= c;
        normalize();
        return *this;
    }
    pair<poly<T>, poly<T>> div_rem(const poly& d) const {
        poly<T> r(coeff), q;
        int dg = d.coeff.size();
        while(r.coeff.size() >= dg) {
            T c = r.coeff.back() / d.coeff.back();
            while(q.coeff.size() <= r.coeff.size() - dg)
                q.coeff.push_back(T(0));
            q.coeff[r.coeff.size() - dg] += c;
            r -= d.shift(r.coeff.size() - dg) * c;
        }
        return make_pair(q, r);
    }
    poly<T> mod_pow(ll e, const poly& m) const {
        vector<T> id({ T(0), T(1) });
        poly<T> res(id), b(coeff);
        while(e) {
            if(e & 1) res = (res * b).div_rem(m).second;
            b = (b * b).div_rem(m).second;
            e >>= 1;
        }
        return res;
    }
    T lin_rec(ll n, const poly& inits) {
        // treat self as char poly
        vector<T> idc({ T(0), T(1) });
        poly<T> id(idc), shf = id.mod_pow(n - 1, *this);
        T res(0);
        for(int i = 0; i < shf.coeff.size() && inits.coeff.size(); ++i)
            res += shf.coeff[i] * inits.coeff[i];
        return res;
    }
    friend bool operator ==(const poly<T>& l, const poly<T>& r) {
        return l.coeff == r.coeff;
    }
    friend bool operator !=(const poly<T>& l, const poly<T>& r) {
        return l.coeff != r.coeff;
    }
};
