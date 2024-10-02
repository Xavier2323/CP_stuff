struct line {
    ll a, b;
    line(ll _a, ll _b): a(_a), b(_b) {}
    ll operator()(ll x) {
        return a * x + b;
    }
};

bool remove(line &L1, line &L2, line &now)
{   // L1 + now remove L2 ?
    // p1_now = (now.b-L1.b)/(L1.a-now.a);
    // p2_now = (now.b-L2.b)/(L2.a-now.a);
    // return p1 >= p2
    return (now.b-L1.b)*(L2.a-now.a) >= (now.b-L2.b)*(L1.a-now.a);
}

const ll maxn = 200005;
ll s[maxn];
ll f[maxn];
ll dp[maxn];
// 斜率優化-單調對列
// Monster Game I
// https://cses.fi/problemset/task/2084/
// 斜率單調、查詢單調

int main() {	 
	ll n,m,i,k,t;
    cin >> n >> m;
    for(i=1;i<=n;i++) cin >> s[i];
    for(i=1;i<=n;i++) cin >> f[i];
    deque<line> q;
    q.push_back(line(m,0));
    for(i=1;i<=n;i++) {
        while(q.size() >= 2 && q[0](s[i]) >= q[1](s[i])) 
            q.pop_front(); 
        dp[i] = q[0](s[i]);
        line now = line(f[i],dp[i]);
        while(q.size() >= 2 && remove(q[q.size()-2],q[q.size()-1],now)) 
            q.pop_back();
        q.push_back (now);
    }
    cout << dp[n] << endl;
    return 0;
}