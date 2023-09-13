template<class T>
struct Dinic{
	struct edge{
		int from, to;
		T cap;
		edge(int _from, int _to, T _cap) : from(_from), to(_to), cap(_cap) {}
	};
	int n;
	vector<edge> edges;
	vector<vector<int>> g;
	vector<int> cur, h;
	Dinic(int _n) : n(_n+1), g(_n+1) {}
	void add_edge(int u, int v, T cap){
		g[u].push_back(edges.size());
		edges.push_back(edge(u, v, cap));
		g[v].push_back(edges.size());
		edges.push_back(edge(v, u, 0));
	}
	bool bfs(int s,int t){
		h.assign(n, -1);
		h[s] = 0;
		queue<int> que;
		que.push(s);
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			for(auto id : g[u]) {
				const edge& e = edges[id];
				int v = e.to;
				if(e.cap > 0 && h[v] == -1) {
					h[v] = h[u] + 1;
					if(v == t) {
						return 1;
					}
					que.push(v);
				}
			}
		}
		return 0;
	}
	T dfs(int u, int t, T f) {
		if(u == t) {
			return f;
		}
		T r = f;
		for(int& i = cur[u]; i < (int) g[u].size(); ++i) {
			int id = g[u][i];
			const edge& e = edges[id];
			int v = e.to;
			if(e.cap > 0 && h[v] == h[u] + 1) {
				T send = dfs(v, t, min(r, e.cap));
				edges[id].cap -= send;
				edges[id ^ 1].cap += send;
				r -= send;
				if(r == 0) {
					return f;
				}
			}
		}
		return f - r;
	}
	T flow(int s, int t, T f = numeric_limits<T>::max()) {
		T ans = 0;
		while(f > 0 && bfs(s, t)) {
			cur.assign(n, 0);
			T send = dfs(s, t, f);
			ans += send;
			f -= send;
		}
		return ans;
	}
	vector<pair<int,int>> min_cut(int s) {
		vector<bool> vis(n);
		vis[s] = true;
		queue<int> que;
		que.push(s);
		while(!que.empty()) {
			int u = que.front();
			que.pop();
			for(auto id : g[u]) {
				const auto& e = edges[id];
				int v = e.to;
				if(e.cap > 0 && !vis[v]) {
					vis[v] = true;
					que.push(v);
				}
			}
		}
		vector<pair<int,int>> cut;
		for(int i = 0; i < (int) edges.size(); i += 2) {
			const auto& e = edges[i];
			if(vis[e.from] && !vis[e.to]) {
				cut.push_back(make_pair(e.from, e.to));
			}
		}
		return cut;
	}
};

//CSES Distinct Routes
#include <bits/stdc++.h>

using namespace std;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr, path;
    vector< vector<int> > paths;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        path.push_back(v);
        if (v == t) {
            for (int iiddxx = 0; iiddxx < pushed; ++iiddxx)
                paths.push_back(path);
            path.pop_back();
            return pushed;
        }
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            path.pop_back();
            return tr;
        }
        path.pop_back();
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

int main() {
    int n, m, v, u;
    cin >> n >> m;
    Dinic D(n+1, 1, n);
    for (int i = 0; i < m; ++i) {
        cin >> v >> u;
        D.add_edge(v, u, 1);
    }
    D.flow();
    Dinic FLOW(n+1, 1, n);
    for (auto e: D.edges) {
        if (e.flow > 0) {
            FLOW.add_edge(e.v, e.u, 1);
        }
    }
    cout << FLOW.flow() << "\n";
    for (auto p: FLOW.paths) {
        cout << p.size() << "\n";
        for (auto verti: p)
            cout << verti << " ";
        cout << "\n";
    }
    
    return 0;
}
