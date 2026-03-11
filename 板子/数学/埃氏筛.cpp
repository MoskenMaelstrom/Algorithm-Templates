
	vector<bool> isp(N+1,1);
	isp[0]=isp[1]=0;
	for(int i=2;i<=n;i++) {
		if (!isp[i]) continue;
		for(int j=i;i*j<=n;j++) isp[i*j]=0;
	}
	