using ll = long long;
int n;

struct node {
  node *l, *r; ll sum;
  void pull() {
    sum = 0;
    for (auto x : {l, r})
      if (x) sum += x->sum;
  }
  node(int v = 0): sum(v) {l = r = nullptr;}
} *root = nullptr;

void upd(node *prv, node* cur, int x, int v, int l = 1, int r = n) {
  if (l == r) return cur->sum = v, void();
  int m = (l + r) >> 1;
  if (x <= m) cur->r = prv->r, upd(prv->l, cur->l = new node, x, v, l, m);
  else cur->l = prv->l, upd(prv->r, cur->r = new node, x, v, m + 1, r);
  cur->pull();
}

ll qry(node* a, node* b, int ql, int qr, int l = 1, int r = n) {
  if (ql <= l && r <= qr) return b->sum - a->sum;
  int m = (l + r) >> 1; ll ret = 0;
  if (ql <= m) ret += qry(a->l, b->l, ql, qr, l, m);
  if (qr > m) ret += qry(a->r, b->r, ql, qr, m + 1, r);
  return ret;
}
