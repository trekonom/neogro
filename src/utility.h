#ifndef UTILITY_H
#define UTILITY_H

#include <Rcpp.h>
using namespace Rcpp;

// Parameters
struct Params {
  double beta;
  double sigma;
  double alpha;
  double delta;
  double neg;
  double k0;
  NumericVector k;
  NumericVector vold;
};

double k_steady_state(double alpha, double beta, double delta);
double u(double c, double sigma);
double uc(double c, double sigma);
double output(double k, const Params params);
double consumption(double k0, double k1, const Params params);
double investment(double k0, double k1, const Params params);
double residuals(double k1, double c0, NumericVector k, NumericVector copt, const Params params);
double value(double x, NumericVector k, NumericVector vold);
double bellman1(double k1, const Params params);
double bellman(double k0, double k1, const Params params);

#endif
