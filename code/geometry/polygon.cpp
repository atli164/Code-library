typedef vector<point> polygon;
double sgnarea(polygon &p) {
  double r = 0; rep(i, 0, p.size() - 1) {
    r += cross(p[i], p[i + 1]);
  } return abs(r / 2); }
bool pointinpoly(polygon &p, point q) {
  double s = 0; rep(i, 0, p.size() - 1) {
    s += (ccw(q, p[i], p[i + 1]) > 0 ? 1 : -1) * \
      angle(p[i], q, p[i + 1]);
  } return abs(s) > M_PI; }
polygon convexhull(polygon p) {
  polygon h; int mn = 0; rep(i, 1, p.size()) {
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
