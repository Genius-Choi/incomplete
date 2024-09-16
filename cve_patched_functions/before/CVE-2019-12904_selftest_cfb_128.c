selftest_cfb_128 (void)
{
  const int nblocks = 8+2;
  const int blocksize = BLOCKSIZE;
  const int context_size = sizeof(RIJNDAEL_context);

  return _gcry_selftest_helper_cfb("AES", &rijndael_setkey,
           &rijndael_encrypt, &_gcry_aes_cfb_dec, nblocks, blocksize,
	   context_size);
}
