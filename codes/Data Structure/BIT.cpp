//迭代

int n;
int bit[100000 + 9];
void modify(int i, int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & -i;
    }
}
int query(int i) {
    int res = 0;
    while (i) {
        res += bit[i];
        i -= i & -i;
    }
    return res;
}

//bit上二分搜
int findk(int k) {
    int id = 0, res = 0;
    int mx = __lg(n) + 1;
    for (int i = mx; i >= 0; i--) {
        if ((id | (1<<i)) > n) continue;
        if (res + b[id|(1<<i)] < k) { 
            id = (id | (1<<i));
            res += b[id];
        }
    }
    return id + 1;
}

//O(n)建bit
for (int i = 1; i <= n; ++i) {
    bit[i] += a[i];
    int j = i + lowbit(i);
    if (j <= n) bit[j] += bit[i];
}

