int cost[MAX_V][MAX_V];//Edge的權重（不存在時為INF)
int mincost[MAX_V];//來自集合X的邊的最小權重
bool used[MAX_V];//頂點i是否包含在X之中
int V;//頂點數

int prim() {
    for(int i = 0; i < v; i++) {
        mincost[i] = INF;
        used[i] = false;
    }
    mincost[0] = 0;
    int res = 0;
    while(true) {
        int v = -1;
        //從不屬於X的頂點中尋找會讓來自X的邊之權重最小的頂點
        for(int u = 0; u < V; u++) {
            if(!used[u] && (v==-1 || mincost[u] < mincost[v])) v = u;
        }
        if(v == -1) break;
        used[v] = true;//將頂點v追加至X
        res += mincost[v];//加上邊的權重
        for(int u = 0; u < V; u++) {
            mincost[u] = min(mincost[u],cost[v][u]);
        }
    }
    return res;
}