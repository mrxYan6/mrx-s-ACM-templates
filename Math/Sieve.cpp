phi[1] = 1;
for(int i = 2;i <= N;++i){
	if(!vis[i]){
		pri[++cnt] = i;
		phi[i] = i - 1;
	}
	for(int j = 1;j <= cnt && i * pri[j] <= N;++j){
		vis[i * pri[j]] = 1;
		if(i % pri[j]){
			phi[i * pri[j]] = phi[i] * (pri[j] - 1);
		}else {
			phi[i * pri[j]] = phi[i] * pri[j];
			break;
		}
	}
}