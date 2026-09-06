test_that("k_steady_state matches the closed-form formula", {
  alpha <- 0.33
  beta <- 0.96
  delta <- 0.05

  expected <- (alpha * beta / (1 - beta * (1 - delta)))^(1 / (1 - alpha))

  expect_equal(k_steady_state(alpha, beta, delta), expected)
})
