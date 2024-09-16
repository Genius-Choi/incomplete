selftest (void)
{
  const char *r;

  if ( (r = selftest_basic_128 ())
       || (r = selftest_basic_192 ())
       || (r = selftest_basic_256 ()) )
    return r;

  if ( (r = selftest_ctr_128 ()) )
    return r;

  if ( (r = selftest_cbc_128 ()) )
    return r;

  if ( (r = selftest_cfb_128 ()) )
    return r;

  return r;
}
