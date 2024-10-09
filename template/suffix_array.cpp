#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define vt vector

vt<int> build_suffix_arr(const string &s) {
  const auto n = s.size();
  vt<int> suffix_arr(n), ranks(n), temp_ranks(n);
  for (int i = 0; i < n; i++) {
    suffix_arr[i] = i;
    ranks[i] = s[i] - '0';
  }
  for (int len = 1; len < n; len *= 2) {
    auto compare = [&](int i, int j) {
      if (ranks[i] != ranks[j])
        return ranks[i] < ranks[j];
      int ri = i + len < n ? ranks[i + len] : -1;
      int rj = j + len < n ? ranks[j + len] : -1;
      return ri < rj;
    };
    ranges::sort(suffix_arr, compare);
    temp_ranks[suffix_arr[0]] = 0;
    for (int i = 1; i < n; i++)
      temp_ranks[suffix_arr[i]] = temp_ranks[suffix_arr[i - 1]] +
                                  compare(suffix_arr[i - 1], suffix_arr[i]);
    ranks = temp_ranks;
  }
  return suffix_arr;
}
