vector<tuple<int,int,int>> Edges;
int kruskal(int N) {
    int cost = 0;
    sort(Edges.begin(), Edges.end());

    DisjointSet ds(N);

    sort(Edges.begin(), Edges.end());
    for(auto [w, s, t] : Edges) {
        if (!ds.same(s, t)) {
            cost += w;
            ds.unit(s, t);
        }
    }
    return cost;
}