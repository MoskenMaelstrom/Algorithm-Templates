
//Min-Plus求floyd最短路 固定步数的最小代价
const int inf=1e18;
vector<vector<int>> operator * (const vector<vector<int>>& A,const vector<vector<int>>& B) {
	const int n=A.size();
	vector C(n,vector<int>(n,inf));
    for (int i=0;i<n;i++) {
        for (int k=0;k<n;k++) {
        	if (A[i][k] == inf) continue;
            for (int j=0;j<n;j++) {
            	if (B[k][j] == inf) continue;
                C[i][j]=min(C[i][j],A[i][k]+B[k][j]);
            }
        }
    }
    return C;
}

vector<vector<int>> Pow(vector<vector<int>> A,int exp) {
	int n=A.size();
	vector res(n,vector<int>(n,inf));
	for(int i=0;i<n;i++) res[i][i]=0;
	while (exp) {
		if (exp&1) res=res*A;
		A=A*A;
		exp>>=1;
	}
	return res;
}
