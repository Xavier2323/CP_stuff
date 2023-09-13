//沒什麼用的BST
struct Treap {
	Treap *lc = nullptr, *rc = nullptr;
	unsigned pri, sz;
	int Key;
	Treap(int Key):pri(rand()),sz(1),Key(Key) {}
	void pull();
} *root;

inline unsigned sz(Treap *x) {
	return x ? x->sz:0;
}

inline void Treap::pull() {
	sz = 1u + ::sz(lc) + ::sz(rc);
}

inline Treap *merge(Treap *a, Treap *b) {
	if(!a || !b) return a ? a : b;
	if(a->pri < b->pri) {
		a->rc = merge(a->rc, b);
		a->pull();
		return a;
	}
	else {
		b->lc = merge(a, b->lc);
		b->pull();
		return b;
	}
}

inline pair<Treap *, Treap *> spilt(Treap *x, int Key) {
	Treap *a = nullptr, *b = nullptr;
	if(!x) return {a, b};
	if(x->Key < Key) {
		a = x;
		tie(a->rc,b) = spilt(x->rc,Key);
	}
	else {
		b = x;
		tie(a,b->lc) = spilt(x->lc,Key);
	}
	x->pull();
	return {a, b};
}

inline pair<Treap *, Treap *> spiltK(Treap *x, unsigned K) {
	Treap *a = nullptr, *b = nullptr;
	if(!x) return {a,b};
	unsigned leftSize = sz(x->lc) + 1;
	if(K >= leftSize) {
		a = x;
		tie(a->rc, b) = spiltK(x->rc, K - leftSize); 
	}
	else {
		b = x;
		tie(a,b->lc) = spiltK(x->lc, K); 
	}
	x->pull();
	return {a,b};
}

void Insert(Treap *&root, int Key) {
	auto [a,b] = spilt(root,Key);
	root = merge(a, merge(new Treap(Key),b)); 
}

Treap *&find(Treap *&root, int Key) {
	if(!root || root->Key == Key) return root;
	if(Key < root->Key) return find(root->lc,Key);
	else return find(root->rc,Key);
}

bool erase(Treap *&root, int Key) {
	Treap *&x = find(root,Key);
	if(!x) return false;
	Treap *tmp = x;
	x = merge(x->lc,x->rc);
	delete tmp;
	return true;
}

unsigned Rank(Treap *&root, int Key) {
	auto [a,b] = spilt(root, Key);
	unsigned ans = sz(a);
	root = merge(a, b);
	return ans;
}

int Kth(Treap *&root, unsigned K) {
	auto [a,b] = spiltK(root, K);
	auto [c,d] = spiltK(a,K-1);
	int ans = d->Key;
	root = merge(merge(c,d),b);
	return ans;
}
