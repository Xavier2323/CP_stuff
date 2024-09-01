#define ull unsigned long long
#define ldb long double

vector<ll> factor;
vector<pair<ll,ll>> fac;

ll fpow(ll x, ll y, ll p) {
  ll res = 1;
  while (y) {
    if (y & 1) res = (__int128)res * x % p;
    x = (__int128)x * x % p;
    y >>= 1;
  }
  return res;
}

bool mr(ll x, ll p) {
  if (fpow(x, p - 1, p) != 1) return 0;
  ll y = p - 1, z;
  while (!(y & 1)) {
    y >>= 1;
    z = fpow(x, y, p);
    if (z != 1 && z != p - 1) return 0;
    if (z == p - 1) return 1;
  }
  return 1;
}

// Miller Rabin ~O(log p)
bool is_prime(ll p) {
  if (p < 2) return 1;
  if (p==2 || p==3 || p==5 || p==7 || p==43) return 1;
  return mr(2,p) && mr(3,p) && mr(5,p) && mr(7,p) && mr(43,p);
}

// O(1) 快速乘(防ll overflow)
ll ksc(ull x, ull y, ll p) {   
  return (x*y-(ull)( (ldb)x/p*y)*p+p)%p;
}

//求n任一真因數(需保證n非質數) O(n^1/4)
ll pollar_rho(ll n) {   
  ll x,y,z,c,g,i,j;
  while(1) {
    x = y = rand()%n;
    z = 1;
    c = rand()%n;
    i = 0, j = 1;
    while(++i) {
      x = (ksc(x,x,n) + c)%n;
      z = ksc(z,abs(y-x),n);
      if(x == y || !z) break;
      if(!(i%127) || i == j) {
        g = __gcd(z,n);
        if(g > 1) return g;
        if(i == j) y = x, j <<= 1;
      }
    }
  }
}

void factorization(ll n) { 
  while(!is_prime(n)) {
    ll f = pollar_rho(n);
    while(!is_prime(f)) {
      f = pollar_rho(f);
    }
    ll cou = 0;
    while(n%f == 0) n /= f, cou++;
    fac.push_back({f,cou});
  }
  if(n != 1) fac.push_back({n,1});
}
 
void get_factors(ll now, ll cou) {
  if(now >= fac.size()) {
    factor.push_back(cou);
    return;
  }
  get_factors(now+1,cou);
  for(ll i=1;i<=fac[now].second;i++) {
    cou *= fac[now].first;
    get_factors(now+1,cou);
  }
}