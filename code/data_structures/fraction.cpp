template <typename T> struct fraction {
    T p, q;
    T gcd(T a, T b) { return b == T(0) ? a : gcd(b, a % b); }
    fraction() : p(T(0)), q(T(1)) { }
    fraction(T _p) : p(_p), q(T(1)) { }
    fraction(T _p, T _q) : p(_p), q(_q) {
        reduce();
    }
    void reduce() {
        if(p == T(0)) {
            q = T(1);
            return;
        }
        assert(q != T(0));
        if(q < T(0)) {
            p = -p;
            q = -q;
        }
        T g = gcd(abs(q), abs(p));
        p /= g;
        q /= g;
    }
    fraction<T> operator +(const fraction& o) {
        return fraction<T>(p * o.q + q * o.p, q * o.q);
    }
    fraction<T> operator -(const fraction& o) {
        return fraction<T>(p * o.q - q * o.p, q * o.q);
    }
    fraction<T> operator *(const fraction& o) {
        return fraction<T>(p * o.p, q * o.q);
    }
    fraction<T> operator /(const fraction& o) {
        return fraction<T>(p * o.q, q * o.p);
    }
    fraction<T> operator -() {
        return fraction<T>(-p, q);
    }
    fraction<T>& operator +=(const fraction& o) {
        p *= o.q;
        p += q * o.p;
        q *= o.q;
        reduce();
        return *this;
    }
    fraction<T>& operator -=(const fraction& o) {
        p *= o.q;
        p -= q * o.p;
        q *= o.q;
        reduce();
        return *this;
    }
    fraction<T>& operator *=(const fraction& o) {
        p *= o.p;
        q *= o.q;
        reduce();
        return *this;
    }
    fraction<T>& operator /=(const fraction& o) {
        p *= o.q;
        q *= o.p;
        reduce();
        return *this;
    }
    friend bool operator ==(const fraction<T>& l, const fraction<T>& r) {
        return l.p == r.p && l.q == r.q;
    }
    friend bool operator !=(const fraction<T>& l, const fraction<T>& r) {
        return l.p != r.p || l.q != r.q;
    }
    friend bool operator <(const fraction<T>& l, const fraction<T>& r) {
        return l.p * r.q < r.p * l.q;
    }
    friend bool operator >(const fraction<T>& l, const fraction<T>& r) {
        return l.p * r.q > r.p * l.q;
    }
    friend std::ostream& operator <<(std::ostream& out, const fraction<T>& o) {
        out << o.p << '/' << o.q;
        return out;
    }
    friend fraction<T> abs(const fraction<T> &x) {
        return x < 0 ? -x : x;
    }
};
