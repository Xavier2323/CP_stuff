vector<tuple<int,int,int>> Edges;
int BellmanFord(int s, int e, int N) {
    const int INF = INT_MAX / 2;
    vector<int> dist(N, INF);

    dist[s] = 0;
    bool update;
    for(int i=1;i<=N;++i) {
        update = false;
        for(auto [v, u, w] : Edges)
        {
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                update = true;
            }
        }

        if (!update)
            break;
        if (i == N) // && update
            return -1; // gg !
    }
    return dist[e];
}