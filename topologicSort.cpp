
void topo(){
	for(int i = 1; i <= n; ++i){
		if(in[i]==0)Q.push(i);
	}
	while(!Q.empty()){
		auto now = Q.front();
		Q.pop();
		if(w[now]<0)w[now]=0;
		for(auto x : G[now]){
			int v = x.first;
			int ww = x.second;
			in[v]--;
			if(in[v]==0)Q.push(v);
			w[v] += ww * w[now];
		}
	}
}