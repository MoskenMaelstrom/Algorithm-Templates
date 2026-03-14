
	// 经典01背包
	for(int i=1;i<=n;i++) {
		for(int j=T;j>=b[i];j--) {
			dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
		}
	}


	// 有限制的01背包,要求最后只能选k个,并且对背包大小有要求(>=sum)
	int T=0;
	for(int i=0;i<n;i++) T+=b[i];
	vector dp(n+1,vector<int>(T+1,0));
	for(int i=1;i<=n;i++) {
		for(int j=i;j>=1;j--) {
			for(int c=T;c>=b[i];c--) {
				dp[j][c]=max(dp[j][c],dp[j-1][c-b[i]]+a[i]);
			}
		}
	}
	cout<<*max_element(dp[k].begin()+sum,dp[k].end());
