
const int inf=1e18;
vector<int> dijkstra(vector<vector<array<int,2>>> &adj,int st) {
    int n=adj.size();
    vector<int> dis(n,inf);
    priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;
    dis[st]=0;
    pq.push({0,st});
    while (!pq.empty()) {
        auto [d,u]=pq.top();
        pq.pop();
        if (d > dis[u]) continue;
        for (auto &[v,w] : adj[u]) {
            if (dis[u]+w < dis[v]) {
                dis[v]=dis[u]+w;
                pq.push({dis[v],v});
            }
        }
    }
    return dis;
}
