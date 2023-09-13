//CSES Static Range Minimum Queries
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
vector<vector<int>> st;

void build_sparse_table(int n) {
 	st.assign(__lg(n)+1,vector<int> (n+1,inf));
	for(int i=1;i<=n;i++) cin>>st[0][i];
	for(int i=1;(1<<i)<=n;i++) {
		for(int j=1;j + (1<<i) - 1 <= n;j++) {
			st[i][j] = min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}
	}
}

int query(int l, int r) {
	int k = __lg(r - l + 1);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}

signed main() {
	int n,q;cin>>n>>q;
	build_sparse_table(n);
	while(q--) {
		int l,r;cin>>l>>r;
		cout<<query(l,r)<<'\n';
	}
}
