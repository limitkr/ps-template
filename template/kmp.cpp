class KMP {
public:
  static vector<int> get_prefix(const string &s) {
    int n = static_cast<int>(s.size());
    vector<int> prefix(n);
    for (int i = 1, j = 0; i < n; i++) {
      while (j > 0 && s[i] != s[j]) j = prefix[j - 1];
      if (s[i] == s[j]) j++;
      prefix[i] = j;
    }
    return prefix;
  }

  static vector<int> search(const string &t, const string &p) {
    int n = static_cast<int>(p.size()),
        m = static_cast<int>(t.size());
    string s = p + "!" + t;
    vector<int> prefix = get_prefix(s), ans;
    for (int i = n + 1; i < n + 1 + m; i++) {
      if (prefix[i] == n) {
        ans.emplace_back(i - 2 * n);
      }
    }
    return ans;
  }
};

// Example usage
auto kmp_test() -> int32_t {
  string text = "ababcababcabc";
  string pattern = "abc";
  vector<int> occurrences = KMP::search(text, pattern);
  cout << "Pattern occurrences: ";
  for (auto pos : occurrences) {
    cout << pos << " ";
  }
  cout << '\n';
  return 0;
}
