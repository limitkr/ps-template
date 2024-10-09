#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define vt vector

// FFT
namespace FFT {
struct cmpl {
  double x, y;
  cmpl() { x = y = 0; }
  cmpl(double x, double y) : x(x), y(y) {}
  cmpl conjugated() const { return {x, -y}; }
};
inline cmpl operator+(cmpl a, cmpl b) { return {a.x + b.x, a.y + b.y}; }
inline cmpl operator-(cmpl a, cmpl b) { return {a.x - b.x, a.y - b.y}; }
inline cmpl operator*(cmpl a, cmpl b) {
  return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

int base = 1;
vt<cmpl> roots = {{0, 0}, {1, 0}};
vt<int> rev = {0, 1};
const double PI = static_cast<double>(acosl(-1.0));

void ensure_base(const int nbase) {
  if (nbase <= base)
    return;

  rev.resize(1 << nbase);
  for (int i = 1; i < 1 << nbase; i++)
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));

  roots.resize(1 << nbase);
  while (base < nbase) {
    const double angle = 2 * PI / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < 1 << base; i++) {
      roots[i << 1] = roots[i];
      const double angle_i = angle * (2 * i + 1 - (1 << base));
      roots[(i << 1) + 1] = cmpl(cos(angle_i), sin(angle_i));
    }
    base++;
  }
}

void fft(vt<cmpl> &a, int n = -1) {
  if (n == -1)
    n = static_cast<int>(a.size());

  assert((n & (n - 1)) == 0);
  const int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  const int shift = base - zeros;
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> shift))
      ranges::swap(a[i], a[rev[i] >> shift]);
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        const cmpl z = a[i + j + k] * roots[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}

vt<cmpl> fa, fb;

vt<ll> square(const vt<int> &a) {
  if (a.empty())
    return {};

  const int need = static_cast<int>(a.size()) + static_cast<int>(a.size()) - 1;
  int nbase = 1;
  while (1 << nbase < need)
    nbase++;

  ensure_base(nbase);
  const int sz = 1 << nbase;
  if (sz >> 1 > static_cast<int>(fa.size()))
    fa.resize(sz >> 1);

  for (int i = 0; i < sz >> 1; i++) {
    int x = 2 * i < static_cast<int>(a.size()) ? a[2 * i] : 0;
    int y = 2 * i + 1 < static_cast<int>(a.size()) ? a[2 * i + 1] : 0;
    fa[i] = cmpl(x, y);
  }
  fft(fa, sz >> 1);
  const cmpl r(1.0 / (sz >> 1), 0.0);
  for (int i = 0; i <= sz >> 2; i++) {
    int j = (sz >> 1) - i & (sz >> 1) - 1;
    const cmpl fe = (fa[i] + fa[j].conjugated()) * cmpl(0.5, 0);
    const cmpl fo = (fa[i] - fa[j].conjugated()) * cmpl(0, -0.5);
    cmpl aux = fe * fe + fo * fo * roots[(sz >> 1) + i] * roots[(sz >> 1) + i];
    cmpl tmp = fe * fo;
    fa[i] = r * (aux.conjugated() + cmpl(0, 2) * tmp.conjugated());
    fa[j] = r * (aux + cmpl(0, 2) * tmp);
  }
  fft(fa, sz >> 1);
  vt<ll> res(need);
  for (int i = 0; i < need; i++)
    res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);

  return res;
}

