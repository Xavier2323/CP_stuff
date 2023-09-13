
vector<int> G[MAXN];
int color[MAXN]; // -1: not colored, 0: black, 1: white
/* color the connected component where u is */
/* parameter col: the color u should be colored */ 
bool coloring(int u, int col) {
    if(color[u] != -1) {
        if(color[u] != col) return false;
        return true;
    }
    color[u] = col;
    for(int v : G[u])
        if(!coloring(v, col ^ 1))
            return false;
    return true;
}

//check if a graph is a bipartite graph

bool checkBipartiteG(int n) {
    for(int i = 1; i <= n; i++)
        color[i] = -1;
    for(int i = 1; i <= n; i++)
        if(color[i] == -1 && 
            !coloring(i, 0))
            return false;
    return true;
}