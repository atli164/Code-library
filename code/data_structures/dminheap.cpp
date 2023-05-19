template<typename T, int child_num>
struct DMinHeap {
    std::vector<T> dat;
    DMinHeap() : dat(std::vector<T>()) { }
    void sink(size_t i) {
        while(true) {
            size_t c = child_num * i + 1, mnind = c;
            if(c >= dat.size()) break;
            for(size_t j = 1; j < child_num; ++j) {
                if(j + c < dat.size() && dat[j + c] < dat[mnind]) mnind = j + c;
            }
            if(dat[mnind] >= dat[i]) break;
            std::swap(dat[i], dat[mnind]);
            i = mnind;
        }
    }
    void swim(size_t i) {
        while(i > 0 && dat[(i - 1) / child_num] > dat[i]) {
            std::swap(dat[i], dat[(i - 1) / child_num]);
            i--; i /= child_num;
        }
    }
    bool empty() {
        return dat.empty();
    }
    size_t size() {
        return dat.size();
    }
    T peek() { 
        return dat[0]; 
    }
    void increase_root(T x) {
        dat[0] += x;
        sink(0);
    }
    void pop() {
        dat[0] = std::move(dat.back());
        dat.pop_back();
        sink(0);
    }
    void push(T val) {
        dat.push_back(val);
        swim(dat.size() - 1);
    }
};
