vector<long long> spfa(vector<vector<pair<int, int>>> G, int S) {  
	int n = G.size(); // 假設點的編號為 0 ~ n-1  
	vector<long long> d(n, INF);  
	vector<bool> in_queue(n, false);  
	vector<int> cnt(n, 0);  
	queue<int> Q;  
	d[S] = 0;  
	auto enqueue = [&](int u) {   
		in_queue[u] = true; Q.emplace(u);  
	};  
	enqueue(S);  
	while (Q.size()) {    
	int u = Q.front(); 
	Q.pop();    
	in_queue[u] = false;    
	for (auto [v, cost] : G[u])      
		if (d[v] > d[u] + cost) {        
			if (++cnt[u] >= n) return {}; // 存在負環        
			d[v] = d[u] + cost;        
			if (!in_queue[v]) enqueue(v);      
		}  
	}  
	return d;
}