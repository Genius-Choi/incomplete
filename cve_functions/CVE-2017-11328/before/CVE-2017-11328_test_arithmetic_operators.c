static void test_arithmetic_operators()
{
  assert_true_rule(
      "rule test { condition: (1 + 1) * 2 == (9 - 1) \\ 2 }", NULL);

  assert_true_rule(
      "rule test { condition: 5 % 2 == 1 }", NULL);

  assert_true_rule(
      "rule test { condition: 1.5 + 1.5 == 3}", NULL);

  assert_true_rule(
      "rule test { condition: 3 \\ 2 == 1}", NULL);

  assert_true_rule(
      "rule test { condition: 3.0 \\ 2 == 1.5}", NULL);

  assert_true_rule(
      "rule test { condition: 1 + -1 == 0}", NULL);

  assert_true_rule(
      "rule test { condition: -1 + -1 == -2}", NULL);

  assert_true_rule(
      "rule test { condition: 4 --2 * 2 == 8}", NULL);

  assert_true_rule(
      "rule test { condition: -1.0 * 1 == -1.0}", NULL);

  assert_true_rule(
      "rule test { condition: 1-1 == 0}", NULL);

  assert_true_rule(
      "rule test { condition: -2.0-3.0 == -5}", NULL);

  assert_true_rule(
      "rule test { condition: --1 == 1}", NULL);

  assert_true_rule(
      "rule test { condition: 1--1 == 2}", NULL);

  assert_true_rule(
      "rule test { condition: -0x01 == -1}", NULL);

  assert_true_rule(
      "rule test { condition: 0o10 == 8 }", NULL);

  assert_true_rule(
      "rule test { condition: 0o100 == 64 }", NULL);

  assert_true_rule(
      "rule test { condition: 0o755 == 493 }", NULL);

}
