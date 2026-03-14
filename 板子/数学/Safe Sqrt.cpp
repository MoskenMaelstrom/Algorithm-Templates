
int Sqrt(int n) {
    int x=sqrt(n);
    if (x*x > n) {
        x--;
    }
    return x;
}
