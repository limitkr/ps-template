#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define vt vector

// No Pre-Generate Version
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
vt<char> sieve(ll L, ll R) {
  vt<char> isPrime(R - L + 1, true);
  ll lim = sqrt(R);
  for (ll i = 2; i <= lim; i++) {
    for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
      isPrime[j - L] = false;
  }
  if (L == 1)
    isPrime[0] = false;
  return isPrime;
}
