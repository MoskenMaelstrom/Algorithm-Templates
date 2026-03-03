
struct Q {
    int l,r,id;
};

const int N=1e6;
struct Mo {
    int B;
    vector<int> cnt,res;
    Mo(int n,int m,vector<int>& a,vector<Q>& que) {
        B=max(1ll,(int)(n / sqrt(m)));
        cnt.assign(N+1,0);
        res.resize(m+1);

        sort(que.begin(),que.end(),[&](Q& a,Q& b) {
            if (a.l / B != b.l / B) return a.l < b.l;
            return ((a.l / B) & 1) ? a.r < b.r : a.r > b.r;
        });

		int kind=0;
        auto add=[&](int x) {
        	if (++cnt[a[x]] == 1) kind++;
        };
        auto del=[&](int x) {
        	if (--cnt[a[x]] == 0) kind--;
        };

        int l=1,r=0;
        for (auto q : que) {
            while (l > q.l) add(--l);
            while (r < q.r) add(++r);
            while (l < q.l) del(l++);
            while (r > q.r) del(r--);
            res[q.id]=kind;
        }
    }
};
