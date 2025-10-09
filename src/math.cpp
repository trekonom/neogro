#include <Rcpp.h>
#include "math.h"
using namespace Rcpp;

// Linear interpolation
double interp(NumericVector x, NumericVector y, double xout) {
  int n = x.size();
  if (xout <= x[0]) return y[0];
  if (xout >= x[n-1]) return y[n-1];
  for (int i = 0; i < n-1; ++i) {
    if (xout >= x[i] && xout < x[i+1]) {
      double t = (xout - x[i]) / (x[i+1] - x[i]);
      return y[i] * (1.0-t) + y[i+1] * t;
    }
  }
  return y[n-1];
}

// Test Functions for Golden Section Maximization
double testfunc(double x) {
  return -std::pow(x, 2) + 6 * x + 6;
}

struct TestParams { double a; double b; };

double testfunc2(double x, const TestParams& p) {
  return -std::pow(x - p.a, 2) + p.b;
}

//' Test Golden Section Maximization
//'
//' @param ax,bx,cx interval and starting value for golden section
//'     search
//' @param tol tolerance for stopping criterion
//'
//' @return A `Numeric`
//'
//' @name test-golden
//'
//' @examples
//' test_golden()

//' @rdname test-golden
//' @export
// [[Rcpp::export]]
 double test_golden(
     double ax = -2.2,
     double bx = 0.0,
     double cx = 10.0,
     double tol = .001
) {
   return golden(testfunc, ax, bx, cx, tol);
 }

//' @rdname test-golden
//' @export
// [[Rcpp::export]]
double test_golden2(
     double ax = -2.2,
     double bx = 0.0,
     double cx = 10.0,
     double tol = .001)
{
   TestParams p{2.0, 3.0};

   return golden(testfunc2, ax, bx, cx, tol, p);
}
