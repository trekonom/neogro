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
double output(double k, const Params& params) {
  return pow(k, params.alpha);
}

// consumption
double consumption(double k0, double k1, const Params& params) {
  return pow(k0, params.alpha) + (1.0 - params.delta) * k0 - k1;
}

// investment
double investment(double k0, double k1, const Params& params) {
  return k1 - (1.0 - params.delta) * k0;
}

// residuals
double residuals(double k1, double c0, NumericVector k, NumericVector copt, const Params& params) {
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

double bellman(double k0, double k1, const Params& params) {
  const NumericVector& k = params.k;
  const NumericVector& vold = params.vold;

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

// Coarse grid search to bracket the optimal k1 for a given k0, then refine
// with golden-section search. `l0` carries the search position across
// successive calls (kopt(k0) is increasing in k0, so each call can resume
// the coarse search where the previous one left off instead of scanning
// the whole grid again).
double find_kopt(double k0, int& l0, const Params& params, double ZETA, double TOL1) {
  const NumericVector& k = params.k;
  const int NK = k.size();

  int l = l0, lopt = -1;
  double v0 = params.neg;
  double ax = k[0], bx = k[0], cx = k[NK - 1];

  while (l < NK - 1) {
    l += 1;
    double c = consumption(k0, k[l], params);
    if (c > 0.0) {
      double v1 = bellman(k0, k[l], params);
      if (v1 > v0) {
        if (l == 0) {
          ax = k[0]; bx = k[0]; cx = k[1];
        } else if (l == NK - 1) {
          ax = k[NK - 2]; bx = k[NK - 1]; cx = k[NK - 1];
        } else {
          ax = k[l - 1]; bx = k[l]; cx = k[l + 1];
          lopt = l;
        }
        v0 = v1;
        l0 = l - 1;
      } else {
        l = NK - 1;
      }
    } else {
      l = NK - 1;
    }
  }

  double kopt;
  if (ax == bx) {
    kopt = k[0];
  } else if (bx == cx) {
    kopt = k[NK - 1];
  } else {
    kopt = k[lopt];
  }

  auto objective = [&](double k1) { return bellman(k0, k1, params); };

  if (ax == bx) {
    bx = ax + ZETA * (k[1] - k[0]);
    if (value(bx, k, params.vold) < value(ax, k, params.vold)) {
      kopt = k[0];
    } else {
      kopt = golden(objective, ax, bx, cx, TOL1);
    }
  } else if (bx == cx) {
    bx = cx - ZETA * (k[NK - 1] - k[NK - 2]);
    if (value(bx, k, params.vold) < value(cx, k, params.vold)) {
      kopt = k[NK - 1];
    } else {
      kopt = golden(objective, ax, bx, cx, TOL1);
    }
  } else {
    kopt = golden(objective, ax, bx, cx, TOL1);
  }

  return kopt;
}

