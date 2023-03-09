#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
const int N = 1e6+100;

std::string s;

void pre(std::string &s){
	std::string tmp="~";
	tmp+=s[0];
	for(int i = 1;i<(int)s.length();++i){
		tmp+='#';
		tmp += s[i];
	}
	s  = tmp;
	//间隔插入#
}

std::vector<int> manacher(std::string &s){
	int n = s.length();
	std::vector<int>d(n);
	for(int i = 0, l = 0, r = -1; i < n; ++i){
		int k = i > r ? 1 : std::min(d[l + r - i],r - i + 1);//通过回文串中心对称性来算出当前点为中心的回文串长度
		while(k <= i && i + k < n && s[i - k] == s[i + k])k++;//特判，回文串长度比其中心点到它上一级回文串长度要大的情况
		d[i] = k--;//记录长度
		if(i + k > r){
			l = i - k;
			r = i + k;
		}
	}
	return d;
}

int main(int argc, char const *argv[])
{
	std::string s;
	std::cin>>s;
	pre(s);
	std::vector<int>d=manacher(s);
	int ans = 0;
	for(int i = 0; i < d.size(); ++i){
		if(s[i]!='#'&&d[i]%2==0)d[i]--;
		if(s[i]=='#'&&d[i]%2)d[i]--;
		ans=std::max(ans,d[i]);
	}
	std::cout<<ans<<std::endl;
	return 0;
}
