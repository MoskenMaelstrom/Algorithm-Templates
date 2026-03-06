
// 求出 ax+by=gcd(a,b)的一组特解(x,y)
int exgcd(int a,int b,int &x,int &y) {
    if (!b) {
        x=1,y=0;
        return a;
    }
    int g=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return g;
}

// 求解 ax ≡ b (mod p)
int work(int a,int b,int p) {
    int x,y;
    int d=exgcd(a,p,x,y);
    if (b % d != 0) return -1; 
    int mod=p/d;//通解周期
    x=x%mod*((b/d)%mod)%mod;
    return (x+mod)%mod;
}
