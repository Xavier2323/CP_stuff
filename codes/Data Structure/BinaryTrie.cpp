template<class T>
struct binary_trie {
public:
	binary_trie() {
		new_node();
	}

	void clear() {
		trie.clear();
		new_node();
	}

	void insert(T x) {
		for(int i = B - 1, p = 0; i >= 0; i--) {
			int y = x >> i & 1;
			if(trie[p].go[y] == 0) {
				trie[p].go[y] = new_node();
			}
			p = trie[p].go[y];
			trie[p].cnt += 1;
		}
	}

	void erase(T x) {
		for(int i = B - 1, p = 0; i >= 0; i--) {
			p = trie[p].go[x >> i & 1];
			trie[p].cnt -= 1;
		}
	}

	bool contains(T x) {
		for(int i = B - 1, p = 0; i >= 0; i--) {
			p = trie[p].go[x >> i & 1];
			if(trie[p].cnt == 0) {
				return false;
			}
		}
		return true;
	}

	T get_min() {
		return get_xor_min(0);
	}

	T get_max() {
		return get_xor_max(0);
	}

	T get_xor_min(T x) {
		T ans = 0;
		for(int i = B - 1, p = 0; i >= 0; i--) {
			int y = x >> i & 1;
			int z = trie[p].go[y];
			if(z > 0 && trie[z].cnt > 0) {
				p = z;
			} else {
				ans |= T(1) << i;
				p = trie[p].go[y ^ 1];
			}
		}
		return ans;
	}

	T get_xor_max(T x) {
		T ans = 0;
		for(int i = B - 1, p = 0; i >= 0; i--) {
			int y = x >> i & 1;
			int z = trie[p].go[y ^ 1];
			if(z > 0 && trie[z].cnt > 0) {
				ans |= T(1) << i;
				p = z;
			} else {
				p = trie[p].go[y];
			}
		}
		return ans;
	}

private:
	static constexpr int B = sizeof(T) * 8;

	struct Node {
		std::array<int, 2> go = {};
		int cnt = 0;
	};

	std::vector<Node> trie;

	int new_node() {
		trie.emplace_back();
		return (int) trie.size() - 1;
	}
};
