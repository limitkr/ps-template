template <int N, typename T>
struct Vec : vector<Vec<N - 1, T>> {
  template <typename... Args>
  explicit Vec(int n = 0, Args... args)
      : vector<Vec<N - 1, T>>(n, Vec<N - 1, T>(args...)) {}
};
template <typename T>
struct Vec<1, T> : vector<T> {
  explicit Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};
