void test_base64_encode(void)
{
  char buffer[16];
  size_t len = mutt_b64_encode(buffer, clear, sizeof(clear) - 1, sizeof(buffer));
  if (!TEST_CHECK(len == sizeof(encoded) - 1))
  {
    TEST_MSG("Expected: %zu", sizeof(encoded) - 1);
    TEST_MSG("Actual  : %zu", len);
  }
  if (!TEST_CHECK(strcmp(buffer, encoded) == 0))
  {
    TEST_MSG("Expected: %zu", encoded);
    TEST_MSG("Actual  : %zu", buffer);
  }
}
