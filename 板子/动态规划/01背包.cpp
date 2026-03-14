
	// 经典01背包
	for(int i=1;i<=n;i++) {
		for(int j=T;j>=b[i];j--) {
			dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
		}
	}


	// 二维费用背包,有两个约束条件,要求最后只能选k个,总容量>=sum
	int T=0;
	for(int i=1;i<=n;i++) T+=b[i];
	vector dp(n+1,vector<int>(T+1,-1));// 因为容量有要求,所以需要-1代表不可达
	dp[0][0]=0;
	for(int i=1;i<=n;i++) {
		for(int j=i;j>=1;j--) {
			for(int c=T;c>=b[i];c--) {
				if (dp[j-1][c-b[i]] < 0) continue;
				dp[j][c]=max(dp[j][c],dp[j-1][c-b[i]]+b[i]);
			}
		}
	}
	cout<<*max_element(dp[k].begin()+sum,dp[k].end());
