//dfs兩次
vector<int> level;

void dfs(int u, int parent = -1) {
  if(parent == -1) level[u] = 0;
  else level[u] = level[parent] + 1;
  for (int v : Tree[u]) {
    if (v == parent) continue;
    dfs(v, u);
  }
}

dfs(1); // 隨便選一個點
int a = max_element(level.begin(), level.end()) - level.begin();
dfs(a); // a 必然是直徑的其中一個端點
int b = max_element(level.begin(), level.end()) - level.begin();
cout << level[b] << endl;

//紀錄每個點的最長距離跟次長距離
vector<int> D1, D2; // 最遠、次遠距離
int ans = 0; // 直徑長度

void dfs(int u, int parent = -1) {
  D1[u] = D2[u] = 0;
  for (int v : Tree[u]) {
    if (v == parent) continue;
    dfs(v, u);
    int dis = D1[v] + 1;
    if (dis > D1[u]) {
      D2[u] = D1[u];
      D1[u] = dis;
    } else
      D2[u] = max(D2[u], dis);
  }
  ans = max(ans, D1[u] + D2[u]);
}