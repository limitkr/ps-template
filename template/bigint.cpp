/**
 * BigInteger.cpp
 *
 * Big Integer Implementation
 *
 * Reference :
 * https://github.com/sgtlaugh/algovault/blob/master/code_library/bignum.cpp
 *
 * Author: sgtlaugh <https://github.com/sgtlaugh>
 *         limitkr  <https://github.com/limitkr>
 *
 * Can calculate large negative numbers
 */
#pragma GCC optimize("O3,unroll-loops")
#include <bits/extc++.h>
using namespace std;

#define FAST_IO cin.tie(nullptr)->sync_with_stdio(false)

using ll = long long;

constexpr int SIZE = 100;
constexpr int BASE_PW = 9;
constexpr ll BASE = 1000000000LL;
char tmpbuf[SIZE * BASE_PW + 10];

struct UnsignedBigInt {
  int len = 0;
  array<ll, SIZE> data{};

  ll &operator[](const int x) { return (data[x]); }
  const ll &operator[](const int x) const { return (data[x]); }

  UnsignedBigInt(const ll x = 0) {
    ranges::fill(data, 0LL);
    *this = x;
  }

  UnsignedBigInt(const string &str) {
    const int l = static_cast<int>(str.length() - 1);
    ll val = 0;
    this->clear();

    for (int i = 1; i <= (l - 1) / BASE_PW + 1; i++) {
      val = 0;
      for (int j = l - BASE_PW * i + 1; j <= l - BASE_PW * i + BASE_PW; j++) {
        if (j >= 1)
          val = val * 10 + str[j] - 48;
      }
      data[++len] = val;
    }
  }

  void clear() {
    for (int i = 1; i <= len; i++)
      data[i] = 0;
    len = 0;
  }

  static int compare(const UnsignedBigInt &a, const UnsignedBigInt &b) {
    if (a.len > b.len)
      return 0;
    if (a.len < b.len)
      return 1;

    for (int i = a.len; i >= 1; i--) {
      if (a.data[i] > b.data[i])
        return 0;
      if (a.data[i] < b.data[i])
        return 1;
    }
    return 2;
  }

  bool operator<(const UnsignedBigInt &x) const { return compare(*this, x) == 1; }
  bool operator>(const UnsignedBigInt &x) const { return compare(*this, x) == 0; }
  bool operator<=(const UnsignedBigInt &x) const { return compare(*this, x) >= 1; }
  bool operator>=(const UnsignedBigInt &x) const { return (compare(*this, x) & 1) == 0; }
  bool operator!=(const UnsignedBigInt &x) const { return compare(*this, x) != 2; }
  bool operator==(const UnsignedBigInt &x) const { return compare(*this, x) == 2; }

  UnsignedBigInt &operator=(const UnsignedBigInt &x) {
    for (int i = x.len + 1; i <= len; i++)
      data[i] = 0;
    for (int i = 1; i <= x.len; i++)
      data[i] = x.data[i];
    len = x.len;
    return *this;
  }

  UnsignedBigInt &operator=(long long x) {
    for (int i = 0; i <= len; i++)
      data[i] = 0;
    len = 0;

    do {
      data[++len] = x % BASE;
      x /= BASE;
    } while (x);
    return *this;
  }

  UnsignedBigInt operator+=(const UnsignedBigInt &b) { return *this = *this + b; }
  UnsignedBigInt operator*=(const UnsignedBigInt &b) { return *this = *this * b; }
  UnsignedBigInt operator-=(const UnsignedBigInt &b) { return *this = *this - b; }
  UnsignedBigInt operator/=(const UnsignedBigInt &b) { return *this = *this / b; }
  UnsignedBigInt operator%=(const UnsignedBigInt &b) { return *this = *this % b; }
  UnsignedBigInt operator*=(long long x) { return *this = *this * x; }
  UnsignedBigInt operator+=(long long x) { return *this = *this + x; }
  UnsignedBigInt operator-=(long long x) { return *this = *this - x; }
  UnsignedBigInt operator/=(long long x) { return *this = *this / x; }

  UnsignedBigInt operator*(const UnsignedBigInt &x) const {
    auto res = UnsignedBigInt(0LL);

    for (int i = 1; i <= len; i++) {
      for (int j = 1; data[i] && j <= x.len; j++) {
        if (x.data[j]) {
          res.data[i + j - 1] += data[i] * x.data[j];
          res.data[i + j] += res.data[i + j - 1] / BASE;
          res.data[i + j - 1] %= BASE;
        }
      }
    }

    res.len = len + x.len - 1;
    while (res.data[res.len + 1])
      res.len++;
    while (res[res.len] == 0 && res.len > 1)
      res.len--;
    return res;
  }

  UnsignedBigInt operator/(const ll x) const {
    assert(x);

    ll y = 0;
    UnsignedBigInt res;
    for (int i = len; i >= 1; i--) {
      y = y * BASE + data[i];
      res[i] = y / x;
      y %= x;
    }

    res.len = len;
    while (res[res.len] == 0 && res.len > 1)
      res.len--;
    return res;
  }

