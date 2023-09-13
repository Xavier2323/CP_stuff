//CSES Area of Rectangle
#include <bits/stdc++.h>
#define pb push_back
#define int long long
#define mid ((l + r) >> 1)
#define lc (p << 1)
#define rc ((p << 1) | 1)
using namespace std;
struct ooo{
    int x, l, r, v;
};
const int inf = 1e6;
array<int, 8000004> man, tag, cnt;
vector<ooo> Q;
bool cmp(ooo a, ooo b){
    return a.x < b.x;
}
void pull(int p){
    man[p] = min(man[lc], man[rc]);
    if(man[lc] < man[rc]) cnt[p] = cnt[lc];
    else if(man[rc] < man[lc]) cnt[p] = cnt[rc];
    else cnt[p] = cnt[lc] + cnt[rc];
}
void push(int p){
    man[lc] += tag[p];
    man[rc] += tag[p];
    tag[lc] += tag[p];
    tag[rc] += tag[p];
    tag[p] = 0;
}
void build(int p, int l, int r){
    if(l == r){
        cnt[p] = 1;
        return;
    }
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pull(p);
}
void update(int p, int l, int r, int ql, int qr, int x){
    if(ql > r || qr < l) return;
    if(ql <= l && qr >= r){
        man[p] += x;
        tag[p] += x;
        return;
    }
    push(p);
    update(lc, l, mid, ql, qr, x);
    update(rc, mid + 1, r, ql, qr, x);
    pull(p);
}
signed main(){
    int n, x1, y1, x2, y2, p = 0, sum = 0;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        Q.pb({x1, y1, y2 - 1, 1});
        Q.pb({x2, y1, y2 - 1, -1});
    }
    sort(Q.begin(), Q.end(), cmp);
    build(1, -inf, inf);
    for(int i = -inf; i < inf; i++){
        while(p < Q.size() && Q[p].x == i){
            auto [x, l, r, v] = Q[p++];
            update(1, -inf, inf, l, r, v);
        }
        sum += 2 * inf + 1 - cnt[1];
    }
    cout << sum << "\n";
    return 0;
}
//長方形面積
long long AreaOfRectangles(vector<tuple<int,int,int,int>>v){
	vector<tuple<int,int,int,int>>tmp;
	int L = INT_MAX,R = INT_MIN;
	for(auto [x1,y1,x2,y2]:v){
		tmp.push_back({x1,y1+1,y2,1});
		tmp.push_back({x2,y1+1,y2,-1});
		R = max(R,y2);
		L = min(L,y1);
	}
	vector<long long>seg((R-L+1)<<2),tag((R-L+1)<<2);
	sort(tmp.begin(),tmp.end());
	function<void(int,int,int,int,int,int)>update = [&](int ql,int qr,int val,int l,int r,int idx){
		if(ql<=l and r<=qr){
			tag[idx]+=val;
			if(tag[idx])seg[idx] = r-l+1;
			else if(l==r)seg[idx] = 0;
			else seg[idx] = seg[idx<<1]+seg[idx<<1|1];
			return;
		}
		int m = (l+r)>>1;
		if(ql<=m)update(ql,qr,val,l,m,idx<<1);
		if(qr>m)update(ql,qr,val,m+1,r,idx<<1|1);
		if(tag[idx])seg[idx] = r-l+1;
		else seg[idx] = seg[idx<<1]+seg[idx<<1|1];
	};
	long long last_pos = 0,ans = 0;
	for(auto [pos,l,r,val]:tmp){
		ans+=(pos-last_pos)*seg[1];
		update(l,r,val,L,R,1);
		last_pos = pos;
	}
	return ans;
}

// CSES Intersection Points
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
struct line{
    int p, l, r;
};
const int inf = 1e6 + 1;
array<int, 2000004> BIT;
vector<line> A, Q;
bool cmp(line a, line b){
    return a.p < b.p;
}
void update(int p, int x){
    for(; p < 2000004; p += p & -p) BIT[p] += x;
}
int query(int p){
    int sum = 0;
    for(; p; p -= p & -p) sum += BIT[p];
    return sum;
}
int run(){
    int ans = 0, p = 0;
    for(auto [t, l, r] : Q){
        while(p < A.size()){
            auto [x, y, v] = A[p];
            if(x > t) break;
            update(y, v);
            p++;
        }
        ans += query(r) - query(l - 1);
    }
    return ans;
}
signed main(){
    int n, x1, x2, y1, y2;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += inf, x2 += inf, y1 += inf, y2 += inf;
        if(x1 == x2) Q.pb({x1, y1, y2});
        else A.pb({x1, y1, 1}), A.pb({x2 + 1, y2, -1});
    }
    sort(Q.begin(), Q.end(), cmp);
    sort(A.begin(), A.end(), cmp);
    cout << run() << "\n";
    return 0;
}
