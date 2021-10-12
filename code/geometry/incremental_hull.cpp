// credit: chemthan
struct hull_cmp {
    bool operator() (const point& a, const point& b) const {
        if(real(a) != real(b)) return real(a) < real(b);
        return imag(a) < imag(b);
    }
};
struct incremental_hull {
    set<point, hull_cmp> hull;
    typedef set<point, hull_cmp>::iterator point_it;
    bool inside(point p) {
        auto p1 = hull.lower_bound(p);
        if(p1 == hull.end()) {
            return false;
        }
        if(real(*p1) == real(p)) {
            return p1 != hull.begin() && imag(p) <= imag(*p1);
        }
        if(p1 == hull.begin()) {
            return false;
        }
        auto p2 = p1--;
        return cross(p - *p1, *p2 - p) >= 0;
    }
    void remove(point_it it) {
        if(hull.size() == 1 || it == hull.begin()) {
            hull.erase(it);
            return;
        }
        auto p1 = --it, p2 = ++it;
        if(++it == hull.end()) {
            hull.erase(p2);
            return;
        }
        hull.erase(p2);
    }
    void insert(point p) {
        if(inside(p)) return;
        point_it p1, p2, pnt = hull.insert(p).fs;
        for(;; remove(p2)) {
            p1 = pnt;
            if(++p1 == hull.end()) break;
            p2 = p1;
            if(++p1 == hull.end()) break;
            if(cross(*p2 - p, *p1 - p) < 0) break;
        }
        for(;; remove(p2)) {
            if((p1 = pnt) == hull.begin()) break;
            if(--p1 == hull.begin()) break;
            p2 = p1--;
            if(cross(*p2 - p, *p1 - p) > 0) break;
        }
    }
};
// Field tested: Hiring Help