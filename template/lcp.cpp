#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define vt vector

vt<int> build_lcp(const string &s, const vt<int> &suffix_arr) {
  auto n = s.size();
  vt<int> rank(n), lcp(n);
  for (int i = 0; i < n; i++)
    rank[suffix_arr[i]] = i;
  int h = 0;
  for (int i = 0; i < n; i++) {
    if (rank[i] > 0) {
      int j = suffix_arr[rank[i] - 1];
      while (i + h < n && j + h < n && s[i + h] == s[j + h])
        h++;
      lcp[rank[i]] = h;
      if (h > 0)
        h--;
    }
  }
  return lcp;
}
