// pisano number:費氏數列 mod m 
// 情況下多長會循環
// Can be proved under O(6m)
ll find_pisano(ll m) {
  ll a = 0, b = 1, c;
  for(i=0;;i++) {
    c = (a+b) % m;
    a = b; b = c;
    if(!a && b == 1)
      return i+1;
  }
}