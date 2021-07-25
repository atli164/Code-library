typedef complex<long double> cpx;

void fft(vector<cpx> &x, int n, bool inv=false) {
  for(int i = 0, j = 0; i < n; i++) {
    if(i < j) swap(x[i], x[j]);
    int m = n >> 1; while(1 <= m && m <= j) 
      j -= m, m >>= 1; j += m; }
  for(int mx = 1; mx < n; mx <<= 1) {
    cpx wp = polar(1.0L, (inv ? -1 : 1) * M_PIl / mx), w = 1;
    for(int m = 0; m < mx; m++, w *= wp) {
      for(int i = m; i < n; i += mx << 1) {
        cpx t = x[i + mx] * w; x[i + mx] = x[i] - t;
        x[i] += t; } } } if(inv) rep(i,0,n) x[i] /= n; }
