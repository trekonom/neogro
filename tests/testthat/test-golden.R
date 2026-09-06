test_that("golden section search finds the maximum of a simple parabola", {
  # test_golden() maximizes -x^2 + 6x + 6, whose maximum is at x = 3
  expect_equal(test_golden(tol = 1e-7), 3, tolerance = 1e-5)
})

test_that("golden section search works with an extra params argument", {
  # test_golden2() maximizes -(x - 2)^2 + 3, whose maximum is at x = 2
  expect_equal(test_golden2(tol = 1e-7), 2, tolerance = 1e-5)
})
