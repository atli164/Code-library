vi nge(vi& v) {
  vi res(v.size(), -1);
  stack<ii> s; s.push(ii(0,v[0]));
  for(int i = 0; i < v.size(); ++i) {
    while(!s.empty() && s.top().second <= v[i]) {
      res[s.top().first] = i; s.pop(); }
    s.push(ii(i,v[i])); }
  return res; }
