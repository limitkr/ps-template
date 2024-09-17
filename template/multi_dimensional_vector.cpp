template<int N, typename T>
struct vt : public vector<vt<N - 1, T>> {
  template<typename... Args>
  explicit vt(int n = 0, Args... args) : vector<vt<N - 1, T>>(n, vt<N - 1, T>(args...)) {}
};
template<typename T>
struct vt<1, T> : public vector<T> {
  explicit vt(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};
