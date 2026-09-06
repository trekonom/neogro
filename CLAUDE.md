# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`neogro` is an R package that solves the deterministic neoclassical growth
model via value function iteration, implemented in C++ (via Rcpp) for speed.
Almost all of the substantive logic lives in `src/`, not in R code — the R
layer (`R/RcppExports.R`) is a generated, thin wrapper around the compiled
routines.

## Common commands

This is a standard R package (devtools/roxygen2 workflow). Run these from an
R console with working directory set to the package root (or via `Rscript -e`):

- Rebuild `RcppExports.{R,cpp}` after adding/changing `// [[Rcpp::export]]`
  functions in `src/`: `Rcpp::compileAttributes()`
- Regenerate `.Rd` docs from roxygen comments (also re-runs compileAttributes
  if needed): `devtools::document()`
- Load the package for interactive development (compiles C++ sources):
  `devtools::load_all()`
- Full package check (build, compile, R CMD check): `devtools::check()`
- Build the vignette / README: `devtools::build_vignettes()`,
  `rmarkdown::render("README.Rmd")`

- Run the test suite: `devtools::test()` (or `testthat::test_dir("tests/testthat")`)

Automated tests live in `tests/testthat/` (testthat edition 3): closed-form
checks for `k_steady_state()` and `neogro()` (log utility + full
depreciation gives the known Brock-Mirman policy `k' = alpha*beta*k^alpha`),
sanity checks for `test_golden()`/`test_golden2()`, and a check that
`neogro()` warns on non-convergence. These are the primary regression net
for changes to the solver internals — run them after any change to
`src/*.cpp`/`*.h`.

In addition, manual/visual verification scripts live in `dev/` (git-ignored,
excluded from the build via `.Rbuildignore`):
- `dev/dev-test-golden.R` — sanity-checks the golden-section search against
  `test_golden()`/`test_golden2()` (toy functions defined in `src/math.cpp`).
- `dev/dev-check-neogro.R` — runs `neogro()`, writes `dev/policy.csv`, and
  plots policy/value functions and a simulated capital path to visually
  confirm the solver behaves as expected. Use this as the manual test when
  changing solver internals.

## Architecture

The C++ code is split into three files under `src/`, layered bottom-up:

- **`src/math.h`** — generic numerical primitives, header-only templates:
  - `golden(func, a, b, c, tol[, params])`: golden-section maximization.
    Overloaded to accept an optional `params` struct that gets forwarded to
    `func`; uses `if constexpr` to detect whether `func` takes one or two
    arguments. Note the function is negated internally (`-call_func`), so it
    finds a *maximum*.
  - `interp(x, y, xout)`: linear interpolation with clamping (flat)
    extrapolation at the boundaries — used to evaluate the value function
    and consumption policy off-grid.
  - `src/math.cpp` only holds toy test functions (`test_golden`,
    `test_golden2`) exported to R for validating `golden()` in isolation.

- **`src/utility.h` / `src/utility.cpp`** — the economic model: the `Params`
  struct (all model parameters plus the capital grid `k` and last-iteration
  value function `vold`; always passed as `const Params&`, never by value),
  the CRRA utility `u`/`uc`, the production function `output`, the
  budget-constraint helpers `consumption`/`investment`, the Euler-equation
  `residuals` (used only for post-hoc accuracy checks, not during solving),
  and the Bellman equation itself (`bellman`). `value()` is just `interp`
  over `(k, vold)`.

  `find_kopt(k0, l0, params, ZETA, TOL1)` is the per-grid-point optimizer
  used by `neogro()`'s main loop: it does a coarse grid search over `k1` to
  bracket the maximizing `kopt` for a given `k0` (exploiting concavity of
  the value function — the search stops as soon as `bellman` starts
  decreasing), handles boundary cases (optimum at the grid edges) by
  nudging the bracket by `ZETA`, then refines with `golden()` using a lambda
  closure over `k0`/`params` as the objective. `l0` is passed by reference
  and carries the coarse-search position *across* successive calls (kopt(k0)
  is increasing in k0, so each grid point's search resumes where the
  previous one left off instead of rescanning the whole grid) — it must be
  reset to `-1` at the start of each full sweep over the grid.

- **`src/rcpp_neogro.cpp`** — the `neogro()` entry point (the only
  `// [[Rcpp::export]]` in this file). Structure of the algorithm:
  1. Compute the steady-state capital `k_steady_state()` and build a grid
     `k` spanning `[0.5*ks, 1.5*ks]`.
  2. Initialize `v` from the closed-form value of consuming output forever.
  3. Iterate value function iteration until RMSE convergence (`TOL`) or
     `MAXIT`: for each grid point `k[i]`, call `find_kopt()` to get
     `kopt[i]`, then update `v[i] = bellman(k[i], kopt[i], params)`.
  4. Warn (`Rcpp::warning`) if the loop exits at `MAXIT` without meeting
     `TOL`, then recover `copt`, `iopt`, `y`, and Euler-equation `ropt`
     residuals for diagnostics.

When modifying the solver, keep the layering intent: `math.h` stays
model-agnostic (no `Params`/economics knowledge), `utility.*` encodes the
economics, and `rcpp_neogro.cpp` only orchestrates the iteration loop.

After editing any `src/*.cpp`/`*.h` file, `devtools::load_all()` or
`devtools::check()` recompiles automatically — there's no separate build
step to remember. If you add a new `// [[Rcpp::export]]`, run
`Rcpp::compileAttributes()` (or `devtools::document()`) before loading, or R
won't find the new exported symbol.
