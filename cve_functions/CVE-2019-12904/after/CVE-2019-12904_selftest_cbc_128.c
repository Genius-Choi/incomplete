selftest_cbc_128 (void)
{
  const int nblocks = 8+2;
  const int blocksize = BLOCKSIZE;
  const int context_size = sizeof(RIJNDAEL_context);

  return _gcry_selftest_helper_cbc("AES", &rijndael_setkey,
           &rijndael_encrypt, &_gcry_aes_cbc_dec, nblocks, blocksize,
	   context_size);
}
