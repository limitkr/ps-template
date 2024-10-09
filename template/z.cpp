#include <bits/stdc++.h>
using namespace std;

#define vt vector

/**
 * Z Algorithm in O(n)
 * Reference:
 * https://github.com/sgtlaugh/algovault/blob/master/code_library/python/z_algorithm.py
 */
vt<int> Z(const string &s) {
  const int n = static_cast<int>(s.size());
  vt<int> res(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    int z = res[i - l];
    if (i + z >= r) {
      z = ranges::max(r - i, 0);
      while (i + z < n && s[z] == s[i + z])
        z++;
      l = i;
      r = i + z;
    }
    res[i] = z;
  }
  res[0] = n;
  return res;
}
