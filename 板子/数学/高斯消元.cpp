
// A为增广矩阵
// 加法:
const double eps=1e-9;
int gauss(vector<vector<double>>& A,int n,int m) {
    int row=0;
    for(int col=0;col<m;col++) {
        int r=row;
        for(int i=row+1;i<n;i++) {
            if (abs(A[i][col]) > abs(A[r][col])) r=i;
        }
        if (abs(A[r][col]) < eps) continue;
        if (r != row) swap(A[r],A[row]);

        for(int k=row+1;k<n;k++) {
            if (abs(A[k][col]) > eps) {
                double factor=A[k][col]/A[row][col];
                for(int j=col;j<=m;j++) {
                    A[k][j]-=factor*A[row][j];
                }
            }
        }
        row++;// 秩++
        if (row == n) break;// 后面几列都是自由变元
    }

    // 无解
    for(int i=row;i<n;i++) {
        if (abs(A[i][m]) > eps) return -1;
    }

    // 多解
    if (row < m) return m-row;// 返回自由变元个数

    // 唯一解
    for(int i=m-1;i>=0;i--) {
        for(int j=i+1;j<m;j++) {
            A[i][m]-=A[i][j]*A[j][m];
        }
        A[i][m]/=A[i][i];
    }
    return 0;
}

// 异或:
int gauss(vector<vector<int>>& A,int n,int m) {
    int row=0;
    for(int col=0;col<m;col++) {
        int r=row;
        while (r < n and A[r][col] == 0) r++;
        if (r == n) continue;// 这列是自由变元
        if (r != row) swap(A[r],A[row]);

        for(int k=row+1;k<n;k++) {
            if (A[k][col] == 1) {
                for(int j=col;j<=m;j++) {
                    A[k][j]^=A[row][j];
                }
            }
        }
        row++;// 秩++
        if (row == n) break;// 后面几列都是自由变元
    }
	
    // 无解
    for(int i=row;i<n;i++) {
        if (A[i][m] != 0) return -1;
    }

    // 多解
    if (row < m) return m-row;// 自由变元个数

    // 回代，唯一解
    for(int i=m-1;i>=0;i--) {
        for(int j=i+1;j<m;j++) {
            if (A[i][j]) A[i][m]^=A[j][m];
        }
    }
    return 0;
}

// Gauss-Jordan消元
	vector<bitset<1001>> A(n);
    int row=0;
    vector<int> mark(n,-1);
    for(int col=0;col<m;col++) {
        int r=row;
        while (r < n and !A[r][col]) r++;
        if (r == n) continue;
        if (r != row) swap(A[r],A[row]);
        mark[row]=col;

        for(int k=0;k<n;k++) {
            if (k != row and A[k][col]) A[k]^=A[row];
        }
        row++;
        if (row == n) break;
    }
