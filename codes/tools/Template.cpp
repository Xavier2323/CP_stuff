#include <bits/extc++.h>
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long
#define double long double
#define pb push_back
#define sz(x) (int)(x).size()
#define all(v) begin(v),end(v)
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
#define LINE cout<<"\n-----------------\n"
#define endl '\n'
#define VI vector<int>
#define F first
#define S second
#define MP(a,b) make_pair(a,b)
#define rep(i,m,n) for(int i = m;i<=n;++i)
#define res(i,m,n) for(int i = m;i>=n;--i)
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) a*b/gcd(a,b)
#define Case() int _;cin>>_;for(int Case = 1;Case<=_;++Case)
#define pii pair<int,int>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
template <typename K, typename cmp = less<K>, typename T = thin_heap_tag> using _heap = __gnu_pbds::priority_queue<K, cmp, T>;
template <typename K, typename M = null_type> using _hash = gp_hash_table<K, M>;
const int N = 1e6+5,L = 20,mod = 1e9+7;
const long long inf = 2e18+5;
const double eps = 1e-7,pi = acos(-1);
void solve(){
}
signed main(){
	IOS;
	solve();
}

//使用內建紅黑樹
template<class T, typename cmp=less<>>struct _tree{//#include<bits/extc++.h>
	tree<pair<T,int>,null_type,cmp,rb_tree_tag,tree_order_statistics_node_update>st;
	int id = 0;
	void insert(T x){st.insert({x,id++});}
	void erase(T x){st.erase(st.lower_bound({x,0}));}
	int order_of_key(T x){return st.order_of_key(*st.lower_bound({x,0}));}
	T find_by_order(int x){return st.find_by_order(x)->first;}
	T lower_bound(T x){return st.lower_bound({x,0})->first;}
	T upper_bound(T x){return st.upper_bound({x,(int)1e9+7})->first;}
	T smaller_bound(T x){return (--st.lower_bound({x,0}))->first;}
};
