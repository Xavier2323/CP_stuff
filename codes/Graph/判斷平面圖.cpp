//做smoothing,把degree <= 2的點移除
//O(n^3)
using AdjacencyMatrixTy = vector<vector<bool>>;
AdjacencyMatrixTy smoothing(AdjacencyMatrix &G) {
	size_t N = G.size(), Change = 0;
	do {
		Change = 0;
		for(size_t u = 0; u < N; ++u) {
			vector<size_t> E;
			for(size_t v = 0; v < N && E.size() < 3; ++v) 
				if(G[u][v] && u != v) E.emplace_back(v);
			if(E.size() == 1 || E.size() == 2) {
				++Change;
				for(auto v : E) G[u][v] = G[v][u] = false;
			}
			if(E.size() == 2) {
				auto [a,b] = make_pair(E[0], E[1]);
				G[a][b] = G[b][a] = true;
			}
		}
	}
	while(Change);
	return G;
}

//計算Degree
//O(n^2)
vector<size_t> getDegree(const AdjacencyMatrixTy &G) {
	size_t N = G.size();
	vector<size_t> Degree(N);
	for(size_t u = 0; u < N; ++u) 
		for(size_t v = u + 1; v < N; ++v) {
			if(!G[u][v]) continue;
			++Degree[u], ++Degree[v];
		}
	return Degree;
}

//判斷是否為K5 or K33
//O(n)
bool is_K5_or_K33(const vector<size_t> &Degree) {
	unordered_map<size_t, size_t> Num;
	for(auto Val : Degree) ++Num[Val];
	size_t N = Degree.size();
	bool isK5 = Num[4] == 5 && Num[4] + Num[0] == N;
	bool isK33 = Num[3] == 6 && Num[3] + Num[0] == N;
	return isK5 || isK33;
}