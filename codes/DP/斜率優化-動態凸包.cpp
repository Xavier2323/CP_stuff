struct Line
{
    mutable ll a, b, l;
    Line(ll _a, ll _b, ll _l) : a(_a), b(_b), l(_l) {}
    bool operator<(const Line &rhs) const
    {
        return make_pair(-a, -b) < make_pair(-rhs.a, -rhs.b);
    }
    bool operator<(ll rhs_l) const
    {
        return l < rhs_l;
    }
};

struct ConvexHullMin : std::multiset<Line, std::less<>>
{
    static const ll INF = (1ll << 60);
    static ll DivCeil(ll a, ll b)
    {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool Intersect(iterator x, iterator y)
    {
        if (y == end())
        {
            x->l = INF;
            return false;
        }
        if (x->a == y->a)
        {
            x->l = x->b < y->b ? INF : -INF;
        }
        else
        {
            x->l = DivCeil(y->b - x->b, x->a - y->a);
        }
        return x->l >= y->l;
    }
    void Insert(ll a, ll b)
    {
        auto z = insert(Line(a, b, 0)), y = z++, x = y;
        while (Intersect(y, z))
            z = erase(z);
        if (x != begin() && Intersect(--x, y))
            Intersect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->l >= y->l)
            Intersect(x, erase(y));
    }
    ll query(ll x) const
    {
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
} convexhull;

const ll maxn = 200005;
ll s[maxn];
ll f[maxn];
ll dp[maxn];
// CSES monster game2
int main()
{   Crbubble
    ll n,m,i,k,t;
    cin >> n >> f[0];
    for(i=1;i<=n;i++) cin >> s[i];
    for(i=1;i<=n;i++) cin >> f[i];
    convexhull.Insert(f[0],0);
    for(i=1;i<=n;i++)
    {
        dp[i] = convexhull.query(s[i]);
        convexhull.Insert(f[i],dp[i]);
    }
    cout << dp[n] << endl;
    return 0;
}