  void divide(const UnsignedBigInt &b, UnsignedBigInt &rem, UnsignedBigInt &quot) const {
    assert(!(b.len == 1 && b[1] == 0));

    ll x = data[len], y = b[b.len];
    int i, l1 = BASE_PW * (len - 1), l2 = BASE_PW * (b.len - 1);

    while (x)
      x /= 10, l1++;
    while (y)
      y /= 10, l2++;

    UnsignedBigInt temp = b;
    rem = *this;

    for (i = 1; i * BASE_PW <= (l1 - l2); i++)
      temp *= BASE;
    for (i = 1; i <= (l1 - l2) % BASE_PW; i++)
      temp *= 10;
    for (i = l1 - l2; i >= 0; i--) {
      x = 0;
      while (rem >= temp)
        rem -= temp, x++;
      quot[i / BASE_PW + 1] = quot[i / BASE_PW + 1] * 10 + x;
      temp /= 10;
    }

    quot.len = (l1 - l2) / BASE_PW + 1;
    while (rem.len > 1 && !rem[rem.len])
      rem.len--;
    while (quot.len > 1 && !quot[quot.len])
      quot.len--;
  }

  UnsignedBigInt operator/(const UnsignedBigInt &x) const {
    UnsignedBigInt rem, quot;
    divide(x, rem, quot);
    assert(quot.len > 0);
    return quot;
  }

  UnsignedBigInt operator%(const UnsignedBigInt &x) const {
    UnsignedBigInt rem, quot;
    divide(x, rem, quot);
    assert(rem.len > 0);
    return rem;
  }

  ll operator%(const ll x) const {
    ll res = 0;
    for (int i = len; i >= 1; i--)
      res = (res * BASE + data[i]) % x;
    return res;
  }

  UnsignedBigInt operator+(const UnsignedBigInt &x) const {
    UnsignedBigInt res;
    const int l = max(len, x.len);
    for (int i = 1; i <= l; i++)
      res[i] = data[i] + x[i];
    for (int i = 1; i <= l; i++)
      res[i + 1] += res[i] / BASE, res[i] %= BASE;

    res.len = l;
    if (res[res.len + 1])
      res.len++;
    while (res[res.len] == 0 && res.len > 1)
      res.len--;
    return res;
  }

  UnsignedBigInt operator-(const UnsignedBigInt &x) const {
    UnsignedBigInt res;
    for (int i = 1; i <= len; i++)
      res.data[i] = data[i] - x.data[i];
    for (int i = 1; i <= len; i++) {
      if (res[i] < 0)
        res.data[i] += BASE, res.data[i + 1]--;
    }

    res.len = len;
    while (res[res.len] == 0 && res.len > 1)
      res.len--;
    return res;
  }

  void read_bignum() {
    assert(scanf("%s", tmpbuf + 1));
    *this = UnsignedBigInt(tmpbuf);
  }

  [[nodiscard]] string to_str() const {
    if (len == 0)
      return "0";

    string s = to_string(data[len]);

    for (int i = len - 1; i >= 1; i--) {
      if (string seg = to_string(data[i]); seg.length() < BASE_PW) {
        s += string(BASE_PW - seg.length(), '0') + seg;
      } else {
        s += seg;
      }
    }
    return s;
  }
};

struct BigInt {
  int sign;
  UnsignedBigInt val;

  BigInt(const ll x = 0) {
    sign = 0;
    val = llabs(x);
    if (x < 0)
      sign = 1;
  }

  BigInt(const UnsignedBigInt &x) {
    val = x;
    sign = 0;
  }

  BigInt(const string &str) {
    if (str[0] == '-') {
      sign = 1;
    } else {
      sign = 0;
    }
    val = UnsignedBigInt(str);
  }

  BigInt &operator=(const ll x) {
    sign = 0;
    val = llabs(x);
    if (x < 0)
      sign = 1;
    return *this;
  }

  BigInt operator*(const BigInt &x) const {
    const UnsignedBigInt y = x.val;
    BigInt res;
    res.val = y * this->val;
    res.sign = this->sign ^ x.sign;
    if (res.val == UnsignedBigInt(0LL))
      res.sign = 0;
    return res;
  }

  BigInt operator/(const BigInt &x) const {
    const UnsignedBigInt y = this->val;
    BigInt res;
    res.val = y / x.val;
    res.sign = this->sign ^ x.sign;
    if (res.val == UnsignedBigInt(0LL))
      res.sign = 0;
    return res;
  }

  BigInt operator%(const BigInt &x) const {
    const UnsignedBigInt y = this->val;
    BigInt res;
    res.val = y % x.val;
    res.sign = this->sign;
    if (res.val == UnsignedBigInt(0LL))
      res.sign = 0;
    return res;
  }

