run_selftests (int algo, int extended, selftest_report_func_t report)
{
  gpg_err_code_t ec;

  switch (algo)
    {
    case GCRY_CIPHER_AES128:
      ec = selftest_fips_128 (extended, report);
      break;
    case GCRY_CIPHER_AES192:
      ec = selftest_fips_192 (extended, report);
      break;
    case GCRY_CIPHER_AES256:
      ec = selftest_fips_256 (extended, report);
      break;
    default:
      ec = GPG_ERR_CIPHER_ALGO;
      break;

    }
  return ec;
}
