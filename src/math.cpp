#include <Rcpp.h>
#include "math.h"
using namespace Rcpp;

double golden2(
    double (*func)(double, void *params),
    double a,
    double b,
    double c,
    void *params,
    double tol
) {
  const double r1 = 0.61803399;
  const double r2 = 1.0 - r1;
  double x0 = a, x3 = c;
  double x1, x2;
  if (fabs(c - b) <= fabs(b - a)) {
    x1 = b;
    x2 = b + r2 * (c - b);
  } else {
    x2 = b;
    x1 = b - r2 * (b - a);
  }
  double f1 = -func(x1, params);
  double f2 = -func(x2, params);

  while (fabs(x3 - x0) > tol * (fabs(x1) + fabs(x2))) {
    if (f2 < f1) {
      x0 = x1;
      x1 = x2;
      x2 = r1 * x1 + r2 * x3;
      f1 = f2;
      f2 = -func(x2, params);
    } else {
      x3 = x2;
      x2 = x1;
      x1 = r1 * x2 + r2 * x0;
      f2 = f1;
      f1 = -func(x1, params);
    }
  }
  if (f1 <= f2) {
    return x1;
  } else {
    return x2;
  }
}

// Test Function
double testfunc(double x) {
  return -pow(x, 2) + 4 * x + 6;
}

//' Test Golden Section Maximization
//'
//' This function computes the steady state capital stock of the standard
//' deterministic neoclassical growth model
//'
//' @return A `Numeric` with the following components:
//'
//' @examples
//' k_steady_state(alpha = 0.33, beta = 0.96, delta = 0.05)
//'
//' @export
// [[Rcpp::export]]
 double test_golden(
     double ax = -2.2,
     double bx = 0.0,
     double cx = 10.0,
     double tol = .001
) {
   params_golden params;
   return golden2(
     (double (*)(double,void*))testfunc,
     ax = ax, bx = bx, cx = cx, &params, tol = tol
   );
 }
