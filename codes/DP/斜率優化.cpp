using Slope = pair<long long, long long>;
// 注意要避免浮點數誤差
bool operator<=(const Slope &a, const Slope &b) {
  // a.first/a.second <= b.first/b.second
  return 1LL * a.first * b.second <= 1LL * b.first * a.second;
}

long long solve(vector<int> C, int n, int M) {
  vector<long long> DP(n + 1), S(n + 1), X(n + 1), Y(n + 1);
  partial_sum(C.begin(), C.end(), S.begin()); //前綴和
  auto getSlope = [&](int a, int b) -> Slope {
    return {Y[b] - Y[a], X[b] - X[a]};
  };
  deque<int> q(1);
  for (int i = 1; i <= n; ++i) {
    long long A_i = -S[i], B_i = 1, C_i = 1LL * S[i] * S[i] + M;
    Slope K_i = {-A_i, B_i};
    while (q.size() > 1 && getSlope(q[0], q[1]) <= K_i)
      q.pop_front();
    int j = q[0];
    DP[i] = A_i * X[j] + B_i * Y[j] + C_i;
    Y[i] = DP[i] + 1LL * S[i] * S[i], X[i] = 2 * S[i]; //計算X_i,Y_i
    while ((j = q.size()) > 1 &&
           getSlope(q[j - 1], i) <= getSlope(q[j - 2], q[j - 1]))
      q.pop_back();
    q.push_back(i);
  }
  return DP[n];
}

// 形式：DP[i] = C_i + max{A_j * x_i + B_j}, j <= R_i
