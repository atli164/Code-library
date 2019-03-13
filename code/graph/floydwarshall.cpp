vvi floydwarshall(vvii& g) {
  ll n = g.size();
  vvi dp(n, vi(n, LLONG_MAX / 4));
  rep(i, 0, n) dp[i][i] = 0;
  rep(i, 0, n) for(ii x : g[i])
    dp[i][x.second] = min(x.first, dp[i][x.second]);
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
    if(dp[i][k] == LLONG_MAX / 4 || 
      dp[k][j] == LLONG_MAX / 4) continue;
    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]); }
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
    if(dp[i][k] == LLONG_MAX / 4 || dp[k][j] == LLONG_MAX / 4 || 
      dp[i][j] == LLONG_MAX / 4) continue;
    if(dp[i][k] + dp[k][j] < dp[i][j]) dp[i][j] = -(LLONG_MAX / 4); }
  return dp; }
// field tested: allpairspath
