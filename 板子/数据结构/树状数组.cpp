
struct BIT {
	int n;
	vector<int> c;
	BIT(int n) : n(n),c(n+1,0) {}

	void add(int x,int y) {
		for (;x<=n;x+=x&-x) c[x]+=y;
	}

	int query(int x) {
		int res=0;
		for (;x;x-=x&-x) res+=c[x];
		return res;
	}
};
