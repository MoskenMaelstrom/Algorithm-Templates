
//查找区间最大值
auto f=[&](int x) {
	
};

	int hi,lo,res; 
    if (lo > hi) return -1;
    while (hi-lo > 3) {
        int m1=lo+(hi-lo)/3;
        int m2=hi-(hi-lo)/3;
        if (f(m1) < f(m2)) lo=m1+1;
        else hi=m2-1;
    }
    res=f(lo);
    for (int i=lo+1;i<=hi;i++){
        res=max(res,f(i));
    }
