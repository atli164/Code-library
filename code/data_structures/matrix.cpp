template <typename T> bool eq(T a, T b) { return a == b; }
template <typename T> T t_abs(T x) { return (x < T(0)) ? (-x) : x; }
template <> bool eq<double>(double a, double b) { return t_abs<double>(a - b) < 1e-9; }
template <typename T> struct matrix {
    int r, c;
    std::vector<T> dat;
    matrix(int _r, int _c) : r(_r), c(_c) {
        dat = std::vector<T>(r * c, T(0));
    }
    matrix(const matrix& o) : r(o.r), c(o.c), dat(o.dat) { }
    T& operator()(int i, int j) { return dat[i * c + j]; }
    matrix<T> operator +(const matrix& o) {
        matrix<T> res(*this);
        for(int i = 0; i < dat.size(); ++i) {
            res.dat[i] += o.dat[i];
        }
        return res;
    }
    matrix<T> operator -(const matrix& o) {
        matrix<T> res(*this);
        for(int i = 0; i < dat.size() ; ++i) {
            res.dat[i] -= o.dat[i];
        }
        return res;
    }
    matrix<T> operator *(T o) {
        matrix<T> res(*this);
        for(int i = 0; i < dat.size(); ++i) {
            res.dat[i] *= o;
        }
        return res;
    }
    matrix<T> operator *(const matrix& o) {
        matrix<T> res(r, o.c);
        for(int i = 0; i < r; ++i) {
            for(int k = 0; k < c; ++k) {
                for(int j = 0; j < o.c; ++j) {
                    res(i, j) += (*this)(i, k) * o(k, j);
                }
            }
        }
        return res;
    }
    matrix<T> pow(long long p) {
        matrix<T> res(r, c), sq(*this);
        for(int i = 0; i < r; ++i) {
            res(i, i) = T(1);
        }
        while(p) {
            if(p & 1) res = res * sq;
            p >>= 1;
            if(p) sq = sq * sq;
        }
        return res;
    }
    matrix<T> transpose() {
        matrix<T> res(c, r);
        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j) {
                res(j, i) = (*this)(i, j);
            }
        }
        return res;
    }
    matrix<T> rref(T& det, int& rank) {
        matrix<T> mat(*this);
        det = T(1);
        rank = 0;
        for(int ri = 0, ci = 0; ci < c; ++ci) {
            int k = ri;
            for(int i = k + 1; i < r; ++i) if(t_abs(mat(i, ci)) > t_abs(mat(k, ci))) k = i;
            if(k >= r || eq<T>(mat(k, ci), T(0))) continue;
            if(k != ri) {
                det *= T(-1);
                for(int i = 0; i < c; ++i) std::swap(mat(k, i), mat(ri, i));
            }
            det *= mat(ri, ri);
            rank++;
            T d = mat(ri, ci);
            for(int i = 0; i < c; ++i) mat(ri, i) /= d;
            for(int i = 0; i < r; ++i) {
                T piv = mat(i, ci);
                if(i != ri && !eq<T>(piv, T(0))) {
                    for(int j = 0; j < c; ++j) mat(i, j) -= piv * mat(ri, j);
                }
            }
            ri++;
        }
        return mat;
    }
    friend std::ostream& operator <<(std::ostream& out, const matrix<T>& o) {
        for(int i = 0; i < o.r; ++i) {
            for(int j = 0; j < o.c; ++j) {
                out << o.dat[i * o.c + j] << ' ';
            }
            out << '\n';
        }
        return out;
    }
};
// semi-field-tested: personal resistor research