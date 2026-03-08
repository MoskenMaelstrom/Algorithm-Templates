// 判环,cross数组判断u和pa[u]这条树边在不在环上
// dfs扫到返祖边时,deep可判奇偶环
void solve()
{
	vector<int> pa(n),deep(n),cross(n),ord;
	vector<bool> vis(n);
	function<void(int)> dfs=[&](int u) {
		ord.push_back(u);
		vis[u]=1;
		for(auto v : adj[u]) {
			if (vis[v]) continue;
			pa[v]=u;
			deep[v]=deep[u]+1;
			dfs(v);
		}
	};
	dfs(0);
	
	int ans=1;
	for(int u=0;u<n;u++) {
		for(auto v : adj[u]) {
			if (deep[v] < deep[u]-1) {
				cross[u]++;
				cross[v]--;
				if ((deep[u]-deep[v]+1)&1) {
					if (a[u] > 0) ans=0;
					a[u]=0;
				}
			}
		}
	}
	
	ranges::reverse(ord);
	for(auto u : ord) {
		if (u != 0) cross[pa[u]]+=cross[u];
	}
}
