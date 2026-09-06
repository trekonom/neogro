# neogro 0.1.0

## Internal changes

- Extracted the per-grid-point bracket-search / golden-section refinement
  step of the value function iteration in `neogro()` into a new
  `find_kopt()` helper, shrinking the main solver loop to the outer
  iterate-until-converged logic.
- `bellman()` and friends now take `Params` by `const&` instead of by value,
  and the mutable `Params.k0` currying field (and `bellman1()`) was replaced
  by a lambda closure at the call site.
- Fixed a latent uninitialized-variable read risk (`lopt` in the bracket
  search).
- `neogro()` now emits a warning if value function iteration fails to
  converge within `MAXIT` iterations, instead of failing silently.

## Testing

- Added a `tests/testthat` suite: closed-form checks for `k_steady_state()`
  and `neogro()` (log utility with full depreciation has a known
  closed-form policy function), sanity checks for `test_golden()` /
  `test_golden2()`, and a check for the new non-convergence warning.

These changes are internal/behind-the-scenes and do not change `neogro()`'s
public interface or numerical output.
