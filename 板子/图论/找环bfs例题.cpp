//2025 ICPC 沈阳 F
//找无向图(无重边,无自环)里的简单环,要求环离起点是尽量近的,所以是双源bfs.

void print(int u,int v) {
	cout<<u+1<<" "<<v+1<<"\n";
}
void solve()
{
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	s--,t--;
	
	vector<int> fa(n,-1);
	vector<array<int,2>> edge;
	vector adj(n,vector<array<int,2>>(0));
	vector<int> visp(n);
	vector<int> vise(m);
	vector<array<int,2>> ans(m);
	int pos=-1;
	for(int i=0;i<m;i++) {
		int u,v;
		cin>>u>>v;
		u--,v--;
		if (u == s and v == t or u == t and v == s) pos=i;
		edge.push_back({u,v});
		adj[u].push_back({v,i});
		adj[v].push_back({u,i});
	}
	
	if (pos == -1) {
		cout<<"Yes\n";
		for(auto [u,v] : edge) {
			if (u == s or u == t) print(v,u);
			else print(u,v);
		}
		return;
	}
	
	auto check=[&]() -> int {
		queue<int> q;
		q.push(s),q.push(t);
		visp[s]=visp[t]=1;
		fa[s]=fa[t]=pos;
		while (!q.empty()) {
			int u=q.front();
			q.pop();
			for(auto [v,i] : adj[u]) {
				if (i == fa[u]) continue;
				if (visp[v]) return i;
				q.push(v);
				visp[v]=1;
				fa[v]=i;
				ans[i]={v,u};
			}
		}
		return -1;
	};
	
	//避免LCA冲突
	auto work=[&](int r,bool update) {
		while (1) {
			int p=fa[r];
			vise[p]=1;
			auto [u,v]=edge[p];
			visp[u]=visp[v]=2;
			if (u == r) {
				if (update) ans[p]={v,u};
				r=v;
			}
			else {
				if (update) ans[p]={u,v};
				r=u;
			}
			if (p == pos) break;
		}
	};
	
	int st=check();
	if (st == -1) {cout<<"No\n";return;}
	vise[st]=1;
	auto [l,r]=edge[st];
	ans[st]={r,l};
	work(r,1);
	work(l,0);
	
	queue<int> q;
	for(int i=0;i<n;i++) {
		if (visp[i] == 2) q.push(i);
	}
	
	while (!q.empty()) {
		int u=q.front();
		q.pop();
		for(auto [v,i] : adj[u]) {
			if (vise[i]) continue;
			vise[i]=1;
			ans[i]={v,u};
			q.push(v);
		}
	}
	
	cout<<"Yes\n";
	for(int i=0;i<m;i++) {
		print(ans[i][0],ans[i][1]);
	}
}
