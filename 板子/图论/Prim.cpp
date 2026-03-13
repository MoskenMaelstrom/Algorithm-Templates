
const int inf=1e18;
int Prim(int n,vector<vector<int>>& adj) {
    int res=0;
    vector<int> dist(n,inf);
    vector<bool> vis(n);
    dist[0]=0;
    for (int i=0;i<n;i++) {
        int u=-1;
        for (int j=0;j<n;j++) {
            if (!vis[j] and (u == -1 or dist[j] < dist[u])) u=j;
        }
        if (dist[u] == inf) return -1; 
        vis[u]=1;
        res+=dist[u];
        for (int v=0;v<n;v++) {
            if (!vis[v] and adj[u][v] < dist[v]) dist[v]=adj[u][v];
        }
    }
    return res;
}
