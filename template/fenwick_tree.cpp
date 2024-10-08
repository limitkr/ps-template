const int maxN = 1e6; // Modify this
int BIT[maxN];
int N;

void update(int x, int val) {
  ++x;
  while (x <= N) {
    BIT[x] += val;
    x += x & -x;
  }
}

int query(int x) {
  ++x;
  int res = 0;
  while (x > 0) {
    res += BIT[x];
    x -= x & -x;
  }
  return res;
}
