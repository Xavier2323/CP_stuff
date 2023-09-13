

struct Treap {
	Treap *lc = nullptr, *rc = nullptr;
	unsigned pri, sz;
	long long Val, Sum;
	Treap(int Val):pri(rand()),sz(1),Val(Val),Sum(Val),Tag(false) {}
	void pull();
	bool Tag;
	void push();
} *root;

inline unsigned sz(Treap *x) {
	return x ? x->sz:0;
}

inline void Treap::push() {
	if(!Tag) return ;
	swap(lc,rc);
	if(lc) lc->Tag ^= Tag;
	if(rc) rc->Tag ^= Tag;
	Tag = false;
}

inline void Treap::pull() {
	sz = 1;
	Sum = Val;
	if(lc) {
		sz += lc->sz;
		Sum += lc->Sum;
	}
	if(rc) {
		sz += rc->sz;
		Sum += rc->Sum;
	}
}

Treap *merge(Treap *a, Treap *b) {
	if(!a || !b) return a ? a : b;
	if(a->pri < b->pri) {
		a->push();
		a->rc = merge(a->rc,b);
		a->pull();
		return a;
	}
	else {
		b->push();
		b->lc = merge(a,b->lc);
		b->pull();
		return b;
	}
}

pair<Treap *,Treap *> splitK(Treap *x, unsigned K) {
	Treap *a = nullptr, *b = nullptr;
	if(!x) return {a,b};
	x->push();
	unsigned leftSize = sz(x->lc) + 1;
	if(K >= leftSize) {
		a = x;
		tie(a->rc,b) = splitK(x->rc, K - leftSize);
	}
	else {
		b = x;
		tie(a, b->lc) = splitK(x->lc, K);
	}
	x->pull();
	return {a,b};
}

Treap *init(const vector<int> &a) {
	Treap *root = nullptr;
	for(size_t i = 0;i < a.size(); i++) {
		root = merge(root,new Treap(a[i]));
	}
	return root;
}

long long query(Treap *&root, unsigned ql, unsigned qr) {
	auto [a,b] = splitK(root,ql);
	auto [c,d] = splitK(b,qr-ql+1);
	c->push();
	long long Sum = c->Sum;
	root = merge(a,merge(c,d));
	return Sum;
}

void Reverse(Treap *&root, unsigned ql, unsigned qr) {
	auto [a,b] = splitK(root,ql);
	auto [c,d] = splitK(b,qr-ql+1);
	c->Tag ^= true;
	root = merge(a, merge(c,d));
}
