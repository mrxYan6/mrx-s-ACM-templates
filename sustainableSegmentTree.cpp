#include <iostream>
#include <vector>
#include <algorithm>

const int N = 1e5+10;
using namespace std;
struct sustainableSegmentTree{
    int ls, rs, val;
}T[N<<5];
int n,m,tot,rt[N],a[N];
int build(int l,int r){
    int root = ++tot;
    if(l == r)return root;
    int m = l + r >> 1;
    T[root].val = 0;
    T[root].ls = build(l, m);
    T[root].rs = build(m + 1, r);
}

int upd(int k, int l, int r,int root){
    int dir = ++tot;
    T[dir].ls = T[root].ls, T[dir].rs = T[root].rs;
    T[dir].val = T[root].val + 1;
    if(l == r)return dir;
    int m = l + r >> 1;
    if(k <= m)T[dir].ls = upd(k, l , m, T[dir].ls);
    else T[dir].rs = upd(k, m + 1, r, T[dir].rs);
    return dir;
}

int qry(int u,int v,int l, int r, int k){
    int m = l + r >> 1;
    int x = T[T[v].ls].val - T[T[u].ls].val;
    if(l == r)return l;
    if (k <= x)return qry(T[u].ls,T[v].ls,l,m,k);
    else return qry(T[u].rs,T[v].rs,m+1,r,k-x);
}
int main(int argc, char const *argv[])
{
    tot = 0;
    cin>> n>> m;
    std::vector<int> lsh;
    for(int i  = 1; i <= n; ++i){
        cin>>a[i];
        lsh.push_back(a[i]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()),lsh.end());
    int len = lsh.size();
    rt[0]=build(1,len);
    for(int i = 1; i <= n; ++i){
        rt[i]=upd(lower_bound(lsh.begin(), lsh.end(),a[i])-lsh.begin()+1,1,len,rt[i-1]);
    }
    while(m--){
        int l ,r, k;
        cin>>l>>r>>k;
        cout<<lsh[qry(rt[l-1],rt[r],1,len,k)-1]<<endl;
    }
    return 0;
}