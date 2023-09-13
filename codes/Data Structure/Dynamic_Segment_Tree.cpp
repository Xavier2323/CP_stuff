using ll = long long;
struct node {
	node *l, *r; ll sum;
	void pull() {
		sum = 0;
		for(auto x : {l, r}) if(x) sum += x->sum;
	}
	node(int v = 0): sum(v) {l = r = nullptr;}
};

void upd(node*& o, int x, ll v, int l, int r) {
	if(!o) o = new node;
	if(l == r) return o->sum += v, void();
	int m = (l + r) / 2;
	if(x <= m) upd(o->l, x, v, l, m);
	else upd(o->r, x, v, m+1, r);
	o->pull();
}

ll qry(node* o, int ql, int qr, int l, int r) {
	if(!o) return 0;
	if(ql <= l && r <= qr) return o->sum;
	int m = (l + r) / 2; ll ret = 0;
	if(ql <= m) ret += qry(o->l, ql, qr, l, m);
	if(qr > m) ret += qry(o->r, ql, qr, m+1, r);
	return ret;
}
