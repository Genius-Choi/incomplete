ghash_armv7_neon (gcry_cipher_hd_t c, byte *result, const byte *buf,
		  size_t nblocks)
{
  return _gcry_ghash_armv7_neon(c->u_mode.gcm.u_ghash_key.key, result, buf,
				nblocks);
}
