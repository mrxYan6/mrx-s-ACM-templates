#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define ull unsigned long long
const int mod1 = 1e9+9, mod2 = 1e9+7, p = 2333, N = 1e6;
pair<ull,ull>prprv[N],prsa[N];

void getHash(string s){
	prprv[0].first=prprv[0].second=0;
	for(int i = 0; i < s.length(); ++i){
		prprv[i+1].first = (prprv[i].first * p + s[i]) % mod1;
		prprv[i+1].second = (prprv[i].second * p + s[i]) % mod2;
	}
	prsa[s.length()+1].first=prsa[s.length()+1].second=0;
	for(int i = s.length(); i; --i){
		prsa[i].first = (prsa[i+1].first * p + s[i-1]) % mod1;
		prsa[i].second = (prsa[i+1].second * p + s[i-1]) % mod2;
	}
}

bool checkParadrom(){}