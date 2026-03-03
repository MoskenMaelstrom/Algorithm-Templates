
int N=1e6;
struct Q {
    int l,r,id,bl;
    bool operator<(const Q &q) const {
        if (bl != q.bl) return bl < q.bl;
        return (bl & 1) ? (r < q.r) : (r > q.r);
    }
};

    int ans=0;
    vector<int> a(n+1);
    vector<int> cnt(N+1,0);
    vector<int> res(m);
    vector<Q> que(m);
    
    for (int i=1;i<=n;i++) cin >> a[i];
    int B=max(1,(int)(n/sqrt(max(1,m))));

    for (int i=0;i < m;i++) {
        cin >> que[i].l >> que[i].r;
        que[i].id=i;
        que[i].bl=que[i].l/B;
    }
    ranges::sort(que);

    auto add=[&](int pos) {
        if (++cnt[a[pos]] == 1) ans++;
    };

    auto del=[&](int pos) {
        if (--cnt[a[pos]] == 0) ans--;
    };

    int l=1,r=0;
    for (const auto &q : que) {
        while (l > q.l) add(--l);
        while (r < q.r) add(++r);
        while (l < q.l) del(l++);
        while (r > q.r) del(r--);
        res[q.id]=ans;
    }
