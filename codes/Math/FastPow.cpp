ll modexp(ll x, ll k, ll p) {
    ll ans = 1;
    for(int i = 1; i <= k; i <<= 1) {
        if(i & k) ans *= x, ans %= p;
        x *= x, x %= p;
    }
    return ans;
}

