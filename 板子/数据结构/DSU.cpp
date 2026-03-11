
struct DSU {
    vector<int> f,siz;
    int cnt;

    DSU():cnt(0) {}
    DSU(int n) {init(n);}

    void init(int n) {
        f.resize(n);
        iota(f.begin(),f.end(),0);
        siz.assign(n,1);
        cnt=n;
    }

    int find(int x) {
        while (x != f[x]) x=f[x]=f[f[x]];
        return x;
    }

    bool merge(int x,int y) {
        x=find(x);
        y=find(y);
        if (x == y) return 0;
        siz[x]+=siz[y];
        f[y]=x;
        cnt--;
        return 1;
    }

    int esize(int x) {
        return siz[find(x)];
    }
};
