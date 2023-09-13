struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int find(int x) {
		return (dsu[x] == x ? x : dsu[x] = find(dsu[x]));
	}
	int unite(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
        	return 1;
	}
};
