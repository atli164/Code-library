vector<point> convexhull(vector<point> p) {
  vector<point> h; int mn = 0; rep(i, 1, p.size()) {
    if(make_pair(imag(p[i]), real(p[i])) <
      make_pair(imag(p[mn]), real(p[mn]))) mn = i; }
    swap(p[mn], p[0]); point piv = p[0];
    auto cmp = [&piv](point a, point b) {
      return abs(arg(a - piv) - arg(b - piv)) < eps ?
        abs(a - piv) < abs(b - piv) :
        arg(a - piv) < arg(b - piv); };
    sort(++p.begin(), p.end(), cmp); 
    h.push_back(p.back()); h.push_back(p[0]); 
    h.push_back(p[1]); int ind = 2, cnt; 
    while(cnt < p.size()) { cnt = h.size() - 1;
      if(ccw(h[cnt - 1], h[cnt], p[ind]) > 0)
        h.push_back(p[ind++]); else h.pop_back();
    } return h; }