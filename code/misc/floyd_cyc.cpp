template<typename T>
ii floyd_cyc(T (*f)(T), T x0) {
    T tort = f(x0), hare = f(f(x0));
    while(tort != hare) {
        tort = f(tort);
        hare = f(f(hare));
    }
    int mu = 0, lam = 1;
    tort = x0;
    while(tort != hare) {
        tort = f(tort);
        hare = f(hare);
        mu++;
    }
    hare = f(tort);
    while(tort != hare) {
        hare = f(hare);
        lam++;
    }
    return ii(lam, mu);
}
