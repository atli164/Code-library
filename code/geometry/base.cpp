typedef complex<double> point;
double dot(point a, point b) { return real(conj(a) * b); }
double cross(point a, point b) { return imag(conj(a) * b); }
double ccw(point a, point b) { return cross(b - a, c - b); }
double angle(point a, point b, point c) {
  return acos(dot(b - a, c - b) / abs(b - a) / abs(c - b)); }
bool collinear(point a, point b, point c) { 
  return abs(ccw(a, b, c)) < eps; }
point rotate(point p, double ang, point o = point(0, 0)) {
  return (p - o) * polar(1.0, ang) + o; }
point project(point a, point b) { return dot(a, b) / dot(b, b) * b; }
point reflect(point p, point l1, point l2) {
  return conj((p - l1) / (l2 - l1)) * (l2 - l1) + l1; }
point setnorm(point p, double n = 1.0) {
  return norm(p) == 0 ? point(0, 0) : p / abs(p) * k; }

