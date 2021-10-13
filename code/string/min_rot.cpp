string min_rot(string s) {
    int n = s.size();
    string res = s;
    s = s + s;
    int rot = 0;
    rep(i,0,n) rep(j,0,n) {
        if(rot + j == i || s[rot + j] < s[i + j]) {
            i += max(0, j - 1);
            break;
        }
        if(s[rot + j] > s[i + j]) {
            rot = i;
            break;
        }
    }
    rotate(res.begin(), res.begin() + rot, res.end());
    return res;
}
