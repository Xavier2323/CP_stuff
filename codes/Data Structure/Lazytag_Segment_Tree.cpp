using ll = long long;
const int N = 2e5 + 5;
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
ll seg[N << 2], tag[N << 2];
int n;

void pull(int id) {
  seg[id] = seg[lc(id)] + seg[rc(id)];
}

void push(int id, int l, int r) {
  if (tag[id]) {
    int m = (l + r) >> 1;
    tag[lc(id)] += tag[id], tag[rc(id)] += tag[id];
    seg[lc(id)] += (m - l + 1) * tag[id], seg[rc(id)] += (r - m) * tag[id];
    tag[id] = 0;
  }
}

void upd(int ql, int qr, ll v, int l = 1, int r = n, int id = 1) {
  if (ql <= l && r <= qr) return tag[id] += v, seg[id] += (r - l + 1) * v, void();
  push(id, l, r);
  int m = (l + r) >> 1;
  if (ql <= m) upd(ql, qr, v, l, m, lc(id));
  if (qr > m) upd(ql, qr, v, m + 1, r, rc(id));
  pull(id);
}

ll qry(int ql, int qr, int l = 1, int r = n , int id = 1) {
  if (ql <= l && r <= qr) return seg[id];
  push(id, l, r);
  int m = (l + r) >> 1; ll ret = 0;
  if (ql <= m)  ret += qry(ql, qr, l, m, lc(id));
  if (qr > m) ret += qry(ql, qr, m + 1, r, rc(id));
  return ret;
}
