#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <type_traits>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include <Rcpp.h>
using namespace Rcpp;

template <typename Func, typename param>
double golden(
    Func func,
    double a,
    double b,
    double c,
    double tol,
    const param& params)
{
  const double r1 = 0.61803399;
  const double r2 = 1.0 - r1;
  double x0 = a, x3 = c;
  double x1, x2;
  if (std::fabs(c - b) <= std::fabs(b - a)) {
    x1 = b;
    x2 = b + r2 * (c - b);
  } else {
    x2 = b;
    x1 = b - r2 * (b - a);
  }

  // Helper to call f with correct number of arguments
  auto call_func = [&](double xx) -> double {
    if constexpr (std::is_invocable_v<Func, double, param>) {
      return func(xx, params);
    } else {
      return func(xx);
    }
  };

  double f1 = -call_func(x1);
  double f2 = -call_func(x2);

  while (std::fabs(x3 - x0) > tol * (std::fabs(x1) + std::fabs(x2))) {
    if (f2 < f1) {
      x0 = x1;
      x1 = x2;
      x2 = r1 * x1 + r2 * x3;
      f1 = f2;
      f2 = -call_func(x2);
    } else {
      x3 = x2;
      x2 = x1;
      x1 = r1 * x2 + r2 * x0;
      f2 = f1;
      f1 = -call_func(x1);
    }
  }
  if (f1 <= f2) {
    return x1;
  } else {
    return x2;
  }
}

template <typename Func>
double golden(
    Func func,
    double a,
    double b,
    double c,
    double tol)
{
  struct Empty {};
  Empty params{};
  return golden(func, a, b, c, tol, params);
}

// Generic linear interpolation
template <typename Container>
double interp(const Container& x, const Container& y, double xout) {
  const size_t n = x.size();
  if (n == 0) throw std::invalid_argument("Input vectors are empty");
  if (n != y.size()) throw std::invalid_argument("x and y must have the same size");
  if (n == 1) return y[0];  // single point

  // Extrapolation
  if (xout <= x[0]) return y[0];
  if (xout >= x[n - 1]) return y[n - 1];

  // Binary search using std::lower_bound
  auto it = std::lower_bound(x.begin(), x.end(), xout);
  size_t idx = std::distance(x.begin(), it);

  // Ensure interval is valid
  if (idx == 0) idx = 1;  // in case xout == x[0]

  double x0 = x[idx - 1];
  double x1 = x[idx];
  double y0 = y[idx - 1];
  double y1 = y[idx];

  double t = (xout - x0) / (x1 - x0);
  return y0 * (1.0 - t) + y1 * t;
}

#endif
