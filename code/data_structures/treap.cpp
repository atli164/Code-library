struct treap {
    struct node {
        int dat, pri, cnt;
        node *l, *r;
        node(int x, int p) : dat(x), pri(p), l(nullptr), r(nullptr), cnt(1) { }
    };

    int get_cnt(node* t) { 
        return t ? t->cnt : 0; 
    }

    void upd_cnt(node* t) { 
        if(t) {
            t->cnt = 1 + get_cnt(t->l) + get_cnt(t->r); 
        }
    }

    void clear_single(node *t) {
        if(t) {
            t->l = t->r = nullptr;
            delete t;
        }
    }

    void clear_rec(node *t) {
        if(t) {
            clear_rec(t->l);
            clear_rec(t->r);
            delete t;
        }
    }

    pair<node*,node*> split(node* t, int k) {
        if(!t) {
            return make_pair(nullptr, nullptr);
        } else if(t->dat < k) {
            auto res = split(t->r, k);
            t->r = res.first;
            upd_cnt(t);
            return make_pair(t, res.second);
        } else if(t->dat > k) {
            auto res = split(t->l, k);
            t->l = res.second;
            upd_cnt(t);
            return make_pair(res.first, t);
        } else {
            auto res = make_pair(t->l, t->r);
            clear_single(t);
            return res;
        }
    }

    node* join(node* l, node* r) {
        if(!l || !r) {
            return l ? l : r;
        } else if(l->pri > r->pri) {
            l->r = join(l->r, r);
            upd_cnt(l);
            return l;
        } else {
            r->l = join(l, r->l);
            upd_cnt(r);
            return r;
        }
    }

    node* find(node *t, int x) {
        while(t) {
            if(x < t->dat) t = t->l;
            else if(t->dat < x) t = t->r;
            else return t;
        }
        return nullptr;
    }

    bool insert(node *&t, int x, int p) {
        if(find(t, x)) return false;
        auto res = split(t, x);
        t = join(res.first, join(new node(x, p), res.second));
        return true;
    }

    bool erase(node *&t, int x) {
        if(!t) return false;
        bool ret;
        if(t->dat < x) ret = erase(t->r, x);
        else if(t.dat > x) ret = erase(t->l, x);
        else {
            node* prv = t;
            t = join(t->l, t->r);
            clear_single(prv);
            ret = true;
        }
        upd_cnt(t);
        return ret;
    }

    node* kth(node *t, int k) {
        if(!t) return t;
        else if(k < get_cnt(t->l)) return kth(t->l, k);
        else if(k == get_cnt(t->l)) return t;
        else return kth(t->r, k - get_cnt(t->l) - 1);
    }

    node* unite(node* l, node* r) {
        if(!l || !r) return l ? l : r;
        if(l->pri < r->pri) swap(l, r);
        auto res = split(r, l->dat);
        l->l = unite(l->l, res.first);
        l->r = unite(l->r, res.second);
        upd_cnt(l);
        return l;
    }

    node* intersect(node* l, node* r) {
        if(!l || !r) {
            clear_rec(l);
            clear_rec(r);
            return nullptr;
        }
        if(l->pri < r->pri) swap(l, r);
        bool has = find(r, l->dat);
        auto res = split(r, l->dat);
        if(has) {
            l->l = intersect(l->l, res.first);
            l->r = intersect(l->r, res.second);
        } else {
            node* old = l;
            l = join(intersect(l->l, res.first), intersect(l->r, res.second));
            clear_single(old);
        }
        upd_cnt(l);
        return l;
    }

    node* sym_diff(node* l, node* r) {
        if(!l || !r) return l ? l : r;
        if(l->pri < r->pri) swap(l, r);
        bool has = find(r, l->dat);
        auto res = split(r, l->dat);
        if(has) {
            node* old = l;
            l = join(sym_diff(l->l, res.first), sym_diff(l->r, res.second));
            clear_single(old);
        } else {
            l->l = unite(l->l, res.first);
            l->r = unite(l->r, res.second);
        }
        upd_cnt(l);
        return l;
    }
};
