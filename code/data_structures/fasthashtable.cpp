template<typename K, typename V>
struct HashCell {
    int8_t dist;
    K key;
    V val;

    HashCell() : dist(-1) { }

    void set_values(int8_t d, K k, V v) {
        dist = d;
        key = k;
        val = v;
    }

    bool inline has_value() const {
        return dist >= 0;
    }
};


// Have to have K as an int-like type to allow for bit operations
// No such limitations on V
template<typename K, typename V>
struct HashTable {
    size_t entries, size, mask, log;
    std::vector<HashCell<K,V> > dat;

    HashTable() : entries(0), size(4), mask(3), log(2), dat(7, HashCell<K,V>()) { }

    void grow() {
        size *= 2;
        mask = size - 1;
        log++;
        rehash(size + log + 1);
    }

    void rehash(size_t buckets) {
        std::vector<HashCell<K, V> > old_dat;
        std::swap(dat, old_dat);
        dat = std::vector<HashCell<K, V> >(buckets, HashCell<K, V>());
        entries = 0;
        for(auto cell : old_dat) {
            if(cell.has_value()) {
                insert(cell.key, cell.val);
            }
        }
    }

    void clear() {
        size = 4;
        mask = 3;
        log = 2;
        entries = 0;
        std::vector<HashCell<K,V> > new_dat(7, HashCell<K,V>());
        std::swap(new_dat, dat);
    }

    // Using a hash incurs a minor overhead but it allows for a far better load factor
    // In tests the resulting hash table is about 4 times smaller
    // Tests show this function to be sufficient to achieve this effect
    // while still being very fast for minimal overhead
    // Will likely have to be changed if table is used for non-32bit inputs
    K inline hash(K x) const {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        return x & mask;
    }

    void insert(K k, V v) {
        if(entries > size / 2) grow();
        K ind = hash(k);
        for(int8_t d = 0; d < log; ++d, ++ind) {
            if(!dat[ind].has_value()) {
                dat[ind].set_values(d, k, v);
                entries++;
                return;
            } else if(dat[ind].key == k) {
                dat[ind].val = v;
                return;
            } else if(dat[ind].dist < d) {
                std::swap(v, dat[ind].val);
                std::swap(k, dat[ind].key);
                std::swap(d, dat[ind].dist);
            }
        }
        grow();
        insert(k, v);
    }

    V get(K k, V fallback) {
        K ind = hash(k);
        for(int8_t d = 0; dat[ind].dist >= d; ++d, ++ind) {
            if(dat[ind].key == k) {
                return dat[ind].val;
            }
        }
        return fallback;
    }

    bool get_ref(K k, V& var) {
        K ind = hash(k);
        for(int8_t d = 0; dat[ind].dist >= d; ++d, ++ind) {
            if(dat[ind].key == k) {
                var = dat[ind].val;
                return true;
            }
        }
        return false;
    }
};