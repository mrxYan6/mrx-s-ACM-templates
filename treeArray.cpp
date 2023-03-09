#include <iostream>
#include <vector>

using namespace std;

const int N = 5e5+100;

long long a[N];
int n;

inline int lbt(int x){return x&-x;}

void add(int pos,int val){
	for(int i = pos; i <= n; i += lbt(i))a[i]+=val;
}

long long qry(int pos){
	long long ans = 0;
	for(int i = pos; i ; i -= lbt(i))ans+=a[i];
	return ans;
}


int main(){
	cin>>n;
	memset(a,0,sizeof a);
	vector<pair<int,int>>v;
	for(int i = 1; i <= n;++i){
		int x;
		cin>>x;
		v.emplace_back(x,i);
	}
	sort(v.begin(), v.end());
	long long ans = 0;
	for(int i = 0; i < n;++i){
		add(v[i].second, 1);
		ans += i + 1 - qry(v[i].second);
	}
	cout<<ans<<endl;
}