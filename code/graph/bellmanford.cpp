vi bellmanford(vvii& g, ll a) {
  vi dist(g.size(), INT_MAX); dist[a] = 0;
  rep(i, 0, g.size() - 1) { rep(j, 0, g.size()) {
    if(dist[j] == INT_MAX) continue; for(ii x : g[j]) 
      dist[x.second] = min(dist[x.second], dist[j] + x.first);
  } } while(true) { bool done = true;
    rep(i, 0, g.size()) {
      if(dist[i] == INT_MAX) continue; for(ii x : g[i]) {
        if(dist[x.second] == -INT_MAX) continue;
        if(dist[i] + x.first < dist[x.second]) {
          dist[x.second] = -INT_MAX; done = false;
  } } } if(done) break; } return dist; }
// field tested: shortestpath3
