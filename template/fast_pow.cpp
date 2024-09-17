template <typename T> static constexpr T pow(T x, unsigned p) {
  T res = 1;
  while (p) {
    if (p & 0x1)
      res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}
