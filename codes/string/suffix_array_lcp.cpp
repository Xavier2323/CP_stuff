// Suffix Array: 將一字串所有後綴排序形成的array
// sa[i]: 第 i 大的後綴從哪開始 (0-index)
// rk[i]: 從 i 開始的後綴是第幾大
// lcp[i]: 第 i 和 i+1 個後綴的最長前綴長度
const int maxn = 100005; string s;
int sa[maxn], tmp[2][maxn], c[maxn];
void getSA() {
  int *x=tmp[0],*y=tmp[1],m=256,n=s.size();
  int i,k;
  for(i=0;i<m;i++) c[i] = 0;
  for(i=0;i<n;i++) c[x[i] = s[i]]++;
  for(i=1;i<m;i++) c[i] += c[i-1];
  for(i=n-1;i>=0;i--) sa[--c[x[i]]] = i;
  for(k=1;k<n;k<<=1) {
    for(i=0;i<m;i++) c[i] = 0;
    for(i=0;i<n;i++) c[x[i]]++;
    for(i=1;i<m;i++) c[i] += c[i-1];
    int p = 0;
    for(i=n-k;i<n;i++) y[p++] = i;
    for(i=0;i<n;i++)
      if(sa[i] >= k) y[p++] = sa[i]-k;
    for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]] = y[i];
    y[sa[0]] = p = 0;
    for(i=1;i<n;i++) {
      int a = sa[i], b = sa[i-1];
      if(x[a]==x[b] && a+k<n && b+k<n && x[a+k]==x[b+k]);
      else p++;
      y[sa[i]] = p;
    }
    if(n == p+1) break;
      swap(x,y), m = p+1;
  }
}
int rk[maxn], lcp[maxn];
void getLCP() {
  int n = s.size(), val = 0, i;
  for(i=0;i<n;i++) rk[sa[i]] = i;
  for(i=0;i<n;i++) {
    if(rk[i] == 0) lcp[rk[i]] = 0;
    else {
      if(val) --val;
      int p = sa[rk[i]-1];
      while(val+i<n && val+p<n && s[val+i]==s[val+p]) val++;
      lcp[rk[i]] = val;
    }
  }
}