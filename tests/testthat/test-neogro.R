test_that("neogro's policy function matches the closed-form Brock-Mirman solution", {
  # Under log utility (sigma = 1) and full depreciation (delta = 1), the
  # neoclassical growth model has a known closed-form policy function:
  #   k' = alpha * beta * k^alpha
  alpha <- 0.33
  beta <- 0.96
  sigma <- 1.0
  delta <- 1.0

  result <- neogro(
    NK = 300,
    alpha = alpha,
    beta = beta,
    sigma = sigma,
    delta = delta,
    verbose = FALSE
  )

  analytical_kopt <- alpha * beta * result$k^alpha
  rel_err <- abs(result$kopt - analytical_kopt) / analytical_kopt

  expect_lt(max(rel_err), 0.01)
})

test_that("neogro() warns when it fails to converge within MAXIT iterations", {
  expect_warning(
    neogro(MAXIT = 1, verbose = FALSE),
    "did not converge"
  )
})
