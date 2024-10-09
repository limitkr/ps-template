#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define vt vector

vt<char> sieve(const ll L, const ll R) {
  const ll lim = static_cast<ll>(sqrt(R));
  vt<char> mark(lim + 1, false);
  vt<ll> primes;
  for (ll i = 2; i <= lim; i++) {
    if (!mark[i]) {
      primes.emplace_back(i);
      for (ll j = i * i; j <= lim; j += i)
        mark[j] = true;
    }
  }
  vt<char> is_prime(R - L + 1, true);
  for (const auto i : primes)
    for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
      is_prime[j - L] = false;
  if (L == 1)
    is_prime[0] = false;
  return is_prime;
}
