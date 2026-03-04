
int kruskal(int n,vector<array<int,3>>& E) {
	ranges::sort(E);
    DSU dsu(n);
    int res=0,cnt=0;
    for (auto& [w,u,v] : E) {
        if (dsu.merge(u,v)) {
            res+=w;
            cnt++;
            if (cnt == n-1) break;
        }
    }
    assert(cnt == n-1);
	return res;
}
