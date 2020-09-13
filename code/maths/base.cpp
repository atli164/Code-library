ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll egcd(ll a, ll b, ll& x, ll& y) {
  if(b == 0) { x = 1; y = 0; return a; }
  ll d = egcd(b, a % b, x, y);
  x -= a / b * y; swap(x, y); return d; }

ll mod_inv(ll a, ll m) {
  ll x, y, d = egcd(a, m, x, y);
  return d == 1 ? (x%m+m)%m : -1; }

ll mod_pow(ll b, ll e, ll m) {
  ll res = 1; while(e) {
    if(e & 1) res = (res*b%m+m)%m;
    b *= b; b %= m; e >>= 1; }
  return res; }
