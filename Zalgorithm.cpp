#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6+100;

vector<int> getz(string &s){
	int n = s.length();
	vector<int> z(n, 0);
	for(int i = 1,l = 0,r = 0; i < n; ++i){
		if(i <= r && z[i - l] < r - i + 1){//如果i<=r
			z[i] = z[i - l];
		} else {
			z[i] = max(0, r - i + 1);
			while(i + z[i] < n && s[z[i]] == s[i + z[i]])z[i]++;
		}
		if(i + z[i] - 1 > r)r = i + z[i] - 1, l = i;
	}
	return z;
}

int main(){
	string s;
	cin>>s;
	vector<int>z= getz(s);
	for(auto x:z)cout<<x<<' ';	
	cout<<endl;
}