// interface
vt<ll> multiply(const vt<int> &a, const vt<int> &b) {
  if (a.empty() || b.empty())
    return {};
  if (a == b)
    return square(a);

  const int need = static_cast<int>(a.size() + b.size() - 1);
  int nbase = 1;
  while ((1 << nbase) < need)
    nbase++;
  ensure_base(nbase);
  const int sz = 1 << nbase;
  if (sz > static_cast<int>(fa.size()))
    fa.resize(sz);

  for (int i = 0; i < sz; i++) {
    const int x = i < static_cast<int>(a.size()) ? a[i] : 0;
    const int y = i < static_cast<int>(b.size()) ? b[i] : 0;
    fa[i] = cmpl(x, y);
  }
  fft(fa, sz);
  const cmpl r(0, -0.25 / (sz >> 1));
  for (int i = 0; i <= sz >> 1; i++) {
    int j = (sz - i) & (sz - 1);
    cmpl z = (fa[j] * fa[j] - (fa[i] * fa[i]).conjugated()) * r;
    fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conjugated()) * r;
    fa[i] = z;
  }
  for (int i = 0; i < sz >> 1; i++) {
    const cmpl A0 = (fa[i] + fa[i + (sz >> 1)]) * cmpl(0.5, 0);
    const cmpl A1 =
        (fa[i] - fa[i + (sz >> 1)]) * cmpl(0.5, 0) * roots[(sz >> 1) + i];
    fa[i] = A0 + A1 * cmpl(0, 1);
  }
  fft(fa, sz >> 1);
  vt<ll> res(need);
  for (int i = 0; i < need; i++)
    res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);

  return res;
}

vt<int> multiply_mod(const vt<int> &a, const vt<int> &b, const int m) {
  if (a.empty() || b.empty())
    return {};

  const int need = static_cast<int>(a.size() + b.size() - 1);
  int nbase = 0;
  while (1 << nbase < need)
    nbase++;

  ensure_base(nbase);
  const int sz = 1 << nbase;
  if (sz > static_cast<int>(fa.size()))
    fa.resize(sz);

  for (int i = 0; i < static_cast<int>(a.size()); i++) {
    int x = (a[i] % m + m) % m;
    fa[i] = cmpl(x & (1 << 15) - 1, x >> 15);
  }
  ranges::fill(fa.begin() + static_cast<int>(a.size()), fa.begin() + sz,
               cmpl{0, 0});
  fft(fa, sz);
  if (sz > static_cast<int>(fb.size()))
    fb.resize(sz);
  if (a == b)
    ranges::copy(fa.begin(), fa.begin() + sz, fb.begin());
  else {
    for (int i = 0; i < static_cast<int>(b.size()); i++) {
      const int x = (b[i] % m + m) % m;
      fb[i] = cmpl(x & (1 << 15) - 1, x >> 15);
    }
    ranges::fill(fb.begin() + static_cast<int>(b.size()), fb.begin() + sz,
                 cmpl{0, 0});
    fft(fb, sz);
  }
  const double ratio = 0.25 / sz;
  const cmpl r2(0, -1);
  const cmpl r3(ratio, 0);
  const cmpl r4(0, -ratio);
  const cmpl r5(0, 1);
  for (int i = 0; i <= sz >> 1; i++) {
    int j = sz - i & sz - 1;
    const cmpl a1 = fa[i] + fa[j].conjugated();
    const cmpl a2 = (fa[i] - fa[j].conjugated()) * r2;
    const cmpl b1 = (fb[i] + fb[j].conjugated()) * r3;
    const cmpl b2 = (fb[i] - fb[j].conjugated()) * r4;
    if (i != j) {
      const cmpl c1 = fa[j] + fa[i].conjugated();
      const cmpl c2 = (fa[j] - fa[i].conjugated()) * r2;
      const cmpl d1 = (fb[j] + fb[i].conjugated()) * r3;
      const cmpl d2 = (fb[j] - fb[i].conjugated()) * r4;
      fa[i] = c1 * d1 + c2 * d2 * r5;
      fb[i] = c1 * d2 + c2 * d1;
    }
    fa[j] = a1 * b1 + a2 * b2 * r5;
    fb[j] = a1 * b2 + a2 * b1;
  }
  fft(fa, sz);
  fft(fb, sz);
  vt<int> res(need);
  for (int i = 0; i < need; i++) {
    const ll aa = llround(fa[i].x);
    const ll bb = llround(fb[i].x);
    const ll cc = llround(fa[i].y);
    res[i] = static_cast<int>((aa + (bb % m << 15) + (cc % m << 30)) % m);
  }
  return res;
}
} // namespace FFT
