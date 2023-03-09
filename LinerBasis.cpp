#include <vector>
const int N = 61;

struct LinearBasis
{
	std::vector<long long> p, d;
	int cnt;
	LinearBasis(){
		p.clear();
		d.clear();
		d.resize(N,0);
		cnt = 0;
	}

	bool ins(long long x){
		for(int i = 60; i >= 0; --i){
			if(1&(x>>i)){
				if(!d[i]){
					d[i] = x;
					break;
				}
				x ^= d[i];
			}
		}
		return x != 0;
	}

	void rebuild(){
		for(int i = 60; i >=0; --i){
			for(int j = i - 1; j >= 0; --j){
				if(1&(d[i]>>j)){
					d[i]^=d[j];
				}
			}
		}
		for(int i = 0; i <= 60; ++i){
			if(d[i])p.push_back(d[i]);
		}
	}

	long long qry_max(){
		long long ret = 0;
		for (int i = 60;i >= 0;i--)
            if ((ret^d[i])>ret)
                ret^=d[i];
        return ret;
	}

	long long qry_min(){
		for (int i=0;i<=60;i++)
            if (d[i])
                return d[i];
        return 0;
	}


	long long qry_kth(long long k){
		long long ret = 0;
		if(k>=(1ll<<cnt))return -1;
		for(int i = 0; i < p.size(); ++i){
			if(1&(k>>i))ret ^= p[i];
		}
		return ret;
	}
};

LinearBasis merge(const LinearBasis &lhs,const LinearBasis &rhs){
	LinearBasis ans = lhs;
	for(int i = 60; i >= 0; --i){
		if(rhs.d[i]){
			ans.ins(rhs.d[i]);
		}
	}
	return ans;
}