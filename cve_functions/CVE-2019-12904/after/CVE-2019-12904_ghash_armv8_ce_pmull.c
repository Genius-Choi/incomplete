ghash_armv8_ce_pmull (gcry_cipher_hd_t c, byte *result, const byte *buf,
                      size_t nblocks)
{
  return _gcry_ghash_armv8_ce_pmull(c->u_mode.gcm.u_ghash_key.key, result, buf,
                                    nblocks, c->u_mode.gcm.gcm_table);
}
