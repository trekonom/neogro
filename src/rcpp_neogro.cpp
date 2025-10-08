#include <Rcpp.h>
#include "utility.h"
using namespace Rcpp;

//' Solve the Neoclassical Growth Model
//'
//' This function solves a standard deterministic neoclassical growth model
//' using value function iteration. The solution returns the optimal
//' policy functions and the value function over a discretized grid of capital.
//'
//' The model assumes a Cobb-Douglas production function
//' \eqn{f(k) = k^{\alpha}}, and solves for the household's
//' optimal savings policy under given parameters. Convergence is controlled
//' by the tolerances \code{TOL} and \code{TOL1}.
//'
//' @param NK Integer. Number of grid points for capital (default = 200).
//' @param MAXIT Integer. Maximum number of value function iterations (default = 500).
//' @param TOL Numeric. Convergence tolerance for value function (default = 1e-5).
//' @param TOL1 Numeric. Convergence tolerance for golden section search (default = 1e-7).
//' @param NEG Numeric. Large negative number used as a placeholder for infeasible utility (default = -1e10).
//' @param ZETA Numeric. Relaxation parameter for value function updates (default = 0.05).
//' @param beta Numeric. Discount factor \eqn{\beta} (default = 0.994).
//' @param sigma Numeric. Relative risk aversion (CRRA) parameter \eqn{\sigma} (default = 2.0).
//' @param alpha Numeric. Capital share \eqn{\alpha} in production (default = 0.28).
//' @param delta Numeric. Depreciation rate of capital \eqn{\delta} (default = 0.0).
//' @param verbose Boolean. If `true` prints the error at each iteration (default = false).
//'
//' @return A `DataFrame` with the following components:
//' \itemize{
//'   \item `k` – Capital stock.
//'   \item `v` – Value function.
//'   \item `kopt` – Optimal capital choice.
//'   \item `copt` – Optimal consumption choice.
//'   \item `iopt` – Optimal investment choice.
//'   \item `y` – output.
//'   \item `ropt` – residuals of first-order condition of optimal savings
//'       decision problem..
//' }
//'
//' @examples
//' # Solve the neoclassical growth model with default parameters
//' result <- neogro()
//' head(result)
//'
//' # Solve with custom parameters
//' result <- neogro(NK = 300, beta = 0.96, alpha = 0.33, delta = 0.05)
//' plot(result$k, result$kopt, type = "l", main = "Policy Function")
//'
//' @export
// [[Rcpp::export]]
DataFrame neogro(int NK = 200,
                 int MAXIT = 500,
                 double TOL = 1e-5,
                 double TOL1 = 1e-7,
                 double NEG = -1e10,
                 double ZETA = 0.05,
                 double beta = 0.994,
                 double sigma = 2.0,
                 double alpha = 0.28,
                 double delta = 0.0,
                 bool verbose = false) {

  NumericVector k(NK), kopt(NK), copt(NK), iopt(NK), y(NK), ropt(NK),
    v(NK), vold(NK), vsub(NK);

  // Parameters
  Params params;
  params.beta = beta;
  params.sigma = sigma;
  params.alpha = alpha;
  params.delta = delta;
  params.neg = NEG;
  params.k0 = 0.0;

  // Steady state and grid
  double ks = k_steady_state(alpha, beta, delta);
  double kk_min = 0.5 * ks;
  double kk_max = 1.5 * ks;
  double step = (kk_max - kk_min) / (NK - 1);

  for (int i = 0; i < NK; ++i) {
    k[i] = kk_min + i * step;
  }

  Rcpp::Rcout << "Steady-state capital stock: " << ks << std::endl;

  // Initial value function
  for (int i = 0; i < NK; ++i) {
    v[i] = u(pow(k[i], alpha) - delta * k[i], sigma) / (1.0 - beta);
  }

  double crit = 1.0 + TOL;
  int h = 0;

  // Main loop
  while (crit > TOL && h < MAXIT) {
    h++;
    for (int i = 0; i < NK; ++i) vold[i] = v[i];

    int l0 = -1;
    for (int i = 0; i < NK; ++i) {
      int l = l0, lopt;
      double v0 = NEG;
      double ax = k[0], bx = k[0], cx = k[NK-1];
      double c, v1;

      while (l < NK-1) {
        l += 1;
        c = consumption(k[i], k[l], params);
        if (c > 0.0) {
          v1 = bellman(k[i], k[l], k, vold, params);
          if (v1 > v0) {
            v[i] = v1;
            if (l == 0) {
              ax = k[0]; bx = k[0]; cx = k[1];
            } else if (l == NK-1) {
              ax = k[NK-2]; bx = k[NK-1]; cx = k[NK-1];
            } else {
              ax = k[l-1]; bx = k[l]; cx = k[l+1];
              lopt = l;
            }
            v0 = v1;
            l0 = l-1;
          } else {
            l = NK-1;
          }
        } else {
          l = NK-1;
        }
      }

      if (ax == bx) {
        kopt[i] = k[0];
      } else if (bx == cx) {
        kopt[i] = k[NK-1];
      } else {
        kopt[i] = k[lopt];
      }

      if (ax == bx) {
        bx = ax + ZETA * (k[1] - k[0]);
        if (value(bx, k, vold) < value(ax, k, vold)) {
          kopt[i] = k[0];
        } else {
          kopt[i] = golden(k[i], k, vold, params, ax, bx, cx, TOL1);
        }
      } else if (bx == cx) {
        bx = cx - ZETA * (k[NK-1] - k[NK-2]);
        if (value(bx, k, vold) < value(cx, k, vold)) {
          kopt[i] = k[NK-1];
        } else {
          kopt[i] = golden(k[i], k, vold, params, ax, bx, cx, TOL1);
        }
      } else {
        kopt[i] = golden(k[i], k, vold, params, ax, bx, cx, TOL1);
      }
      v[i] = bellman(k[i], kopt[i], k, vold, params);
    }

    // Root mean squared error
    crit = 0.0;
    for (int i = 0; i < NK; ++i) {
      vsub[i] = pow(v[i] - vold[i], 2.0);
      crit += vsub[i];
      //if (fabs(vsub[i]) > crit) crit = fabs(vsub[i]);
    }
    crit /= NK;
    crit = pow(crit, .5);

    // Print iteration and error (to R console)
    if (verbose) {
      Rcpp::Rcout << "iteration over value function: " << h << " error: " << crit << std::endl;
    }
  }

  Rcpp::Rcout << "iteration over value function: " << h << " error: " << crit << std::endl;

  // consumption policy
  for (int i = 0; i < NK; ++i) {
    copt[i] = consumption(k[i], kopt[i], params);
    iopt[i] = investment(k[i], kopt[i], params);
    y[i] = output(k[i], params);
  }

  // residuals
  for (int i = 0; i < NK; ++i) {
    ropt[i] = residuals(kopt[i], copt[i], k, copt, params);
  }

  // Return as a DataFrame with column names
  return DataFrame::create(
    Named("k") = k,
    Named("kopt") = kopt,
    Named("copt") = copt,
    Named("iopt") = iopt,
    Named("y") = y,
    Named("ropt") = ropt,
    Named("vopt") = v
  );
}
