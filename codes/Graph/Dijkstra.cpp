int Dijkstra(int s, int e, int N) {
    const int INF = INT_MAX / 2;
    vector<int> dist(N, INF);
    vector<bool> used(N, false);

    using T = tuple<int,int>;
    priority_queue<T, vector<T>, greater<T>> pq;

    dist[s] = 0;
    pq.emplace(0, s); // (w, e) 讓 pq 優先用 w 來比較

    while (!pq.empty()) {
        tie(std::ignore, s) = pq.top();
        pq.pop();

        if ( used[s] ) continue;
        used[s] = true; // 每一個點都只看一次

        for (auto [e, w] : V[s]) {
            if (dist[e] > dist[s] + w) {
                dist[e] = dist[s] + w;
                pq.emplace(dist[e], e);
            }
        }
    }

    return dist[e];
}
