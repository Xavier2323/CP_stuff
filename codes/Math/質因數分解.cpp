//CSES Counting Divisors
#include<bits/stdc++.h>
using namespace std;
 
int n;
 
vector<int> primes;
vector<int> LPs;
 
void sieve(int n) {
    LPs.assign(n+1,1);
    for(int i=2;i<n;i++) {
        if(LPs[i]==1) {
          primes.emplace_back(i);
          LPs[i] = i;
        }
        for(auto p:primes) {
            if(1LL*i*p > n) break;
            LPs[i*p] = p;
            if(i%p==0) break;
        }
    }
}
 
signed main() {
    cin>>n;
    sieve((int)1e6);
  	map<int,int> divisor;
    while(n--) {
      	divisor.clear();
        int x;cin>>x;
  	    while(x>1) {
    	    divisor[LPs[x]]++;
      	    x/=LPs[x];
        }
      	int ans = 1;
     	for(auto &[x,y] : divisor) ans *= (y+1);
      	cout<<ans;
        cout<<'\n';
    }
}