  BigInt operator+(const BigInt &x) const {
    BigInt res;

    if (this->sign == x.sign) {
      res.sign = this->sign;
      res.val = this->val + x.val;
    } else {
      const UnsignedBigInt v = this->val;
      const UnsignedBigInt w = x.val;

      if (const int cmp = compare(v, w); cmp != 1) {
        res.sign = this->sign;
        res.val = v - w;
      } else {
        res.sign = x.sign;
        res.val = w - v;
      }
    }

    if (res.val == UnsignedBigInt(0LL))
      res.sign = 0;
    return res;
  }

  BigInt operator-(const BigInt &x) const {
    BigInt res = x;
    res.sign ^= 1;
    return *this + res;
  }

  static int compare(const BigInt &a, const BigInt &b) {
    if (a.sign != b.sign) {
      if (a.sign == 0)
        return 0;
      if (b.sign == 0)
        return 1;
    }

    const UnsignedBigInt x = a.val;
    const UnsignedBigInt y = b.val;
    if (a.sign == 0)
      return UnsignedBigInt::compare(x, y);
    return UnsignedBigInt::compare(y, x);
  }

  bool operator<(const BigInt &x) const { return compare(*this, x) == 1; }
  bool operator>(const BigInt &x) const { return compare(*this, x) == 0; }
  bool operator<=(const BigInt &x) const { return compare(*this, x) >= 1; }
  bool operator>=(const BigInt &x) const { return (compare(*this, x) & 1) == 0; }
  bool operator!=(const BigInt &x) const { return compare(*this, x) != 2; }
  bool operator==(const BigInt &x) const { return compare(*this, x) == 2; }

  BigInt operator+=(const BigInt &b) { return *this = *this + b; }
  BigInt operator*=(const BigInt &b) { return *this = *this * b; }
  BigInt operator-=(const BigInt &b) { return *this = *this - b; }
  BigInt operator/=(const BigInt &b) { return *this = *this / b; }
  BigInt operator%=(const BigInt &b) { return *this = *this % b; }
  BigInt operator*=(const ll x) { return *this = *this * x; }
  BigInt operator+=(const ll x) { return *this = *this + x; }
  BigInt operator-=(const ll x) { return *this = *this - x; }
  BigInt operator/=(const ll x) { return *this = *this / x; }

  void read_bignum() {
    string input;
    cin >> input;
    assert(!input.empty());

    sign = input[0] == '-';
    if (!sign) {
    } else {
      input = input.substr(1);
    }
    val = UnsignedBigInt(input);
  }

  [[nodiscard]] string to_str() const {
    string s;
    if (sign)
      s += '-';
    return s + val.to_str();
  }
};

auto main() -> int32_t {
  FAST_IO;

  // Additional Tests

  BigInt a1 = BigInt(-123);
  BigInt b1 = BigInt(-456);
  BigInt c1 = a1 + b1;
  assert(c1.to_str() == "-579");

  a1 = BigInt("-1267650600228229401496703205376");
  c1 = a1 + a1;
  assert(c1.to_str() == "-2535301200456458802993406410752");

  c1 = a1 * a1;
  assert(c1.to_str() == "1606938044258990275541962092341162602522202993782792835301376");

  // Original Tests

  BigInt x = BigInt(1);
  for (int i = 0; i < 100; i++)
    x = x * BigInt(2);
  assert(x.to_str() == "1267650600228229401496703205376");

  BigInt y = x + x;
  assert(y.to_str() == "2535301200456458802993406410752");

  BigInt r = x % 1000000007;
  assert(r.to_str() == "976371285");

  BigInt q = x / 1000000007;
  assert(q.to_str() == "1267650591354675262013");

  BigInt v = q * 1000000007 + r;
  assert(v.to_str() == "1267650600228229401496703205376");

  BigInt c = v - y;
  assert(c.to_str() == "-1267650600228229401496703205376");

  BigInt chksum = x + c;
  assert(chksum.to_str() == "0");

  constexpr auto is_equal = [](BigInt v1, int v2) -> bool { return v1.to_str() == to_string(v2); };

  for (int a = -100; a < 100; a++) {
    for (int b = -100; b < 100; b++) {
      assert(is_equal(BigInt(a) + BigInt(b), a + b));
      assert(is_equal(BigInt(a) - BigInt(b), a - b));
      assert(is_equal(BigInt(a) * BigInt(b), a * b));
      if (b) {
        assert(is_equal(BigInt(a) / BigInt(b), a / b));
        assert(is_equal(BigInt(a) % BigInt(b), a % b));
      }

      assert((a < b) == (BigInt(a) < BigInt(b)));
      assert((a > b) == (BigInt(a) > BigInt(b)));
      assert((a == b) == (BigInt(a) == BigInt(b)));
      assert((a != b) == (BigInt(a) != BigInt(b)));
      assert((a >= b) == (BigInt(a) >= BigInt(b)));
      assert((a <= b) == (BigInt(a) <= BigInt(b)));
    }
  }

  return 0;
}
