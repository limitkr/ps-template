#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define vt vector

ll _euler_totient(ll n, ll ps) {
  for (ll i = ps; i * i <= n; i++) {
    if (n % i == 0) {
      ll p = 1;
      while (n % i == 0) {
        n /= i;
        p *= i;
      }
      return (p - p / i) * _euler_totient(n, i + 1);
    }
    if (i > 2)
      i++;
  }
  return n - 1;
}

ll euler_totient(ll n) { return _euler_totient(n, 2); }
