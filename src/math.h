#ifndef MATH_H
#define MATH_H

#include <Rcpp.h>
using namespace Rcpp;

struct params_golden {
};

double golden2(
    double (*func)(double, void *params),
    double a,
    double b,
    double c,
    void *params,
    double tol
);

#endif
