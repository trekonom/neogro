#include "utility.h"
#include "math.h"
#include <cmath>

//' Steady State Capital Stock
//'
//' This function computes the steady state capital stock of the standard
//' deterministic neoclassical growth model
//'
//' @param beta Numeric. Discount factor \eqn{\beta}.
//' @param alpha Numeric. Capital share \eqn{\alpha} in production.
//' @param delta Numeric. Depreciation rate of capital \eqn{\delta}.
//'
//' @return A `Numeric` with the following components:
//'
//' @examples
//' k_steady_state(alpha = 0.33, beta = 0.96, delta = 0.05)
//'
//' @export
// [[Rcpp::export]]
double k_steady_state(double alpha, double beta, double delta) {
  return pow(alpha * beta / (1.0 - beta * (1.0 - delta)), 1.0 / (1.0 - alpha));
}

// utiliy
double u(double c, double sigma) {
  if (sigma != 1.0) {
    return (pow(c, 1.0 - sigma)) / (1.0 - sigma);
  } else {
    return log(c);
  }
}

// marginal utility
double uc(double c, double sigma) {
  return pow(c, -sigma);
}

// output
double output(double k, const Params params) {
  return pow(k, params.alpha);
}

// consumption
double consumption(double k0, double k1, const Params params) {
  return pow(k0, params.alpha) + (1.0 - params.delta) * k0 - k1;
}

// investment
double investment(double k0, double k1, const Params params) {
  return k1 - (1.0 - params.delta) * k0;
}

// residuals
double residuals(double k1, double c0, NumericVector k, NumericVector copt, const Params params) {
  double r;
  double c1 = interp(k, copt, k1);

  r = uc(c0, params.sigma) / uc(c1, params.sigma);
  r *= params.beta * (1.0 - params.delta + params.alpha * pow(k1, params.alpha - 1.0));
  r = 1.0 - r;

  return r;
}

double value(double x, NumericVector k, NumericVector vold) {
  return interp(k, vold, x);
}

double bellman1(double k1, const Params params) {
  return bellman(params.k0, k1, params);
}

double bellman(double k0, double k1, const Params params) {
  NumericVector k = params.k;
  NumericVector vold = params.vold;

  double c = consumption(k0, k1, params);
  if (c < 0.0) {
    return params.neg;
  } else {
    if (k1 >= k[k.size()-1]) {
      return pow(k1, 2) * params.neg;
    } else {
      return u(c, params.sigma) + params.beta * value(k1, k, vold);
    }
  }
}

