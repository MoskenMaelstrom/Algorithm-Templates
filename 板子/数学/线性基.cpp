
struct B {
	vector<int> b1(61),b2(61);
    int cnt;
    bool zero;

    void insert(int x) {
        for (int i=60;i>=0;i--) {
            if (x>>i&1) {
                if (!b1[i]) {b1[i]=x;return;}
                x^=b1[i];
            }
        }
        zero=1;
    }

    void build() {
        cnt=0;
        for (int i=60;i>=0;i--)
            for (int j=i-1;j>=0;j--)
                if (b1[i]>>j&1) b1[i]^=b1[j];
        
        for (int i=0;i<=60;i++)
            if (b1[i]) b2[cnt++]=b1[i];
    }

    int kth(int k) {
        if (zero) k--;
        if (k == 0) return 0;
        if (k >= (1LL<<cnt)) return -1;// 找不到
        
        int res=0;
        for (int i=0;i<cnt;i++)
            if (k>>i&1) res^=b2[i];
        return res;
    }
};
