
struct Q {
    int l,r,id;
};

const int N=1e6;

	vector<int> a(n+1);
	vector<int> cnt(N+1);
	int kind=0;
	auto add=[&](int x) {
		if (++cnt[a[x]] == 1) kind++;
	};
	
	auto del=[&](int x) {
		if (--cnt[a[x]] == 0) kind--;
	};

    int B=max(1ll,(int)(n / sqrt(m)));
	sort(que.begin(),que.end(),[&](Q& a,Q& b) {
        if (a.l / B != b.l / B) return a.l < b.l;
        return ((a.l / B) & 1) ? a.r < b.r : a.r > b.r;
    });
	
    int l=1,r=0;
    vector<int> res(m);
    for (auto &q : que) {
        while (l > q.l) add(--l);
        while (r < q.r) add(++r);
        while (l < q.l) del(l++);
        while (r > q.r) del(r--);
        res[q.id]=kind;
    }
