
const int inf=1e18;
struct Info {
	int sum,Max,Min;
	Info() : sum(0),Max(-inf),Min(inf) {};
    Info(int val) : sum(val),Max(val),Min(val) {};
    Info operator+(const Info &other) const {
    	Info res;
    	res.sum=sum+other.sum;
    	res.Min=min(Min,other.Min);
    	res.Max=max(Max,other.Max);
    	return res;
    }
};

struct SegTree {
	int n;
	vector<Info> info;
    vector<int> ladd,lset;
    const int f=1e18+7; 

	SegTree(int _) {
		n=_;
		info.resize(n*4);
        ladd.resize(n*4,0);
        lset.resize(n*4,f);
	}
	
    void applyset(int v,int l,int r,int val) {
        info[v].sum=(r-l+1)*val;
        info[v].Min=val;
        info[v].Max=val;
        lset[v]=val;
        ladd[v]=0;
    }

    void applyadd(int v,int l,int r,int val) {
        info[v].sum+=(r-l+1)*val;
        info[v].Min+=val;
        info[v].Max+=val;
        if (lset[v] != f) {
            lset[v]+=val;
        } else {
            ladd[v]+=val;
        }
    }

    void pushdown(int v,int l,int r) {
        int m=l+r>>1;
        if (lset[v] != f) {
            applyset(v*2,l,m,lset[v]);
            applyset(v*2+1,m+1,r,lset[v]);
            lset[v]=f;
        }
        if (ladd[v] != 0) {
            applyadd(v*2,l,m,ladd[v]);
            applyadd(v*2+1,m+1,r,ladd[v]);
            ladd[v]=0;
        }
    }
	
    void Set(int v,int l,int r,int ql,int qr,int val) {
        if (ql > r or qr < l) return;
        if (ql <= l and r <= qr) {
            applyset(v,l,r,val);
            return;
        }
        pushdown(v,l,r);
        int m=l+r>>1;
        Set(v*2,l,m,ql,qr,val);
        Set(v*2+1,m+1,r,ql,qr,val);
        info[v]=info[v*2]+info[v*2+1];
    }

    void Add(int v,int l,int r,int ql,int qr,int val) {
        if (ql > r or qr < l) return;
        if (ql <= l and r <= qr) {
            applyadd(v,l,r,val);
            return;
        }
        pushdown(v,l,r);
        int m=l+r>>1;
        Add(v*2,l,m,ql,qr,val);
        Add(v*2+1,m+1,r,ql,qr,val);
        info[v]=info[v*2]+info[v*2+1];
    }

	Info query(int v,int l,int r,int ql,int qr) {
		if (ql > r or qr < l) return Info();
		if (ql <= l and r <= qr) return info[v];
        pushdown(v,l,r);
		int m=l+r>>1;
		return query(2*v,l,m,ql,qr)+query(2*v+1,m+1,r,ql,qr);
	}
};
