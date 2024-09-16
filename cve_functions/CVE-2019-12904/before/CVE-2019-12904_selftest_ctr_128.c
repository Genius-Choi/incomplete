selftest_ctr_128 (void)
{
  const int nblocks = 8+1;
  const int blocksize = BLOCKSIZE;
  const int context_size = sizeof(RIJNDAEL_context);

  return _gcry_selftest_helper_ctr("AES", &rijndael_setkey,
           &rijndael_encrypt, &_gcry_aes_ctr_enc, nblocks, blocksize,
	   context_size);
}
