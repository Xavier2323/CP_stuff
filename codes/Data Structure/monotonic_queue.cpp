
vector<int> maxSlidingWindow(vector<int> &num, int k) {
    deque<int> dq;
    vector<int> ans;
    for(int i = 0; i < num.size(); i++) {
        while(dq.size() && dq.front() <= i - k) dq.pop_front();
        while(dq.size() && num[dq.back()] < num[i]) dq.pop_back();
        dq.emplace_back(i);
        if(i >= k - 1) ans.emplace_back(num[dq.front()]);
    }
    return ans;
}
