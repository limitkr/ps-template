using ll = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;


array base_prime{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

u64 powmod(u64 base, u64 e, u64 mod) {
  u128 res = 1;
  base %= mod;
  while (e) {
    if (e & 1)
      res = res * base % mod;
    base = static_cast<u128>(base) * base % mod;
    e >>= 1;
  }
  return res;
}

bool is_composite(u64 n, u64 a, u64 d, int s) {
  u64 x = powmod(a, d, n);
  if (x == 1 || x == n - 1)
    return false;
  for (int r = 1; r < s; r++) {
    x = static_cast<u128>(x) * x % n;
    if (x == n - 1)
      return false;
  }
  return true;
}

bool mr(const u64 n) {
  if (n < 2)
    return false;
  int r = 0;
  u64 d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
    r++;
  }
  for (auto p : base_prime) {
    if (n == p)
      return true;
    if (is_composite(n, p, d, r))
      return false;
  }
  return true;
}

u128 mult(ll a, ll b, ll mod) { return static_cast<u128>(a) * b % mod; }

ll f(ll x, ll c, ll mod) { return (mult(x, x, mod) + c) % mod; }

ll rho(const ll n) {
  if (n % 2 == 0)
    return 2;
  if (mr(n))
    return n;
  ll x = rand() % n + 1, c = rand() % n + 1;
  ll y = x, g = 1;
  while (g == 1) {
    x = f(x, c, n);
    y = f(y, c, n);
    y = f(y, c, n);
    g = gcd(abs(x - y), n);
    if (g == n)
      return rho(g);
  }
  if (mr(g))
    return g;
  return rho(g);
}
