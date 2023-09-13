void compute(int L, int R, int optL, int optR) {
  if (L > R)
    return;
  int mid = L + (R - L) / 2;
  DP[mid] = INF;
  int opt = -1;
  for (int k = optL; k <= min(mid - 1, optR); k++) {
    if (DP[mid] > f(k) + w(k, mid)) {
      DP[mid] = f(k) + w(k, mid);
      opt = k;
    }
  }
  compute(L, mid - 1, optL, opt);
  compute(mid + 1, R, opt, optR);
}
// compute(1, n, 0, n);

