#include <bits/stdc++.h>

// Binary GCD Algorithm
// Reference:
// https://en.wikipedia.org/wiki/Binary_GCD_algorithm
u_int32_t gcd(u_int32_t u, u_int32_t v) {
  if (u == 0)
    return v;
  if (v == 0)
    return u;
  const int uz = __builtin_ctz(u);
  const int vz = __builtin_ctz(v);
  const int shift = uz > vz ? vz : uz;
  u >>= uz;
  do {
    v >>= uz;
    u_int32_t diff = v;
    diff -= u;
    if (!diff)
      break;
    if (v < u)
      u = v;
    v = abs(static_cast<int>(diff));
  } while (true);
  return u << shift;
}

u_int32_t lcm(const u_int32_t a, const u_int32_t b) {
  return a / gcd(a, b) * b;
}
