struct SCC{
	int n, cnt = 0, dfn_cnt = 0;
	vector<vector<int>> g;
	vector<int> sz, scc, low, dfn;
	stack<int> st;
	vector<bool> vis;

	SCC(int _n = 0) : n(_n) {
		sz.resize(n + 1);
		scc.resize(n + 1);
		low.resize(n + 1);
		dfn.resize(n + 1);
		vis.resize(n + 1);
		g.resize(n + 1);
	}

	inline void add_edge(int u, int v) {
		g[u].push_back(v);
	}

	inline void build() {
		function<void(int)> dfs = [&](int u) {
			low[u] = dfn[u] = ++dfn_cnt;
			vis[u] = true;
			st.push(u);

			for (auto v : g[u]) {
				if (!dfn[v]) {
					dfs(v);
					low[u] = min(low[u], low[v]);
				} else if (vis[v]) {
					low[u] = min(low[u], dfn[v]);
				}
			}

			if (low[u] == dfn[u]) {
				++cnt;
				while (true) {
					int v = st.top();
					st.pop();
					vis[v] = false;
					scc[v] = cnt;
					sz[cnt]++;
					if (v == u) break;
				}
			}
		};

		for (int i = 1; i <= n; ++i) {
			if (!dfn[i]) {
				dfs(i);
			}
		}
	}

	vector<vector<int>> compress() {
		vector<vector<int>> ans(cnt + 1);

		for (int u = 1; u <= n; ++u) {
			for (auto v : g[u]) {
				if (scc[u] != scc[v]) {
					ans[scc[u]].push_back(scc[v]);
				}
			}
		}

		for (int i = 1; i <= cnt; ++i) {
			sort(ans[i].begin(), ans[i].end());
			ans[i].erase(unique(ans[i].begin(), ans[i].end()), ans[i].end());
		}

		return ans;
	}
};
