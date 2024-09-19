#define MOD 1'000'000'007

string cv(ll n) {
  string str(64, '0');
  for (int i = 0; i < 64; i++) {
    if ((1ll << i) & n)
      str[63 - i] = '1';
  }
  return str;
}

ll fib(ll n) {
  ll f[] = {0, 1};
  for (auto bin : cv(n)) {
    ll a = f[0]; // F(n)
    ll b = f[1]; // F(n+1)
    ll c = 2 * b - a;
    if (c < 0)
      c += MOD;
    c = a * c % MOD;              // F(2n) = F(n) * 2F(n+1) - F(n)
    ll d = (b * b + a * a) % MOD; // F(2n+1) = F(n)^2 + F(n+1)^2
    if (bin == '0') {
      f[0] = c;
      f[1] = d;
    } else {
      f[0] = d;
      f[1] = c + d;
    }
  }
  return f[0];
}
