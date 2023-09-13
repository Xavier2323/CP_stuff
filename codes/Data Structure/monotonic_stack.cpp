
long long maxRectangle(vector<int> &h) {
    h.emplace_back(0);
    stack<pair<int,int>> stick;
    long long ans = 0;
    for(int i = 0; i < h.size(); i++) {
        int corner = i;
        while(stick.size() && stick.top().first >= h[i]) {
            corner = stick.top().second;
            ans = max(ans, 1LL * (i - corner) * stick.top().first);
            stick.pop();
        }
        stick.emplace(h[i],corner);
    }
    return ans;
}
