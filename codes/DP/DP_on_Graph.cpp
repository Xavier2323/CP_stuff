//G.Longest Path
vector<vector<int>> G;
vector<int> in;
int n, m;
cin >> n >> m;
G.assign(n + 1, {});
in.assign(n + 1, 0);
while (m--) {
  int u, v;
  cin >> u >> v;
  G[u].emplace_back(v);
  ++in[v];
}
int solve(int n) {
  vector<int> DP(G.size(), 0);
  vector<int> Q;
  for (int u = 1; u <= n; ++u)
    if (in[u] == 0)
      Q.emplace_back(u);
  for (size_t i = 0; i < Q.size(); ++i) {
    int u = Q[i];
    for (auto v : G[u]) {
      DP[v] = max(DP[v], DP[u] + 1);
      if (--in[v] == 0)
        Q.emplace_back(v);
    }
  }
  return *max_element(DP.begin(), DP.end());
}
//max_indepent_set on tree
vector<int> DP[2];
int dfs(int u, int pick, int parent = -1) {
  if (u == parent) return 0;
  if (DP[pick][u]) return DP[pick][u];
  if (Tree[u].size() == 1) return pick; // 葉子
  for (auto v : Tree[u]) {
    if (pick == 0) {
      DP[pick][u] += max(dfs(v, 0, u), dfs(v, 1, u));
    } else {
      DP[pick][u] += dfs(v, 0, u);
    }
  }
  return DP[pick][u] += pick;
}
int solve(int n) {
  DP[0] = DP[1] = vector<int>(n + 1, 0);
  return max(dfs(1, 0), dfs(1, 1));
}
//Traveling Salesman // AtCoder
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int cost(vector<tuple<int,int,int>> &point, int from, int to) {
    auto [x,y,z] = point[from];
    auto [X,Y,Z] = point[to];
    return abs(X-x)+abs(Y-y)+max(0,Z-z);
}//從一個點走到另一個點的花費

signed main() {
    int n;cin>>n;
    vector<tuple<int,int,int>> point(n);
    for(auto &[x,y,z]:point) {
        cin>>x>>y>>z;
    }
    vector<vector<int>> dp(1<<n,vector<int> (n,INF));
		//1<<n(2^n)代表1~n的所有子集，代表走過的點
		//n代表走到的最後一個點
    dp[0][0] = 0;
    for(int i=1;i<(1<<n);i++) {
        for(int j=0;j<n;j++) {
            if(i & (1<<j)) {
								//j是走到的最後一個點，必須要在i裡面
                for(int k=0;k<n;k++) {
                    dp[i][j] = min(dp[i][j],dp[i-(1<<j)][k]+cost(point,k,j));
										//i集合裡面走到j = i/{j}集合裡走到k，再從k走到j
                }
            }
          	//cout<<dp[i][j]<<' ';
        }
      	//cout<<endl;
    }
    cout<<dp[(1<<n)-1][0];//每個都要走到，要走回1
    return 0;
}