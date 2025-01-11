struct FenwickTree {
  int sz;
  vt<int> BIT;
  explicit FenwickTree(const int _sz) : sz(_sz) { BIT.assign(sz + 1, 0); }

  void update(int x, const int val) {
    ++x;
    while (x <= N) {
      BIT[x] += val;
      x += x & -x;
    }
  }

  int query(int x) const {
    ++x;
    int res = 0;
    while (x > 0) {
      res += BIT[x];
      x -= x & -x;
    }
    return res;
  }
};
