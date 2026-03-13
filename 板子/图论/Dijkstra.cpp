
const int inf=1e18;
vector<int> dijkstra(vector<vector<array<int,2>>> &adj, int start) {
    int n = adj.size();
    vector<int> dis(n, inf);
    dis[start] = 0;
    set<array<int,2>> st;
    st.insert({0, start});
    while (!st.empty()) {
        auto [cdis, u] = *st.begin();
        st.erase(st.begin());
        if (cdis > dis[u]) continue;
        for (auto &[v, w] : adj[u]) {
            int ndis = dis[u] + w;
            if (ndis < dis[v]) {
                dis[v] = ndis;
                st.insert({ndis, v});
            }
        }
    }
    return dis;
}
