long long solve(vector<int> a, int N, int K) {
  vector<long long> DP(N + 1);
  deque<int> dq(1);
  for (int i = 1; i <= N; ++i) {
    while (dq.front() < i - K)
      dq.pop_front();
    DP[i] = DP[dq.front()] + a[i];
    while (dq.size() && DP[dq.back()] > DP[i])
      dq.pop_back();
    dq.push_back(i);
  }
  long long ans = INF;
  for (int i = N - K + 1; i <= N; ++i)
    ans = min(ans, DP[i]);
  return ans;
}

