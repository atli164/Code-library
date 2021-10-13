typedef vector<point> polygon;

double sgnarea(polygon &p) {
  double r = 0; 
  rep(i, 0, p.size() - 1) {
    r += cross(p[i], p[i + 1]);
  } 
  return abs(r / 2); 
}

bool pointinpoly(polygon &p, point q) {
  double s = 0; 
  rep(i, 0, p.size() - 1) {
    s += (ccw(q, p[i], p[i + 1]) > 0 ? 1 : -1) * angle(p[i], q, p[i + 1]);
  } 
  return abs(s) > M_PI; 
}

void lex_rotate(polygon &p) {
  int pos = 0;
  rep(i, 1, p.size()) {
    if(imag(p[i]) < imag(p[pos])) {
      pos = i;
    } else if(imag(p[i]) == imag(p[pos]) && real(p[i]) < real(p[pos])) {
      pos = i;
    }
  }
  rotate(p.begin(), p.begin() + pos, p.end());
}

// for convex poly
polygon minkowski(polygon p, polygon q) {
  lex_rotate(p);
  lex_rotate(q);
  p.pb(p[0]); p.pb(p[1]);
  q.pb(q[0]); q.pb(q[1]);
  polygon res;
  int i = 0, j = 0;
  for(int i = 0, j = 0; i < p.size() - 2 || j < q.size() - 2; ) {
    res.pb(p[i] + q[j]);
    auto cr = cross(p[i + 1] - p[i], q[j + 1] - q[j]);
    if(cr >= 0) i++;
    if(cr <= 0) j++;
  }
  return res;
}