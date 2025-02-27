using ld = long double;

// Convex hull using the Monotone Chain algorithm
// Complexity: O(N log N)
// Reference:
// https://github.com/sgtlaugh/algovault/blob/master/code_library/convex_hull.cpp
namespace ConvexHull {
struct Point {
  ld x, y;
  explicit Point(const ld x = 0, const ld y = 0) : x(x), y(y) {}
  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
  ld operator*(const Point &p) const { return x * p.y - y * p.x; }
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  [[nodiscard]] ld dot(const Point &p) const { return x * p.x + y * p.y; }
  [[nodiscard]] ld norm() const { return hypot(x, y); }
};

ld ccw(const Point &a, const Point &b, const Point &c) { return (b - a) * (c - a); }
ld cross(const Point &O, const Point &A, const Point &B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> get_convex_hull(vector<Point> &P, bool checkOnHullEdge = true) {
  int k = 0;
  const int n = static_cast<int>(P.size());
  vector<Point> H(n << 1);
  sort(P.begin(), P.end());

  for (int i = 0; i < n; i++) {
    while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) < (checkOnHullEdge ? 0 : 1)) {
      k--;
    }
    H[k++] = P[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && cross(H[k - 2], H[k - 1], P[i]) < (checkOnHullEdge ? 0 : 1)) {
      k--;
    }
    H[k++] = P[i];
  }
  H.resize(k - 1);
  return H;
}

Point rotate(const Point &p, const ld angle) {
  const ld c = cos(angle);
  const ld s = sin(angle);
  return Point{p.x * c - p.y * s, p.x * s + p.y * c};
}
}
